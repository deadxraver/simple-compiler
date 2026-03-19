#pragma once

#include "expression.hpp"
#include "token.hpp"

#include <memory>
#include <string>
#include <iostream>

class Expression {
public:
  virtual void print(std::ostream&) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Expression& expression);

class NumberExpression : public Expression {
private:
  double value_;
public:
  double value() const;
  NumberExpression(double);
  virtual void print(std::ostream& os) const override {
    os << "NumberExpression{" << value_ << "}";
  }
};

class StringExpression : public Expression {
private:
  std::string value_;
public:
  const std::string& value() const;
  StringExpression(const std::string&);
  virtual void print(std::ostream& os) const override {
    os << "StringExpression{'" << value_ << "'}";
  }
};

class VariableExpression : public Expression {
private:
  std::string name_;
public:
  const std::string& name() const;
  VariableExpression(const std::string&);
  virtual void print(std::ostream& os) const override {
    os << "VariableExpression{name='" << name_ << "'}";
  }
};

class UnaryExpression : public Expression {
private:
  TokenType oper_;
  std::unique_ptr<Expression> right_;
public:
  TokenType oper() const;
  const Expression& right() const;
  UnaryExpression(TokenType, std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    const Expression& rex = *right_;
    os << "UnaryExpression{operator=" << oper_ << ",right=" << rex << "}";
  }
};

class BinaryExpression : public Expression {
private:
  std::unique_ptr<Expression> left_;
  TokenType oper_;
  std::unique_ptr<Expression> right_;
public:
  const Expression& left() const;
  TokenType oper() const;
  const Expression& right() const;
  BinaryExpression(std::unique_ptr<Expression>, TokenType, std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    os << "BinaryExpression{left=" << *left_ << ",operator=" << oper_ << ",right=" << *right_ << "}";
  }
};

class AssignExpression : public Expression {
private:
  std::string name_;
  std::unique_ptr<Expression> value_;
public:
  const std::string& name() const;
  const Expression& value() const;
  AssignExpression(const std::string&, std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    os << "AssignExpression{name='" << name_ << "',val=" << *value_ << "}";
  }
};
