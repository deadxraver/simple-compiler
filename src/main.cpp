#include "main.hpp"

#include "lexer.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::string input = "var x = 123; print x + 5;";
  std::cout << "INPUT:\n" << input << std::endl;
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();
  std::cout << "OUTPUT:\n";
  for (Token& token : tokens) {
    std::cout << token.to_string() << std::endl;
  }
  return 0;
}


