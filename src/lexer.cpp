#include "lexer.hpp"

#include "util.hpp"

#include <exception>
#include <iostream>

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

char Lexer::lookup_next() const {
  return this->input_[this->position_ + 1];
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> result;
  while (1) {
    char c = this->current();
    if (is_whitespace(c)) {
      next();
      continue;
    }
    if (c == '/' && lookup_next() == '/') {
      // comment
      while (current() != '\n')
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
    if (c == '"') {
      next();
      c = current();
      std::string val;
      while (c != '"') {
        val.push_back(c);
        next();
        c = current();
      }
      next();
      TokenType t = kString;
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
      if (is_letter(c)) {
        val.push_back(c);
        std::cerr << "Unknown token: "
          << val << std::endl;
        throw std::exception();
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
