#pragma once

#include "token.hpp"
#include "statement.hpp"

#include <vector>
#include <memory>

class Parser {
private:
  std::vector<Token> tokens_;
  std::size_t pos_;
  void next();
  bool consume(TokenType);
  void evil_consume(TokenType, std::string);
  void prev();
  Token current() const;
  bool match(TokenType) const;
  bool is_eof() const;
  std::unique_ptr<Statement> parse_statement();
  std::unique_ptr<Statement> parse_expression();
  std::unique_ptr<Statement> parse_print();
  std::unique_ptr<Statement> parse_var();
  std::unique_ptr<Statement> parse_block();
  std::unique_ptr<Statement> parse_if();
  std::unique_ptr<Statement> parse_while();

  std::unique_ptr<Expression> parse_expr();
  std::unique_ptr<Expression> parse_assignment();
  std::unique_ptr<Expression> parse_logical_or();
  std::unique_ptr<Expression> parse_logical_and();
  std::unique_ptr<Expression> parse_equality();
  std::unique_ptr<Expression> parse_comparison();
  std::unique_ptr<Expression> parse_term();
  std::unique_ptr<Expression> parse_factor();
  std::unique_ptr<Expression> parse_unary();
  std::unique_ptr<Expression> parse_primary();

public:
  std::vector<std::unique_ptr<Statement>> parse();
  Parser(const std::vector<Token>&);
};
