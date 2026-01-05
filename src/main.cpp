#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/lexer/lexer.hpp"
#include "../include/parser/parser_v1.hpp"
#include "../include/tokens.hpp"

int main(int argc, char* argv[])

{
  if (argc < 2) {
    std::cerr << "usage:" << argv[0] << "<source_file>" << std::endl;
    return 1;
  }
  // read the file from the disk
  std::ifstream sourceFile(argv[1]);
  if (!sourceFile.is_open()) {
    std::cerr << "Error: could not open file" << argv[1] << std::endl;
  }

  // load the file as a stream in memory
  std::stringstream buffer;

  buffer << sourceFile.rdbuf();
  // get the string object of the file

  std::string source = buffer.str();

  Lexer lexer(source);

  std::vector<Token> tokens = lexer.lex(source);
  lexer.display();

  Parser parser(tokens);

  parser.parseProgram();
  parser.display();
  return 0;
}
