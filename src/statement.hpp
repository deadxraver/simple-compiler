#pragma once

#include "expression.hpp"

#include <vector>

class Statement {
};

class ExpressionStatement : Statement {
private:
  Expression expr_;
public:
  Expression expr() const;
  ExpressionStatement(Expression);
};

class PrintStatement : Statement {
private:
  Expression expr_;
public:
  Expression expr() const;
  PrintStatement(Expression);
};

class VarStatement : Statement {
private:
  std::string name_;
  Expression init_;
public:
  const std::string& name() const;
  Expression init() const;
  VarStatement(const std::string&, Expression);
};

class BlockStatement : Statement {
private:
  std::vector<Statement> statements_;
public:
  const std::vector<Statement>& statements() const;
  BlockStatement(const std::vector<Statement>&);
};

class IfStatement : Statement {
private:
  Expression condition_;
  BlockStatement then_branch_;
  BlockStatement else_branch_;
public:
  Expression condition() const;
  BlockStatement then_branch() const;
  BlockStatement else_branch() const;
  IfStatement(Expression, BlockStatement, BlockStatement);
};

class WhileStatement : Statement {
private:
  Expression condition_;
  BlockStatement block_;
public:
  Expression condition() const;
  BlockStatement block() const;
  WhileStatement(Expression, BlockStatement);
};
