#pragma once

#include <string>

enum TokenType {
  kNone = 0,
  kNumber,
  kId,
  kVar,
  kPrint,
  kIf,
  kElse,
  kWhile,
  kPlus,
  kMinus,
  kStar,
  kSlash,
  kEq,
  kEqEq,
  kExcl,
  kNEq,
  kLT,
  kGT,
  kLTEQ,
  kGTEQ,
  kAnd,
  kOr,
  kLParen,
  kRParen,
  kLBrace,
  kRBrace,
  kSemicolon,
  kEOF,
};

TokenType parse_type(std::string val);

std::string type_to_str(TokenType tt);

class Token {
private:
  const TokenType tt_;
  const std::string value_;
public:
  TokenType token_type() const;
  std::string value() const;
  std::string to_string() const;
  Token(TokenType tt, std::string value);
  Token(TokenType tt);
};

