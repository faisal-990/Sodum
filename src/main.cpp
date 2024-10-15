#include "../include/lexer/lexer.hpp"
#include "../include/parser/parser.hpp"
#include "../include/tokens.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
int main(int argc, char *argv[])

{
  if (argc < 2) {
    std::cerr << "usage:" << argv[0] << "<source_file>" << std::endl;
    return 1;
  }
  std::ifstream sourceFile(argv[1]);
  if (!sourceFile.is_open()) {
    std::cerr << "Error: could not open file" << argv[1] << std::endl;
  }
  std::stringstream buffer;
  buffer << sourceFile.rdbuf();
  std::string source = buffer.str();

  Lexer lexer(source);
  std::vector<Token> tokens = lexer.lex(source);
  lexer.display();
  return 0;
}
