#include "statement.hpp"
#include "type_setter.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>

void type_setter_test(void) {
  std::vector<std::unique_ptr<Statement>> ast;
  ast.push_back(
    std::make_unique<VarStatement>("x")
  );
  VarStatement* x =
    static_cast<VarStatement*>(ast[0].get());
  ast.push_back(
    std::make_unique<VarStatement>(
      "y",
      std::make_unique<StringExpression>("I am string")
    )
  );
  VarStatement* y =
    static_cast<VarStatement*>(ast[1].get());
  ast.push_back(
    std::make_unique<ExpressionStatement>(
      std::make_unique<AssignExpression>(
        "x",
        std::make_unique<NumberExpression>(42)
      )
    )
  );
  TypeSetter ts(ast);
  ts.figure_out();
  if (x->data_type() != dtNumber) {
    throw std::runtime_error("`x` expected to be number");
  }
  if (y->data_type() != dtString) {
    throw std::runtime_error("`y` expected to be string");
  }
}

int main(void) {
  VarStatement st("x");
  std::cout << st << std::endl;

  if (st.data_type() != dtUnknown) {
    std::cerr << "st.data_type initialized not with dtUnknown\n";
    return -1;
  }

  st.data_type() = dtNumber;
  std::cout << st << std::endl;

  if (st.data_type() != dtNumber) {
    std::cerr << "st.data_type didn't change after assignment\n";
    return -1;
  }

  type_setter_test();

  return 0;
}
