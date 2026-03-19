#include "expression.hpp"

#include <memory>

int main(void) {
  std::unique_ptr<Expression> expr(new NumberExpression(42));
  std::cout << *expr << std::endl;
  return 0;
}
