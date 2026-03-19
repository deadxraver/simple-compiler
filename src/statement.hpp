#pragma once

#include "expression.hpp"

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
public:
  const std::string& name() const;
  const Expression& init() const;
  VarStatement(const std::string&, std::unique_ptr<Expression>);
  virtual void print(std::ostream& os) const override {
    os << "VarStatement{name='" << name_ << "',val=" << *init_ << "}";
  }
};

class BlockStatement : public Statement {
private:
  std::vector<std::unique_ptr<Statement>> statements_;
public:
  const std::vector<std::unique_ptr<Statement>>& statements() const;
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
  BlockStatement then_branch_;
  BlockStatement else_branch_;
public:
  const Expression& condition() const;
  const BlockStatement& then_branch() const;
  const BlockStatement& else_branch() const;
  IfStatement(std::unique_ptr<Expression>, BlockStatement, BlockStatement);
  virtual void print(std::ostream& os) const override {
    os << "IfStatement{cond=" << *condition_ << ",then=" << then_branch_ << "else=" << else_branch_ << "}";
  }
};

class WhileStatement : public Statement {
private:
  std::unique_ptr<Expression> condition_;
  BlockStatement block_;
public:
  const Expression& condition() const;
  const BlockStatement& block() const;
  WhileStatement(std::unique_ptr<Expression>, BlockStatement);
  virtual void print(std::ostream& os) const override {
    os << "WhileStatement{cond=" << *condition_ << ",block=" << block_ << "}";
  }
};
