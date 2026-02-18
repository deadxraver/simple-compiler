#include "token.hpp"

TokenType Token::token_type() const {
  return this->tt_;
}

std::string Token::value() const {
  return this->value_;
}

std::string Token::to_string() const {
  return "{" + std::to_string((int)tt_) + ": '" + value_ + "'}";
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
