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

VarStatement* TypeSetter::find(const std::string& var_name) const {
  if (VarStatement* ret = this->find_in_current(var_name))
    return ret;
  for (VarStatement* v : parent_scope_) {
    if (v->name() == var_name)
      return v;
  }
  return nullptr;
}

DataType TypeSetter::get_type(const Expression& expr) const {
  try {
    const NumberExpression& ne =
      dynamic_cast<const NumberExpression&>(expr);
    return dtNumber;
  } catch (std::bad_cast) {}
  try {
    const StringExpression& se =
      dynamic_cast<const StringExpression&>(expr);
    return dtString;
  } catch (std::bad_cast) {}
  try {
    const VariableExpression& ve =
      dynamic_cast<const VariableExpression&>(expr);
    VarStatement* vs = find(ve.name());
    if (vs == nullptr)
      throw std::logic_error("Use of undefined variable " + ve.name());
    DataType dt = vs->data_type();
    if (dt == dtUnknown) {
      throw std::logic_error("Using `" + ve.name() + "` uninitialized");
    }
    return dt;
  } catch (std::bad_cast) {}
  try {
    const UnaryExpression& ue =
      dynamic_cast<const UnaryExpression&>(expr);
    if (ue.oper() == kMinus) {
      if (get_type(ue.right()) != dtNumber)
        throw std::logic_error("`-` can be used only before numbers");
      return dtNumber;
    }
    else if (ue.oper() == kExcl) {
      if (get_type(ue.right()) != dtBool)
        throw std::logic_error("`!` can be used only before bools");
      return dtBool;
    }
    else {
      throw std::runtime_error(
        "Unknown unary operator " + type_to_str(ue.oper())
      );
    }
  } catch (std::bad_cast) {}
  try {
    const BinaryExpression& be =
      dynamic_cast<const BinaryExpression&>(expr);
    if (
      be.oper() == kPlus ||
      be.oper() == kMinus ||
      be.oper() == kStar ||
      be.oper() == kSlash
    ) {
      if (
        get_type(be.left()) != dtNumber ||
        get_type(be.right()) != dtNumber
      ) {
        throw std::logic_error("arithmetical operators can be used only with numbers");
      }
      return dtNumber;
    }
    else if (
      be.oper() == kEqEq ||
      be.oper() == kNEq
    ) {
      DataType dt = get_type(be.left());
      if (dt == dtUnknown) {
        throw std::logic_error("Use of uninitialized parameter");
      }
      if (dt != get_type(be.right())) {
        throw std::logic_error("`==` and `!=` can be used only with operands of the same type");
      }
      return dtBool;
    }
    else if (
      be.oper() == kLT ||
      be.oper() == kLTEQ ||
      be.oper() == kGT ||
      be.oper() == kGTEQ
    ) {
      if (
        get_type(be.left()) != dtNumber ||
        get_type(be.right()) != dtNumber
      ) {
        throw std::logic_error("Order operators may be applied only to numbers");
      }
      return dtBool;
    }
    else if (
      be.oper() == kAnd ||
      be.oper() == kOr
    ) {
      DataType dt = get_type(be.left());
      if (
        dt == dtString ||
        dt != get_type(be.right())
      ) {
        throw std::logic_error("`|`, `&` can be applied to numbers and bools of the same types");
      }
      return dt;
    }
    throw std::runtime_error("Unknown operator" + type_to_str(be.oper()));
  } catch (std::bad_cast) {}
  try {
    const AssignExpression& ae =
      dynamic_cast<const AssignExpression&>(expr);
    VarStatement* vs = find(ae.name());
    if (vs == nullptr) {
      throw std::logic_error(ae.name() + " undefined");
    }
    DataType dt = get_type(ae.value());
    if (dt == dtUnknown) {
      throw std::logic_error("Cannot assign value of unknown type");
    }
    if (vs->data_type() == dtUnknown)
      vs->data_type() = dt;
    else if (vs->data_type() != dt) {
      throw std::logic_error("Assigning value of different type");
    }
    return dt;
  } catch (std::bad_cast) {}

  throw std::runtime_error("Could not cast to any of known expression types");
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
