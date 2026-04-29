#pragma once

#include "statement.hpp"

#include <memory>
#include <vector>

class TypeSetter {
private:
  std::vector<std::unique_ptr<Statement>>& ast_;
  std::vector<VarStatement*> current_scope_;
  std::vector<VarStatement*> parent_scope_;
  void parse_action(Statement* st);
  VarStatement* find_in_current(const std::string& var_name) const;
  VarStatement* find(const std::string& var_name) const;
  DataType get_type(const Expression& expr) const;

public:
  void figure_out();
  TypeSetter(std::vector<std::unique_ptr<Statement>>& ast);
};
