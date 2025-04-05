#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../tokens.hpp"

// Base node class
class AstNode {
 public:
  virtual ~AstNode() = default;
};

// Program structure nodes
class BlockNode;  // Forward declaration

class ProgramNode : public AstNode {
  std::vector<std::unique_ptr<AstNode>> declarations;
  std::unique_ptr<AstNode> mainFunction;

 public:
  ProgramNode(std::vector<std::unique_ptr<AstNode>> declarations,
              std::unique_ptr<AstNode> mainFunction)
      : declarations(std::move(declarations)),
        mainFunction(std::move(mainFunction)) {}
};

class BlockNode : public AstNode {
  std::vector<std::unique_ptr<AstNode>> statements;

 public:
  BlockNode(std::vector<std::unique_ptr<AstNode>> statements)
      : statements(std::move(statements)) {}
};

// Function-related nodes
class FunctionNode : public AstNode {
 protected:
  std::string funcName;
  std::vector<std::pair<std::string, std::string>> parameters;  // (type, name)

 public:
  FunctionNode(
      const std::string& funcName,
      const std::vector<std::pair<std::string, std::string>>& parameters)
      : funcName(funcName), parameters(parameters) {}
};

class MainNode : public AstNode {
  std::unique_ptr<BlockNode> block;

 public:
  MainNode(std::unique_ptr<BlockNode> block) : block(std::move(block)) {}
};

class FunctionDeclarationNode : public FunctionNode {
 public:
  FunctionDeclarationNode(
      const std::string& funcName,
      const std::vector<std::pair<std::string, std::string>>& parameters)
      : FunctionNode(funcName, parameters) {}
};

class FunctionDefinitionNode : public FunctionNode {
  std::unique_ptr<BlockNode> block;

 public:
  FunctionDefinitionNode(
      const std::string& funcName,
      const std::vector<std::pair<std::string, std::string>>& parameters,
      std::unique_ptr<BlockNode> block)
      : FunctionNode(funcName, parameters), block(std::move(block)) {}
};
// ExpressionNode predefinition as it is used in FunctionCallNode

class ExpressionNode : public AstNode {
 public:
  virtual ~ExpressionNode() = default;
};

class FunctionCallNode : public ExpressionNode {
  std::string funcName;
  std::vector<std::unique_ptr<AstNode>> arguments;

 public:
  FunctionCallNode(const std::string& funcName,
                   std::vector<std::unique_ptr<AstNode>> arguments)
      : funcName(funcName), arguments(std::move(arguments)) {}
};

// Variable-related nodes
class VariableNode : public ExpressionNode {
 protected:
  std::string identifier;
  std::string type;

 public:
  VariableNode(const std::string& identifier, const std::string& type)
      : identifier(identifier), type(type) {}
  const std::string getName() { return identifier; }
};

class VariableDeclarationNode : public VariableNode {
 public:
  VariableDeclarationNode(const std::string& identifier,
                          const std::string& type)
      : VariableNode(identifier, type) {}
};

class VariableDefinitionNode : public VariableNode {
  std::unique_ptr<AstNode> expression;

 public:
  VariableDefinitionNode(const std::string& identifier, const std::string& type,
                         std::unique_ptr<AstNode> expression)
      : VariableNode(identifier, type), expression(std::move(expression)) {}
};

// Expression nodes

enum class AssignmentOperator {
  ASSIGN,    // =
  PLUS_EQ,   // +=
  MINUS_EQ,  // -=
  MULT_EQ,   // *=
  DIV_EQ,    // /=
  MOD_EQ     // %=
};

class AssignmentNode : public AstNode {
  std::string identifier;
  AssignmentOperator op;
  std::unique_ptr<ExpressionNode> expression;

 public:
  const std::string getName() const { return identifier; }
  AssignmentNode(const std::string& identifier, AssignmentOperator op,
                 std::unique_ptr<ExpressionNode> expression)
      : identifier(identifier), op(op), expression(std::move(expression)) {}
};

