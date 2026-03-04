#include "main.hpp"

#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <string>

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
  for (std::string l; getline(fin, l);)
    input += l;
  fin.close();
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();
  std::cout << "TOKENS:\n";
  for (Token& token : tokens) {
    std::cout << token << std::endl;
  }
  std::cout << "STATEMENTS:\n";
  Parser parser(tokens);
  std::vector<Statement> statements = parser.parse();
  // TODO: print
  return 0;
}


