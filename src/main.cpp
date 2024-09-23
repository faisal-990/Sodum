#include "../include/lexer/lexer.hpp"
#include "../include/parser/parser.hpp"
#include "../include/tokens.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
int main(int argc, char *argv[])

{
  if (argc > 2) {
    std::cerr << "wrong format for input" << std::endl;
    std::cerr << "correct format is ./main {file_name}" << std::endl;
  } else if (argc < 2) {
    std::cerr << "less number of arguments" << std::endl;
    std::cerr << "correct format is ./{main_file} {file_name}" << std::endl;
  } else {
    // Open the file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << argv[1] << std::endl;
      return 1;
    }

    // Read the file contents into a string
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the entire file into the buffer
    std::string fileContent = buffer.str();

    // Close the file (optional, as it will close automatically)
    Lexer lexer(argv[1]);
    file.close();
    std::cout << fileContent << std::endl;
  }
}
