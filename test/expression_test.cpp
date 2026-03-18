#include "expression.hpp"

int main(void) {
  Expression expr = NumberExpression(42);
  std::cout << expr << std::endl;
  return 0;
}
