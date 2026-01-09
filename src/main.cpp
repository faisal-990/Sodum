#include <cstdlib>
#include <filesystem>  // For cleanup
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/lexer/lexer.hpp"
#include "../include/parser/parser_v1.hpp"
#include "../include/tokens.hpp"
#include "../include/visitor/ast_visitor.hpp"
#include "../include/visitor/llvm_codegen.hpp"

using namespace sodum;

// Helper to find whatever compiler is available
std::string findSystemCompiler()
{
  for (const auto& c : {"clang", "gcc", "cc"}) {
    std::string check = "which " + std::string(c) + " > /dev/null 2>&1";
    if (std::system(check.c_str()) == 0) return c;
  }
  return "";
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
    return 1;
  }

  std::ifstream sourceFile(argv[1]);
  if (!sourceFile.is_open()) {
    std::cerr << "Error: could not open file " << argv[1] << std::endl;
    return 1;
  }

  std::stringstream buffer;
  buffer << sourceFile.rdbuf();
  std::string source = buffer.str();

  // --- LEXING ---
  Lexer lexer(source);
  std::vector<Token> tokens = lexer.lex(source);
  // lexer.display();  // Optional debug output

  // --- PARSING ---
  Parser parser(tokens);
  auto ast = parser.parseProgram();

  // GATEKEEPER: Stop if the parser found errors
  if (parser.hasError() || !ast) {
    std::cerr << "\033[1;31m[Error]\033[0m Parser failed. Aborting compilation."
              << std::endl;
    return 1;
  }

  // optional to see the ast printed
  // AstPrinter astprinter(std::cout);
  //
  // ast->accept(astprinter);

  // --- CODEGEN ---
  LLVMCodeGen codegen;
  codegen.compile(*ast);

  // --- DRIVER & AUTOMATION ---
  std::string irFile = "output.ll";
  std::string binFile = "sodum_out";

  // 1. Write IR to disk
  codegen.printToFile(irFile);

  // 2. Identify the toolchain
  std::string compiler = findSystemCompiler();
  if (compiler.empty()) {
    std::cerr << "Error: No native compiler (clang/gcc) found in PATH."
              << std::endl;
    return 1;
  }

  // 3. Compile to native binary
  std::string compileCmd = compiler + " " + irFile + " -o " + binFile;
  std::cout << "[Step 1] Compiling via " << compiler << "..." << std::endl;

  int res = std::system(compileCmd.c_str());

  if (res == 0) {
    // Cleanup: Remove the .ll file to keep the folder clean
    std::filesystem::remove(irFile);

    std::cout << "\033[1;32m[Success]\033[0m Build complete: ./" << binFile
              << std::endl;
    std::cout << "Running result check..." << std::endl;

    // Directly run and show the exit code
    std::string runCmd =
        "./" + binFile + "; echo 'Program exited with code: ' $?";
    std::system(runCmd.c_str());
  }
  else {
    std::cerr << "\033[1;31m[Error]\033[0m Native compilation failed."
              << std::endl;
    return 1;
  }

  return 0;
}
