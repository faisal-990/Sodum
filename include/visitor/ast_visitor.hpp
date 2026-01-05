// ast_visitor.hpp
#pragma once

#include <ostream>

#include "visitor.hpp"

class AstPrinter : public Visitor {
 public:
  explicit AstPrinter(std::ostream& out);

  // Program / Block
  void visit(ProgramNode& node) override;
  void visit(BlockNode& node) override;

  // Statements
  void visit(ExpressionStatementNode& node) override;
  void visit(VariableDeclarationNode& node) override;
  void visit(VariableAssignmentNode& node) override;

  // Expressions
  void visit(BinaryExprNode& node) override;
  void visit(IdentifierExprNode& node) override;

  // Literals
  void visit(NumericLiteralNode& node) override;
  void visit(StringLiteralNode& node) override;
  void visit(BooleanLiteralNode& node) override;

 private:
  std::ostream&
      m_out;  // to print wherever specified (eg, cout,filestream,stringstream)
  int m_indent;

  void printIndent();
};
