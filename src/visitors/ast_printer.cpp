// ast_printer.cpp

#include "../../include/parser/ast_v1.1.hpp"
#include "../../include/visitor/ast_visitor.hpp"

// Constructor
AstPrinter::AstPrinter(std::ostream& out) : m_out(out), m_indent(0) {}

// Helper
void AstPrinter::printIndent()
{
  m_out << "|";
  for (int i = 0; i < m_indent; ++i) m_out << "-";
  m_out << ">";
}

// ================= Program / Block =================

void AstPrinter::visit(ProgramNode& node)
{
  m_out << "Program\n";
  m_indent++;
  node.body()->accept(*this);
  m_indent--;
}

void AstPrinter::visit(BlockNode& node)
{
  printIndent();
  m_out << "Block\n";

  m_indent++;
  for (auto& stmt : node.statements()) {
    stmt->accept(*this);
  }
  m_indent--;
}

// ================= Statements =================

void AstPrinter::visit(ExpressionStatementNode& node)
{
  printIndent();
  m_out << "ExprStmt\n";

  m_indent++;
  node.expr()->accept(*this);
  m_indent--;
}

void AstPrinter::visit(VariableDeclarationNode& node)
{
  printIndent();
  m_out << "VarDecl " << node.type() << " " << node.name() << "\n";

  if (node.initializer()) {
    m_indent++;
    node.initializer()->accept(*this);
    m_indent--;
  }
}

void AstPrinter::visit(VariableAssignmentNode& node)
{
  printIndent();
  m_out << "Assign " << node.name() << "\n";

  m_indent++;
  node.value()->accept(*this);
  m_indent--;
}

// ================= Expressions =================

void AstPrinter::visit(BinaryExprNode& node)
{
  printIndent();
  m_out << "BinaryExpr\n,";
  m_indent++;
  node.lhs()->accept(*this);
  node.rhs()->accept(*this);
  m_indent--;
}

void AstPrinter::visit(IdentifierExprNode& node)
{
  printIndent();
  m_out << "Identifier " << node.name() << "\n";
}

// ================= Literals =================

void AstPrinter::visit(NumericLiteralNode& node)
{
  printIndent();
  m_out << "Number " << node.value() << "\n";
}

void AstPrinter::visit(StringLiteralNode& node)
{
  printIndent();
  m_out << "String \"" << node.value() << "\"\n";
}

void AstPrinter::visit(BooleanLiteralNode& node)
{
  printIndent();
  m_out << "Boolean " << (node.value() ? "true" : "false") << "\n";
}
