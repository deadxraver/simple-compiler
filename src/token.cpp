#include "token.hpp"

TokenType Token::token_type() const {
  return this->tt_;
}

std::string Token::value() const {
  return this->value_;
}

std::string type_to_str(TokenType tt) {
  switch (tt) {
    case kNone: return "NONE";
    case kNumber: return "NUMBER";
    case kId: return "ID";
    case kVar: return "VAR";
    case kPrint: return "PRINT";
    case kIf: return "IF";
    case kElse: return "ELSE";
    case kWhile: return "WHILE";
    case kPlus: return "PLUS";
    case kMinus: return "MINUS";
    case kStar: return "STAR";
    case kSlash: return "SLASH";
    case kEq: return "EQ";
    case kEqEq: return "EQEQ";
    case kExcl: return "EXCL";
    case kNEq: return "NEQ";
    case kLT: return "LT";
    case kGT: return "GT";
    case kLTEQ: return "LTEQ";
    case kGTEQ: return "GTEQ";
    case kAnd: return "AND";
    case kOr: return "OR";
    case kLParen: return "LPAREN";
    case kRParen: return "RPAREN";
    case kLBrace: return "LBRACE";
    case kRBrace: return "RBRACE";
    case kSemicolon: return "SEMICOLON";
    case kEOF: return "EOF";
    default: return "UNKNOWN";
  }
}

std::string Token::to_string() const {
  return "{" + type_to_str(tt_) + ": '" + value_ + "'}";
}

TokenType parse_type(std::string val) {
  if (val == "var")
    return kVar;
  if (val == "print")
    return kPrint;
  if (val == "if")
    return kIf;
  if (val == "else")
    return kElse;
  if (val == "while")
    return kWhile;
  if (val == "+")
    return kPlus;
  if (val == "-")
    return kMinus;
  if (val == "*")
    return kStar;
  if (val == "/")
    return kSlash;
  if (val == "=")
    return kEq;
  if (val == "==")
    return kEqEq;
  if (val == "!")
    return kExcl;
  if (val == "!=")
    return kNEq;
  if (val == "<=")
    return kLTEQ;
  if (val == ">=")
    return kGTEQ;
  if (val == "&")
    return kAnd;
  if (val == "|")
    return kOr;
  if (val == "(")
    return kLParen;
  if (val == ")")
    return kRParen;
  if (val == "{")
    return kLBrace;
  if (val == "}")
    return kRBrace;
  if (val == ";")
    return kSemicolon;
  return kId;
}

Token::Token(TokenType tt, std::string value) : tt_(tt), value_(value) {}

Token::Token(TokenType tt) : Token(tt, "") {}
