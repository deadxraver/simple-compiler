#include "statement.hpp"

Expression ExpressionStatement::expr() const {
  return this->expr_;
}

ExpressionStatement::ExpressionStatement(Expression expr) : expr_(expr) {}

Expression PrintStatement::expr() const {
  return this->expr_;
}

PrintStatement::PrintStatement(Expression expr) : expr_(expr) {}

const std::string& VarStatement::name() const {
  return this->name_;
}

Expression VarStatement::init() const {
  return this->init_;
}

VarStatement::VarStatement(const std::string& name, Expression init) : name_(name), init_(init) {}

const std::vector<Statement>& BlockStatement::statements() const {
  return this->statements_;
}

BlockStatement::BlockStatement(const std::vector<Statement>& statements) : statements_(statements) {}

Expression IfStatement::condition() const {
  return this->condition_;
}

BlockStatement IfStatement::then_branch() const {
  return this->then_branch_;
}

BlockStatement IfStatement::else_branch() const {
  return this->else_branch_;
}

IfStatement::IfStatement(Expression condition, BlockStatement then_branch, BlockStatement else_branch) : condition_(condition), then_branch_(then_branch), else_branch_(else_branch) {}

Expression WhileStatement::condition() const {
  return this->condition_;
}

BlockStatement WhileStatement::block() const {
  return this->block_;
}

WhileStatement::WhileStatement(Expression condition, BlockStatement block) : condition_(condition), block_(block) {}
