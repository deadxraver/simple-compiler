#include "parser.hpp"

Parser::Parser(const std::vector<Token>& tokens) : tokens_(tokens), pos_(0) {}

void Parser::next() {
  ++(this->pos_);
}

bool Parser::consume(TokenType expected) {
  if (this->match(expected)) {
    this->next();
    return true;
  }
  return false;
}

void Parser::evil_consume(TokenType expected, std::string message) {
  if (!this->consume(expected))
    throw message;
}

void Parser::prev() {
  --(this->pos_);
}

Token Parser::current() const {
  return this->tokens_[this->pos_];
}

bool Parser::match(TokenType tt) const {
  return tt == this->current().token_type();
}

bool Parser::is_eof() const {
  return this->match(kEOF);
}

std::unique_ptr<Statement> Parser::parse_statement() {
  if (match(kVar))
    return parse_var();
  if (match(kPrint))
    return parse_print();
  if (match(kIf))
    return parse_if();
  if (match(kWhile))
    return parse_while();
  if (match(kLBrace))
    return parse_block();

  return parse_expression();
}

std::unique_ptr<Statement> Parser::parse_expression() {
  std::unique_ptr<Statement> ret = std::make_unique<ExpressionStatement>(parse_expr());
  evil_consume(kSemicolon, "Expected semicolon after statement");
  return ret;
}

std::unique_ptr<Statement> Parser::parse_print() {
  evil_consume(kPrint, "Expected `print`");
  auto ret = std::make_unique<PrintStatement>(parse_expr());
  evil_consume(kSemicolon, "Expected semicolon after print statement");
  return ret;
}

std::unique_ptr<Statement> Parser::parse_var() {
  evil_consume(kVar, "Expected `var`");
  if (!match(kId))
    throw std::string("Expected ID after `var`");
  std::string name = current().value();
  next();
  if (consume(kSemicolon))
    return std::make_unique<VarStatement>(name);
  if (!consume(kEq))
    throw std::string("expected `var <name>;` or `var <name> = ...`");
  std::unique_ptr<VarStatement> ret = std::make_unique<VarStatement>(name, parse_expr());
  evil_consume(kSemicolon, "Expected semicolon after var statement");
  return ret;
}

std::unique_ptr<Statement> Parser::parse_block() {
  evil_consume(kLBrace, "Expected `{` at the start of the block");
  std::vector<std::unique_ptr<Statement>> block;
  while (!match(kRBrace) && !match(kEOF)) {
    block.push_back(parse_statement());
  }
  evil_consume(kRBrace, "Expected `}` at the end of block");
  return std::make_unique<BlockStatement>(std::move(block));
}

std::unique_ptr<Statement> Parser::parse_if() {
  evil_consume(kIf, "Expected IF token");
  return std::make_unique<IfStatement>(parse_expr(), parse_block(), parse_block());
}

std::unique_ptr<Statement> Parser::parse_while() {
  evil_consume(kWhile, "Expected WHILE token");
  return std::make_unique<WhileStatement>(parse_expr(), parse_block());
}

std::unique_ptr<Expression> Parser::parse_expr() {
  return parse_assignment();
}

std::unique_ptr<Expression> Parser::parse_assignment() {
  std::unique_ptr<Expression> left = parse_logical_or();
  if (match(kEq)) {
    Token eq = current();
    next();
    std::unique_ptr<Expression> right = parse_assignment();
    if (auto var = dynamic_cast<VariableExpression*>(left.get())) {
      return std::make_unique<AssignExpression>(var->name(), std::move(right));
    } else {
      throw std::string("Invalid left-hand side in assignment (line " + std::to_string(eq.token_type()) + ")");
    }
  }
  return left;
}

std::unique_ptr<Expression> Parser::parse_logical_or() {
  std::unique_ptr<Expression> expr = parse_logical_and();
  while (match(kOr)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_logical_and();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

// Bajduki
std::unique_ptr<Expression> Parser::parse_logical_and() {
  std::unique_ptr<Expression> expr = parse_equality();
  while (match(kAnd)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_equality();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parse_equality() {
  std::unique_ptr<Expression> expr = parse_comparison();
  while (match(kEqEq) || match(kNEq)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_comparison();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parse_comparison() {
  std::unique_ptr<Expression> expr = parse_term();
  while (match(kLT) || match(kGT) || match(kLTEQ) || match(kGTEQ)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_term();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parse_term() {
  std::unique_ptr<Expression> expr = parse_factor();
  while (match(kPlus) || match(kMinus)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_factor();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parse_factor() {
  std::unique_ptr<Expression> expr = parse_unary();
  while (match(kStar) || match(kSlash)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_unary();
    expr = std::make_unique<BinaryExpression>(std::move(expr), op.token_type(), std::move(right));
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parse_unary() {
  if (match(kExcl) || match(kMinus)) {
    Token op = current();
    next();
    std::unique_ptr<Expression> right = parse_unary();
    return std::make_unique<UnaryExpression>(op.token_type(), std::move(right));
  }
  return parse_primary();
}

std::unique_ptr<Expression> Parser::parse_primary() {
  if (match(kNumber)) {
    double value = std::stod(current().value());
    next();
    return std::make_unique<NumberExpression>(value);
  }
  if (match(kString)) {
    std::string value = current().value();
    next();
    return std::make_unique<StringExpression>(value);
  }
  if (match(kId)) {
    std::string name = current().value();
    next();
    return std::make_unique<VariableExpression>(name);
  }
  if (match(kLParen)) {
    next();
    std::unique_ptr<Expression> expr = parse_expr();
    evil_consume(kRParen, "Expected `)` after expression");
    return expr;
  }
  throw std::string(
    "Expected primary expression (number, string, identifier, or `(`), got: " 
    + type_to_str(current().token_type())
  );
}

std::vector<std::unique_ptr<Statement>> Parser::parse() {
  std::vector<std::unique_ptr<Statement>> result;
  while(!this->is_eof()) {
    result.push_back(parse_statement());
  }
  return result;
}
