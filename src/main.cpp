#include "main.hpp"

#include "lexer.hpp"
#include "parser.hpp"
#include "type_setter.hpp"

#include "object/version.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

void print_help(char* path) {
  std::cout << "Usage: " << path;
  std::cout << " { -h | --help } | { --version } |";
  std::cout << " { <input_file> [ -o <output_file> ] [ -v | --verbose ] }";
  std::cout << std::endl;

  std::cout << "\t-h | --help\t\t:\tprint this message & quit\n";
  std::cout << "\t--version\t\t:\tprint version & quit\n";
  std::cout << "\t<input_file>\t\t:\tfile containg source code\n";
  std::cout << "\t-o <output_file>\t:\toutput object file, if not specified, ./a.out will be used\n";
  std::cout << "\t-v | --verbose\t\t:\tprint verbose info such as tokens & ast\n";
}

void print_version(void) {
  std::cout << "simple-compiler: " << VERSION_STR << std::endl;
}

int main(int argc, char* argv[]) {
  cl_args args(argc, argv);

  if (args.help_only) {
    print_help(argv[0]);
    return 0;
  }

  if (args.version_only) {
    print_version();
    return 0;
  }

  std::ifstream fin(args.file_path);
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
  if (args.verbose) {
    std::cout << "TOKENS:\n";
    for (Token& token : tokens) {
      std::cout << token << std::endl;
    }
  }
  Parser parser(tokens);
  std::vector<std::unique_ptr<Statement>> statements;
  try {
    statements = parser.parse();
  } catch(std::string err) {
    std::cerr << "Error while parsing: " << err << std::endl;
  }

  TypeSetter ts(statements);
  try {
    ts.figure_out();
  } catch (std::logic_error err) {
    std::cerr << err.what() << std::endl;
    return -EINVAL;
  } catch (std::string err) {
    std::cerr << err << std::endl;
    return -EINVAL;
  }

  if (args.verbose) {
    std::cout << "STATEMENTS:\n";
    for (const std::unique_ptr<Statement>& ptr : statements) {
      std::cout << *ptr << std::endl;
    }
  }

  return 0;
}


