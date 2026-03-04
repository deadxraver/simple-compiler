#include "parser.hpp"

Parser::Parser(const std::vector<Token>& tokens) : tokens_(tokens), pos_(0) {}

void Parser::next() {
  ++(this->pos_);
}

Token Parser::current() const {
  return this->tokens_[this->pos_];
}

bool Parser::is_eof() const {
  return this->current().token_type() == kEOF;
}

std::vector<Statement> Parser::parse() {
  std::vector<Statement> result;
  while(!this->is_eof()) {
    // TODO: parser logic
    this->next();
  }
  return result;
}
