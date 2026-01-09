// llvm dummy imports for autocomplete

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

// llvm dummy imports for autocomplete ends here
#include <llvm-18/llvm/IR/Constants.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>
#include <llvm-18/llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

#include <iostream>
#include <memory>
#include <system_error>

#include "../../include/parser/ast_v1.1.hpp"
#include "../../include/visitor/llvm_codegen.hpp"

namespace sodum {

LLVMCodeGen::LLVMCodeGen()
{
  context = std::make_unique<llvm::LLVMContext>();

  module = std::make_unique<llvm::Module>("Sodum Module", *context);

  builder = std::make_unique<llvm::IRBuilder<>>(*context);

  // creating a main wrapper (llvm function block)
  // Create the function type: ReturnType = i32, Params = none, IsVariadic =
  // false
  llvm::FunctionType* funcType = llvm::FunctionType::get(i32(), false);

  // Create the actual function in the module
  llvm::Function* mainFunc = llvm::Function::Create(
      funcType, llvm::Function::ExternalLinkage, "main", module.get());

  // creates the basic block used by progarm
  llvm::BasicBlock* entry =
      llvm::BasicBlock::Create(*context, "entry", mainFunc);

  // now the write pointer of llvm is set at entry block
  // any calls to builder class's api will write the code
  // in this block(entry)
  builder->SetInsertPoint(entry);
}

void LLVMCodeGen::compile(ProgramNode& root)
{
  // binds the program node(root of my program) , to the main function of llvm
  root.accept(*this);

  // since func currently has i32 ret type , a dummy return
  // to make the IR valid , since every functype must have a return value
  // TEMPORARY: Return the last value we encountered
  // If the last thing visited was 42, it will generate 'ret i32 42'
  if (lastValue) {
    builder->CreateRet(lastValue);
  }
  else {
    builder->CreateRet(llvm::ConstantInt::get(i32(), 0));
  }
}

// In llvm_codegen.cpp
void LLVMCodeGen::printToFile(const std::string& filename)
{
  std::error_code ec;

  // In LLVM 18, OF_None is often just 0 or accessed via fs::CD_CreateAlways
  // Using llvm::sys::fs::OF_None specifically if your version requires it,
  // but usually, we use fs::FA_Write
  llvm::raw_fd_ostream dest(filename, ec, llvm::sys::fs::OpenFlags::OF_None);

  if (ec) {
    std::cerr << "Could not open file for writing: " << ec.message()
              << std::endl;
    return;
  }

  module->print(dest, nullptr);
  dest.flush();
}

void LLVMCodeGen::print()
{
  // use our file(module) to dump the output
  module->print(llvm::outs(), nullptr);
}

void LLVMCodeGen::visit(ProgramNode& node)
{
  // highest level of the current tree

  if (node.body()) {
    // calls body
    node.body()->accept(*this);
  }
}

void LLVMCodeGen::visit(BlockNode& node)
{

  for (const auto& stm : node.statements()) {

    // calls statement
    stm->accept(*this);
  }
}

void LLVMCodeGen::visit(ExpressionStatementNode& node)
{
  if (node.expr()) {
    // calls expression
    node.expr()->accept(*this);
  }
}

void LLVMCodeGen::visit(NumericLiteralNode& node)
{
  int val = node.value();
  // wrap the data , in llvm value
  lastValue = llvm::ConstantInt::get(i32(), val);
}

void LLVMCodeGen::visit(VariableDeclarationNode& node)
{

  // Allocate space for one integer on the stack.
  llvm::AllocaInst* alloca = builder->CreateAlloca(i32(), nullptr, node.name());
  // Evaluate the initializer (the 10) if present.

  if (node.initializer()) {
    // go and calculate teh value of the initializer
    node.initializer()->accept(*this);
    // storethe value inhe alloca space
    builder->CreateStore(lastValue, alloca);
  }
  // Register the address in our namedValues map.

  namedValues[node.name()] = alloca;
}

void LLVMCodeGen::visit(VariableAssignmentNode& node)
{
  // 1. Check if the variable exists (Your logic is perfect here)
  if (namedValues.find(node.name()) == namedValues.end()) {
    std::cerr << "Runtime Error: Variable '" << node.name() << "' not declared."
              << std::endl;
    return;
  }

  // 2. Resolve the value we want to assign
  // This handles constants (10), other variables (y), or math (5 + 5)
  node.value()->accept(*this);
  llvm::Value* val = lastValue;

  // 3. Find the address and perform the update
  llvm::AllocaInst* alloca = namedValues[node.name()];
  builder->CreateStore(val, alloca);

  // Update lastValue so the parent knows the result of the assignment
  lastValue = val;
}

void LLVMCodeGen::visit(BinaryExprNode& node)
{
  // visit the lhs node
  node.lhs()->accept(*this);
  llvm::Value* L = lastValue;  // the call to lhs must fill this member

  // vist the right node
  node.rhs()->accept(*this);
  llvm::Value* R = lastValue;

  if (!R || !L) {
    return;
  }

  switch (node.op()) {
    case BinaryOperator::ADD:
      lastValue = builder->CreateAdd(L, R, "addtmp");
      break;
    case BinaryOperator::SUBTRACT:
      lastValue = builder->CreateSub(L, R, "subtmp");
      break;
    case BinaryOperator::MULTIPLY:
      lastValue = builder->CreateMul(L, R, "multmp");

      break;
    case BinaryOperator::DIVIDE:
      lastValue = builder->CreateSDiv(L, R, "divtmp");

      break;
    default:
      lastValue = nullptr;
      break;
  }
}

void LLVMCodeGen::visit(IdentifierExprNode& node)
{
  // 1. Find the memory address (the "box") in our symbol table
  llvm::AllocaInst* alloca = namedValues[node.name()];

  if (!alloca) {
    std::cerr << "Error: Undefined variable '" << node.name() << "'"
              << std::endl;
    return;
  }

  // 2. "Load" the value from that box into a virtual register
  // This turns the 'memory address' into a 'Value*' we can use in math
  lastValue = builder->CreateLoad(i32(), alloca, node.name());
}

void LLVMCodeGen::visit(StringLiteralNode& node) {}

void LLVMCodeGen::visit(BooleanLiteralNode& node) {}

}  // namespace sodum
