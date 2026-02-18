#include "lexer.hpp"

#include "util.hpp"

Lexer::Lexer(std::string input) : input_(input), length_(input.size()), position_(0) {
}

void Lexer::next() {
  ++(this->position_);
}

char Lexer::current() const {
  if (this->position_ >= this->length_) {
    return 0;
  }
  return this->input_[this->position_];
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> result;
  while (1) {
    char c = this->current();
    if (is_whitespace(c)) {
      next();
      continue;
    }
    if (is_letter(c)) {
      std::string val;
      while (is_letter(c) || is_digit(c)) {
        val.push_back(c);
        next();
        c = current();
      }
      TokenType t = parse_type(val);
      result.push_back(Token(t, val));
      continue;
    }
    if (is_digit(c)) {
      std::string val;
      while (is_digit(c)) {
        val.push_back(c);
        next();
        c = current();
      }
      result.push_back(Token(kNumber, val));
      continue;
    }
    if (is_operator(c)) {
      std::string val;
      while (is_operator(c)) {
        val.push_back(c);
        next();
        c = current();
      }
      TokenType tt = parse_type(val);
      result.push_back(Token(tt));
      continue;
    }
    if (c == ';') {
      result.push_back(Token(kSemicolon));
      next();
      continue;
    }
    if (c == '(') {
      result.push_back(Token(kLParen));
      next();
      continue;
    }
    if (c == ')') {
      result.push_back(Token(kRParen));
      next();
      continue;
    }
    if (c == '{') {
      result.push_back(Token(kLBrace));
      next();
      continue;
    }
    if (c == '}') {
      result.push_back(Token(kRBrace));
      next();
      continue;
    }
    if (is_eof(c)) {
      result.push_back(Token(kEOF));
      break;
    }
  }
  return result;
}
