#include "lexer.hpp"
#include "token.hpp"

#include <string>

int main(void) {
  std::string input = "var a = 42;\n\n print a; /* comment */ a = a + 1;";
  std::vector<Token> expected = {
    Token(kVar),
    Token(kId, "a"),
    Token(kEq),
    Token(kNumber, "42"),
    Token(kSemicolon),
    Token(kPrint),
    Token(kId, "a"),
    Token(kSemicolon),
    Token(kId, "a"),
    Token(kEq),
    Token(kId, "a"),
    Token(kPlus),
    Token(kNumber, "1"),
    Token(kSemicolon),
    Token(kEOF),
  };
  Lexer lexer(input);
  std::vector<Token> res = lexer.tokenize();
  if (res.size() != expected.size()) {
    std::cerr << "Sizes do not match\n";
    return -1;
  }
  for (std::size_t i = 0; i < expected.size(); ++i) {
    if (expected[i].token_type() != res[i].token_type()) {
      std::cerr << "Assertion failed for token " << i << " type, expected " << expected[i].token_type() 
        << ", got " << res[i].token_type() << std::endl;
      return -1;
    }
    if (expected[i].token_type() == kId || expected[i].token_type() == kNumber) {
      if (expected[i].value() != res[i].value()) {
        std::cerr << "Assertion failed for token " << i << " value, expected " << expected[i] 
          << ", got: " << res[i] << std::endl;
        return -1;
      }
    }
  }
  std::cout << "OK\n";
  return 0;
}
