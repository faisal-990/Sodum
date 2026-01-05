#pragma once

#include <memory>
#include <string>
#include <vector>

/*
MVP AST MODEL

AST
 └── Program
      └── Block
           ├── Statement
           │    └── Expression
           ├── Statement
           │    └── Expression
           └── Statement

        Expression
         ├── BinaryExpr
         │    ├── Expression
         │    └── Expression
         ├── IdentifierExpr
         └── LiteralExpr
*/

// =====================================================
// Base AST Node
// =====================================================

class Visitor;

class AstNode {
 public:
  virtual ~AstNode() = default;

  // accept takes in the visitor interface(so any concrete impelementation can
  // be passed here) and runs the relevant visit implementation function through
  // dynamic dispath(polymorphism baby)
  virtual void accept(Visitor& visitor) = 0;
};

// =====================================================
// Statements vs Expressions (Semantic Split)
// =====================================================

class StatementNode : public AstNode {};

class ExpressionNode : public AstNode {
 public:
  // this is just a wrapper class ,and no accept is required
  // accept is only present in concrete classes (expect for root(ast node
  // class))
  virtual ~ExpressionNode() = default;
};

// =====================================================
// Program & Block
// =====================================================

class BlockNode;

class ProgramNode : public AstNode {
  std::unique_ptr<BlockNode> m_body;

 public:
  explicit ProgramNode(std::unique_ptr<BlockNode> body)
      : m_body(std::move(body))
  {
  }

  // getter functions to avoid exposing privates

  BlockNode* body() const
  {
    return m_body.get();
  }

  void accept(Visitor& visitor) override;
};

// A statement may contain an expression but an expression is never a staetement
class BlockNode : public AstNode {
  std::vector<std::unique_ptr<StatementNode>> m_statements;

 public:
  explicit BlockNode(std::vector<std::unique_ptr<StatementNode>> statements)
      : m_statements(std::move(statements))
  {
  }

  // getter functions to avoid exposing privates
  const std::vector<std::unique_ptr<StatementNode>>& statements() const
  {
    return m_statements;
  }

  void accept(Visitor& visitor) override;
};

// =====================================================
// Statement Nodes
// =====================================================

// Expression used as a statement:  x + 1;
class ExpressionStatementNode : public StatementNode {
  std::unique_ptr<ExpressionNode> m_expr;

 public:
  explicit ExpressionStatementNode(std::unique_ptr<ExpressionNode> expr)
      : m_expr(std::move(expr))
  {
  }

  // getter functions to avoid exposing privates

  ExpressionNode* expr() const
  {
    return m_expr.get();
  }

  // visitor accepter method
  void accept(Visitor& visitor) override;
};

// Variable declaration: int x;  or  int x = expr;
class VariableDeclarationNode : public StatementNode {
  std::string m_name;
  std::string m_type;
  std::unique_ptr<ExpressionNode>
      m_initializer;  // may be null(variable declaration with initializer)

 public:
  VariableDeclarationNode(std::string name, std::string type,
                          std::unique_ptr<ExpressionNode> initializer = nullptr)
      : m_name(std::move(name)),
        m_type(std::move(type)),
        m_initializer(std::move(initializer))
  {
  }

  // helper getter methods to hide private memebers
  const std::string& name() const
  {
    return m_name;
  }

  const std::string& type() const
  {
    return m_type;
  }

  ExpressionNode* initializer() const
  {
    return m_initializer.get();
  }

  // visitor patterns's acceptors
  void accept(Visitor& visitor) override;
};

// Variable assignment: x = expr;
class VariableAssignmentNode : public StatementNode {
  std::string m_name;
  std::unique_ptr<ExpressionNode> m_value;

 public:
  VariableAssignmentNode(std::string name,
                         std::unique_ptr<ExpressionNode> value)
      : m_name(std::move(name)), m_value(std::move(value))
  {
  }

  const std::string& name() const
  {
    return m_name;
  }

  ExpressionNode* value() const
  {
    return m_value.get();
  }

  void accept(Visitor& visitor) override;
};

// =====================================================
// Expression Nodes
// =====================================================

enum class BinaryOperator { ADD, SUBTRACT, MULTIPLY, DIVIDE };

class BinaryExprNode : public ExpressionNode {
  BinaryOperator m_op;
  std::unique_ptr<ExpressionNode> m_lhs;
  std::unique_ptr<ExpressionNode> m_rhs;

 public:
  BinaryExprNode(BinaryOperator op, std::unique_ptr<ExpressionNode> lhs,
                 std::unique_ptr<ExpressionNode> rhs)
      : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
  {
  }

  BinaryOperator op() const
  {
    return m_op;
  }

  ExpressionNode* lhs() const
  {
    return m_lhs.get();
  }

  ExpressionNode* rhs() const
  {
    return m_rhs.get();
  }

  void accept(Visitor& visitor) override;
};

// Identifier expression: x
class IdentifierExprNode : public ExpressionNode {
  std::string m_name;

 public:
  explicit IdentifierExprNode(std::string name) : m_name(std::move(name)) {}

  const std::string& name() const
  {
    return m_name;
  }

  void accept(Visitor& visitor) override;
};

// =====================================================
// Literal Expressions
// =====================================================

class LiteralNode : public ExpressionNode {
 public:
  virtual ~LiteralNode() = default;
  // this is just a wrapper class ,and no accept is required
  // accept is only present in concrete classes (expect for root(ast node
  // class))
};

class NumericLiteralNode : public LiteralNode {
  int m_value;

 public:
  explicit NumericLiteralNode(int value) : m_value(value) {}

  int value() const
  {
    return m_value;
  }

  void accept(Visitor& visitor) override;
};

class StringLiteralNode : public LiteralNode {
  std::string m_value;

 public:
  explicit StringLiteralNode(std::string value) : m_value(std::move(value)) {}

  const std::string& value() const
  {
    return m_value;
  }

  void accept(Visitor& visitor) override;
};

class BooleanLiteralNode : public LiteralNode {
  bool m_value;

 public:
  explicit BooleanLiteralNode(bool value) : m_value(value) {}

  bool value() const
  {
    return m_value;
  }

  void accept(Visitor& visitor) override;
};
