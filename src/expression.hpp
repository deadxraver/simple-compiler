#pragma once

#include "expression.hpp"
#include "token.hpp"

#include <string>

class Expression {
};

class NumberExpression : Expression {
private:
  double value_;
public:
  double value() const;
  NumberExpression(double);
};

class StringExpression : Expression {
private:
  std::string value_;
public:
  const std::string& value() const;
  StringExpression(const std::string&);
};

class VariableExpression : Expression {
private:
  std::string name_;
public:
  const std::string& name() const;
  VariableExpression(const std::string&);
};

class UnaryExpression : Expression {
private:
  TokenType oper_;
  Expression right_;
public:
  TokenType oper() const;
  Expression right() const;
  UnaryExpression(TokenType, Expression);
};

class BinaryExpression : Expression {
private:
  Expression left_;
  TokenType oper_;
  Expression right_;
public:
  Expression left() const;
  TokenType oper() const;
  Expression right() const;
  BinaryExpression(Expression, TokenType, Expression);
};

class AssignExpression : Expression {
private:
  std::string name_;
  Expression value_;
public:
  const std::string& name() const;
  Expression value() const;
  AssignExpression(const std::string&, Expression);
};