// Control flow nodes

class WhileNode : public AstNode {
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<BlockNode> block;

 public:
  WhileNode(std::unique_ptr<ExpressionNode> condition,
            std::unique_ptr<BlockNode> block)
      : condition(std::move(condition)), block(std::move(block)) {}
};
class IfNode : public AstNode {
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<BlockNode> thenBlock;
  std::vector<
      std::pair<std::unique_ptr<ExpressionNode>, std::unique_ptr<BlockNode>>>
      elseIfBlocks;
  std::unique_ptr<BlockNode> elseBlock;

 public:
  IfNode(std::unique_ptr<ExpressionNode> condition,
         std::unique_ptr<BlockNode> thenBlock,
         std::vector<std::pair<std::unique_ptr<ExpressionNode>,
                               std::unique_ptr<BlockNode>>>
             elseIfBlocks = {},
         std::unique_ptr<BlockNode> elseBlock = nullptr)
      : condition(std::move(condition)),
        thenBlock(std::move(thenBlock)),
        elseIfBlocks(std::move(elseIfBlocks)),
        elseBlock(std::move(elseBlock)) {}
};

class ForNode : public AstNode {
  std::unique_ptr<VariableNode> initialization;
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<AssignmentNode> increment;
  std::unique_ptr<BlockNode> block;

 public:
  ForNode(std::unique_ptr<VariableNode> initialization,
          std::unique_ptr<ExpressionNode> condition,
          std::unique_ptr<AssignmentNode> increment,
          std::unique_ptr<BlockNode> block)
      : initialization(std::move(initialization)),
        condition(std::move(condition)),
        increment(std::move(increment)),
        block(std::move(block)) {}
};

// Expression-related nodes
enum class BinaryOperator {
  ADD,       // +
  SUBTRACT,  // -
  MULTIPLY,  // *
  DIVIDE,    // /
  MODULO,    // %
  AND,       // &&
  OR,        // ||
  XOR,       // ^
  EQ,        // ==
  NEQ,       // !=
  LT,        // <
  GT,        // >
  LTE,       // <=
  GTE        // >=
};

class BinaryExprNode : public ExpressionNode {
  BinaryOperator op;
  std::unique_ptr<ExpressionNode> lhs;
  std::unique_ptr<ExpressionNode> rhs;

 public:
  BinaryExprNode(BinaryOperator op, std::unique_ptr<ExpressionNode> lhs,
                 std::unique_ptr<ExpressionNode> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

enum class UnaryOperator {
  NEGATE,  // -
  NOT      // !
};

class UnaryExprNode : public ExpressionNode {
  UnaryOperator op;
  std::unique_ptr<ExpressionNode> operand;

 public:
  UnaryExprNode(UnaryOperator op, std::unique_ptr<ExpressionNode> operand)
      : op(op), operand(std::move(operand)) {}
};

// Literal nodes
class LiteralNode : public ExpressionNode {
 public:
  virtual ~LiteralNode() = default;
};

class NumericLiteralNode : public LiteralNode {
  int value;

 public:
  NumericLiteralNode(int value) : value(value) {}
  int getValue() const { return value; }
};

class StringLiteralNode : public LiteralNode {
  std::string value;

 public:
  StringLiteralNode(const std::string& value) : value(value) {}
  const std::string& getValue() const { return value; }
};

class BooleanLiteralNode : public LiteralNode {
  bool value;

 public:
  BooleanLiteralNode(bool value) : value(value) {}
  bool getValue() const { return value; }
};

// Return statement node
class ReturnStatementNode : public AstNode {
  std::unique_ptr<ExpressionNode> returnValue;

 public:
  ReturnStatementNode(std::unique_ptr<ExpressionNode> returnValue = nullptr)
      : returnValue(std::move(returnValue)) {}
};

// Identifier reference node
class IdentifierNode : public ExpressionNode {
  std::string name;

 public:
  IdentifierNode(const std::string& name) : name(name) {}
  const std::string& getName() const { return name; }
};
