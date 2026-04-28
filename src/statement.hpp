#pragma once

#include "expression.hpp"
#include "data_type.hpp"

#include <vector>
#include <memory>
#include <iostream>

class Statement {
public:
  virtual void print(std::ostream&) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Statement& statement);

class ExpressionStatement : public Statement {
private:
  std::unique_ptr<Expression> expr_;
public:
  const Expression& expr() const;
  ExpressionStatement(std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    os << "ExpressionStatement{" << *expr_ << "}";
  }
};

class PrintStatement : public Statement {
private:
  std::unique_ptr<Expression> expr_;
public:
  const Expression& expr() const;
  PrintStatement(std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    os << "PrintStatement{" << *expr_ << "}";
  }
};

class VarStatement : public Statement {
private:
  std::string name_;
  std::unique_ptr<Expression> init_;
  DataType data_type_;
public:
  const std::string& name() const;
  const Expression& init() const;
  DataType& data_type();
  VarStatement(const std::string&, std::unique_ptr<Expression> init = nullptr);
  virtual void print(std::ostream& os) const override {
    os << "VarStatement{name='" << name_ << "',type:" << data_type_ << ",val=";
    if (init_ == nullptr)
      os << "{uninitialized}";
    else
      os << *init_;
    os << "}";
  }
};

class BlockStatement : public Statement {
private:
  std::vector<std::unique_ptr<Statement>> statements_;
public:
  std::vector<std::unique_ptr<Statement>>& statements();
  BlockStatement(std::vector<std::unique_ptr<Statement>>);
  virtual void print(std::ostream& os) const override {
    os << "BlockStatement{";
    for (const std::unique_ptr<Statement>& ptr : statements_) {
      Statement& st = *ptr;
      os << st << ",";
    }
    os << "}";
  }
};

class IfStatement : public Statement {
private:
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Statement> then_branch_;
  std::unique_ptr<Statement> else_branch_;
public:
  const Expression& condition() const;
  Statement& then_branch();
  Statement& else_branch();
  IfStatement(std::unique_ptr<Expression>, std::unique_ptr<Statement>, std::unique_ptr<Statement>);
  virtual void print(std::ostream& os) const override {
    os << "IfStatement{cond=" << *condition_ << ",then=" << *then_branch_;
    if (else_branch_ != nullptr)
      os << "else=" << *else_branch_;
    os << "}";
  }
};

class WhileStatement : public Statement {
private:
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Statement> block_;
public:
  const Expression& condition() const;
  Statement& block();
  WhileStatement(std::unique_ptr<Expression>, std::unique_ptr<Statement>);
  virtual void print(std::ostream& os) const override {
    os << "WhileStatement{cond=" << *condition_ << ",block=" << *block_ << "}";
  }
};
