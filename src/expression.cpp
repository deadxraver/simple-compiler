#include "expression.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& expression) {
  expression.print(os);
  return os;
}

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

const Expression& UnaryExpression::right() const {
  return *this->right_;
}

UnaryExpression::UnaryExpression(TokenType oper, std::unique_ptr<Expression> right) : oper_(oper), right_(std::move(right)) {}

const Expression& BinaryExpression::left() const {
  return *this->left_;
}

TokenType BinaryExpression::oper() const {
  return this->oper_;
}

const Expression& BinaryExpression::right() const {
  return *this->right_;
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> left, TokenType oper, std::unique_ptr<Expression> right) : left_(std::move(left)), oper_(oper), right_(std::move(right)) {}

const std::string& AssignExpression::name() const {
  return this->name_;
}

const Expression& AssignExpression::value() const {
  return *this->value_;
}

AssignExpression::AssignExpression(const std::string& name, std::unique_ptr<Expression> value) : name_(name), value_(std::move(value)) {}
