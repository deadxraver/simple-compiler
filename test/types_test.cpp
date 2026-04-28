#include "statement.hpp"

#include <iostream>

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

  return 0;
}
