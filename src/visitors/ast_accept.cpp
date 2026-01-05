// ast_accept.cpp
#include "../../include/parser/ast_v1.1.hpp"
#include "../../include/visitor/visitor.hpp"

// this file glues together (runs ) the contract between ast and visitor
// every ast node passes itself as an arguemnt to visit() which is then
// dynamically dispatched correctly to the correct concrete type , due to
// polymorphism

// ===== Program / Block =====

void ProgramNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

void BlockNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

// ===== Statements =====
void ExpressionStatementNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

void VariableDeclarationNode::accept(Visitor& visitor)
{

  visitor.visit(*this);
}

void VariableAssignmentNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

// ===== Expressions =====

void BinaryExprNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

void IdentifierExprNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

// ===== Literals =====
void NumericLiteralNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

void StringLiteralNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}

void BooleanLiteralNode::accept(Visitor& visitor)
{
  visitor.visit(*this);
}
