#include "statement.hpp"

std::ostream& operator<<(std::ostream& os, const Statement& statement) {
  statement.print(os);
  return os;
}

const Expression& ExpressionStatement::expr() const {
  return *this->expr_;
}

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expr) : expr_(std::move(expr)) {}

const Expression& PrintStatement::expr() const {
  return *this->expr_;
}

PrintStatement::PrintStatement(std::unique_ptr<Expression> expr) : expr_(std::move(expr)) {}

const std::string& VarStatement::name() const {
  return this->name_;
}

const Expression& VarStatement::init() const {
  return *this->init_;
}

VarStatement::VarStatement(const std::string& name, std::unique_ptr<Expression> init) : name_(name), init_(std::move(init)) {}

const std::vector<std::unique_ptr<Statement>>& BlockStatement::statements() const {
  return this->statements_;
}

BlockStatement::BlockStatement(std::vector<std::unique_ptr<Statement>> statements) : statements_(std::move(statements)) {}

const Expression& IfStatement::condition() const {
  return *this->condition_;
}

const BlockStatement& IfStatement::then_branch() const {
  return this->then_branch_;
}

const BlockStatement& IfStatement::else_branch() const {
  return this->else_branch_;
}

IfStatement::IfStatement(std::unique_ptr<Expression> condition, BlockStatement then_branch, BlockStatement else_branch) : condition_(std::move(condition)), then_branch_(std::move(then_branch)), else_branch_(std::move(else_branch)) {}

const Expression& WhileStatement::condition() const {
  return *this->condition_;
}

const BlockStatement& WhileStatement::block() const {
  return this->block_;
}

WhileStatement::WhileStatement(std::unique_ptr<Expression> condition, BlockStatement block) : condition_(std::move(condition)), block_(std::move(block)) {}
