#pragma once
#include "../parser/ast_v1.1.hpp"
#include "visitor.hpp"
// LLVM Core Headers
#include <map>
#include <memory>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

namespace sodum {

class LLVMCodeGen : public Visitor {
 public:
  LLVMCodeGen();
  virtual ~LLVMCodeGen() = default;
  // Compiles the AST and returns the generated LLVM Module
  void compile(ProgramNode& root);

  // Prints the generated IR to the console
  void print();
  void printToFile(const std::string& filename);
  // --- Visitor overrides ---
  void visit(ProgramNode& node);
  void visit(BlockNode& node);

  // Statements
  void visit(ExpressionStatementNode& node);
  void visit(VariableDeclarationNode& node);
  void visit(VariableAssignmentNode& node);

  // Expressions
  void visit(BinaryExprNode& node);
  void visit(IdentifierExprNode& node);

  // Literals
  void visit(NumericLiteralNode& node);
  void visit(StringLiteralNode& node);
  void visit(BooleanLiteralNode& node);

 private:
  // The "Big Three" LLVM Infrastructure
  std::unique_ptr<llvm::LLVMContext> context;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;

  // The Result Carrier: Passes the LLVM Value* between visit calls
  llvm::Value* lastValue;

  // The Symbol Table: Maps variable names to memory locations (stack slots)
  // We use AllocaInst because we'll be using the stack for variables
  std::map<std::string, llvm::AllocaInst*> namedValues;

  // Helper: Returns the 32-bit integer type
  llvm::Type* i32()
  {
    return builder->getInt32Ty();
  }
};

}  // namespace sodum
