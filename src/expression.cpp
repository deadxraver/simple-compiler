#include "expression.hpp"

double NumberExpression::value() const {
  return this->value_;
}

NumberExpression::NumberExpression(double value) : value_(value) {}

const std::string& StringExpression::value() const {
  return this->value_;
}

StringExpression::StringExpression(const std::string& value) : value_(value) {}

const std::string& VariableExpression::name() const {
  return this->name_;
}

VariableExpression::VariableExpression(const std::string& name) : name_(name) {}

TokenType UnaryExpression::oper() const {
  return this->oper_;
}

Expression UnaryExpression::right() const {
  return this->right_;
}

UnaryExpression::UnaryExpression(TokenType oper, Expression right) : oper_(oper), right_(right) {}

Expression BinaryExpression::left() const {
  return this->left_;
}

TokenType BinaryExpression::oper() const {
  return this->oper_;
}

Expression BinaryExpression::right() const {
  return this->right_;
}

BinaryExpression::BinaryExpression(Expression left, TokenType oper, Expression right) : left_(left), oper_(oper), right_(right) {}

const std::string& AssignExpression::name() const {
  return this->name_;
}

Expression AssignExpression::value() const {
  return this->value_;
}

AssignExpression::AssignExpression(const std::string& name, Expression value) : name_(name), value_(value) {}
