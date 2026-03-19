#include "expression.hpp"
#include "statement.hpp"

#include <memory>

int main(void) {
  std::vector<std::unique_ptr<Statement>> blk;
  blk.push_back(
    std::unique_ptr<Statement>(
      new VarStatement(
        "x",
        std::unique_ptr<Expression>(
          new NumberExpression(42)
        )
      )
    )
  );
  blk.push_back(
    std::unique_ptr<Statement>(
      new PrintStatement(
        std::unique_ptr<Expression>(
          new VariableExpression("x")
        )
      )
    )
  );
  std::unique_ptr<Statement> st(new BlockStatement(std::move(blk)));
  std::cout << *st << std::endl;
  return 0;
}
