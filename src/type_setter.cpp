#include "type_setter.hpp"

#include <stdexcept>

TypeSetter::TypeSetter(
  std::vector<std::unique_ptr<Statement>>& ast
) : ast_(ast) {}

VarStatement* TypeSetter::find_in_current(const std::string& var_name) const {
  for (VarStatement* v : current_scope_) {
    if (v->name() == var_name)
      return v;
  }
  return nullptr;
}

DataType TypeSetter::get_type(const Expression& expr) const {
  // TODO:
  return dtUnknown;
}

void TypeSetter::parse_action(Statement* st) {
  if (
    ExpressionStatement* es =
    dynamic_cast<ExpressionStatement*>(st)
  ) {
    get_type(es->expr()); // ignore return, will throw
                          // error on semantic mistakes
                          // & fill in the uninitialized vars
  }
  else if (
    PrintStatement* ps =
    dynamic_cast<PrintStatement*>(st)
  ) {
    get_type(ps->expr());
  }
  else if (
    VarStatement* vs =
    dynamic_cast<VarStatement*>(st)
  ) {
    if (find_in_current(vs->name()))
      throw std::string("Reinitialized variable " + vs->name());
    this->current_scope_.push_back(vs);
    try {
      vs->data_type() = get_type(vs->init());
    } catch (std::logic_error err) {
      throw err;
    } catch (std::exception) {
      // not initialized, ignore
    }
  }
  else if (
    BlockStatement* bs =
    dynamic_cast<BlockStatement*>(st)
  ) {
    TypeSetter block_ts(bs->statements());
    block_ts.parent_scope_ = this->current_scope_;
    for (VarStatement* vs : this->parent_scope_) {
      if (find_in_current(vs->name()) == nullptr)
        block_ts.parent_scope_.push_back(vs);
    }
    block_ts.figure_out();
  }
  else if (
    IfStatement* is =
    dynamic_cast<IfStatement*>(st)
  ) {
    if (get_type(is->condition()) != dtBool) {
      throw std::logic_error("Expected bool in if condition");
    }
    std::vector<VarStatement*> scope = this->current_scope_;
    for (VarStatement* vs : this->parent_scope_) {
      if (find_in_current(vs->name()) == nullptr)
        scope.push_back(vs);
    }
    TypeSetter then_ts(
      static_cast<BlockStatement&>(is->then_branch()).statements()
    );
    then_ts.parent_scope_ = scope;
    then_ts.figure_out();
    try {
      TypeSetter else_ts(
        static_cast<BlockStatement&>(is->else_branch()).statements()
      );
      else_ts.parent_scope_ = scope;
      else_ts.figure_out();
    } catch (std::logic_error err) {
      throw err;
    } catch (std::exception) {}
  }
  else if (
    WhileStatement* ws =
    dynamic_cast<WhileStatement*>(st)
  ) {
    if (get_type(ws->condition()) != dtBool) {
      throw std::logic_error("Expected bool in while condition");
    }
    TypeSetter while_ts(
      static_cast<BlockStatement&>(ws->block()).statements()
    );
    while_ts.parent_scope_ = this->current_scope_;
    for (VarStatement* vs : this->parent_scope_) {
      if (find_in_current(vs->name()) == nullptr)
        while_ts.parent_scope_.push_back(vs);
    }
    while_ts.figure_out();
  }
  else {
    throw std::runtime_error("Could not cast to any of known statement types");
  }
}

void TypeSetter::figure_out() {
  for (std::size_t i = 0; i < ast_.size(); ++i) {
    this->parse_action(ast_[i].get());
  }
}
