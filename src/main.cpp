#include "main.hpp"

#include "lexer.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "No file specified!\n";
    return -1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open()) {
    std::cerr << "No such file or directory " << argv[1] << std::endl;
    return -2;
  }
  std::string input;
  for (std::string l; getline(fin, l);)
    input += l;
  fin.close();
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();
  for (Token& token : tokens) {
    std::cout << token.to_string() << std::endl;
  }
  return 0;
}


