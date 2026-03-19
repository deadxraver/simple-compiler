#include "main.hpp"

#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "No file specified!\n";
    return -EINVAL;
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open()) {
    std::cerr << "No such file or directory " << argv[1] << std::endl;
    return -ENOENT;
  }
  std::string input;
  for (std::string l; getline(fin, l);) {
    input += l;
    input.push_back('\n');
  }
  fin.close();
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();
  std::cout << "TOKENS:\n";
  for (Token& token : tokens) {
    std::cout << token << std::endl;
  }
  std::cout << "STATEMENTS:\n";
  Parser parser(tokens);
  std::vector<std::unique_ptr<Statement>> statements = parser.parse();
  for (const std::unique_ptr<Statement>& ptr : statements) {
    std::cout << *ptr << std::endl;
  }
  return 0;
}


