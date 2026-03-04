#pragma once

#include "token.hpp"
#include "statement.hpp"

#include <vector>

class Parser {
private:
  std::vector<Token> tokens_;
  std::size_t pos_;
  void next();
  Token current() const;
  bool is_eof() const;
public:
  std::vector<Statement> parse();
  Parser(const std::vector<Token>&);
};
