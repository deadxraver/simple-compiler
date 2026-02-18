#pragma once

#include <string>
#include <vector>

#include "token.hpp"

class Lexer {
private:
  const std::string input_;
  const int length_;
  int position_;
  void next();
  char current() const;
public:
  std::vector<Token> tokenize();
  Lexer(std::string input);
};
