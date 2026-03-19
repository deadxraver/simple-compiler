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
  void prev();
  Token current() const;
  bool match(TokenType) const;
  bool is_eof() const;
public:
  std::vector<std::unique_ptr<Statement>> parse();
  Parser(const std::vector<Token>&);
};
