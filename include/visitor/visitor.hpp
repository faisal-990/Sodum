// visitor.hpp
#pragma once

// this file contains the interface/skeleton of all visitors ,
// all concrete implementations of different features implements this parent
// interface

// Forward declarations ONLY (no includes)
class ProgramNode;
class BlockNode;

class ExpressionStatementNode;
class VariableDeclarationNode;
class VariableAssignmentNode;

class BinaryExprNode;
class IdentifierExprNode;

class NumericLiteralNode;
class StringLiteralNode;
class BooleanLiteralNode;

class Visitor {
 public:
  virtual ~Visitor() = default;
  // visit for all types of node available in ast node structure
  virtual void visit(ProgramNode& node) = 0;  //?? why we do this 0, and default

  virtual void visit(BlockNode& node) = 0;
  virtual void visit(ExpressionStatementNode& node) = 0;

  virtual void visit(VariableDeclarationNode& node) = 0;
  virtual void visit(VariableAssignmentNode& node) = 0;
  virtual void visit(BinaryExprNode& node) = 0;
  virtual void visit(IdentifierExprNode& node) = 0;
  virtual void visit(NumericLiteralNode& node) = 0;
  virtual void visit(StringLiteralNode& node) = 0;
  virtual void visit(BooleanLiteralNode& node) = 0;
};
