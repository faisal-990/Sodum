#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../tokens.hpp"

// mvp model
//  AST
//   └── Program
//        └── Main
//             └── Block
//                  ├── Statement
//                  │    └── Expression
//                  ├── Statement
//                  │    └── Expression
//                  └── Statement
//
//
//  Expression
//   ├── BinaryExpr
//   │    ├── Expression
//   │    └── Expression
//   ├── IdentifierExpr
//   └── LiteralExpr

// Base node class
class AstNode {
 public:
  virtual ~AstNode() = default;
  // virtual std::string String() const = 0;  // pure virtual function
};

// Program structure nodes;

class StatementNode : public AstNode {};
class BlockNode;

class ProgramNode : public AstNode {
  // std::vector<std::unique_ptr<StatementNode>> m_declarations;
  // std::unique_ptr<StatementNode> m_mainFunction;
  std::unique_ptr<BlockNode> m_body;

 public:
  //  ProgramNode(std::vector<std::unique_ptr<StatementNode>> declarations,
  //              std::unique_ptr<StatementNode> mainFunction)
  //      : m_declarations(std::move(declarations)),
  //        m_mainFunction(std::move(mainFunction))
  //  {
  ProgramNode(std::unique_ptr<BlockNode> body) : m_body(std::move(body)) {}
};

class BlockNode : public AstNode {
  std::vector<std::unique_ptr<StatementNode>> m_statements;

 public:
  BlockNode(std::vector<std::unique_ptr<StatementNode>> statements)
      : m_statements(std::move(statements)) {}
};

// Function-related nodes
// since i have mainfunction separately in program node , i can ignore this node
// for mvp class FunctionNode : public AstNode {
//  protected:
//   std::string funcName;
//   std::vector<std::pair<std::string, std::string>> parameters;  //
//   (type,name)
//
//  public:
//   FunctionNode(
//       const std::string& funcName,
//       const std::vector<std::pair<std::string, std::string>>& parameters)
//       : funcName(funcName), parameters(parameters)
//   {
//   }
// };
// v2.0 , it is a desigin choice
// whether i want to kepe main as a standalone entry point
// or any function name can be treated as an entry
// in its currently stage i am treating any function as a entry point
// because we dont yet support multiple functions , or function call
// so no point in mainting main , as of now ,
// TODO for v2.0 iterations
// class MainNode : public AstNode {
//   std::unique_ptr<BlockNode> m_block;
//
//  public:
//   MainNode(std::unique_ptr<BlockNode> block) : m_block(std::move(block)) {}
// };

// currently main is the only function being supported for mvp
//  class FunctionDeclarationNode : public FunctionNode {
//   public:
//    FunctionDeclarationNode(
//        const std::string& funcName,
//        const std::vector<std::pair<std::string, std::string>>& parameters)
//        : FunctionNode(funcName, parameters)
//    {
//    }
//  };
//
//  class FunctionDefinitionNode : public FunctionNode {
//    std::unique_ptr<BlockNode> block;
//
//   public:
//    FunctionDefinitionNode(
//        const std::string& funcName,
//        const std::vector<std::pair<std::string, std::string>>& parameters,
//        std::unique_ptr<BlockNode> block)
//        : FunctionNode(funcName, parameters), block(std::move(block))
//    {
//    }
//  };

// ExpressionNode predefinition as it is used in FunctionCallNode
class ExpressionNode : public AstNode {
 public:
  virtual ~ExpressionNode() = default;
};

// strcuture to hold expression that are statements like x+1;
class ExpressionStatementNode : public StatementNode {
  std::unique_ptr<ExpressionNode> m_expr;
};

// external functions not supported in mvps
//  class FunctionCallNode : public ExpressionNode {
//    std::string funcName;
//    std::vector<std::unique_ptr<AstNode>> arguments;
//
//   public:
//    FunctionCallNode(const std::string& funcName,
//                     std::vector<std::unique_ptr<AstNode>> arguments)
//        : funcName(funcName), arguments(std::move(arguments))
//    {
//    }
//  };

// Variable-related nodes

class VariableDeclarationNode : public StatementNode {
  std::string m_name;
  std::string m_type;
  std::unique_ptr<ExpressionNode> m_initializer;

  VariableDeclarationNode(const std::string& name, const std::string& type,
                          std::unique_ptr<ExpressionNode> initializer)
      : m_name(name), m_type(type), m_initializer(std::move(initializer)) {}
};

class VariableAssignmentNode : public StatementNode {
  std::string m_name;
  std::unique_ptr<ExpressionNode> m_value;

  VariableAssignmentNode(const std::string& name,
                         std::unique_ptr<ExpressionNode> value)
      : m_name(name), m_value(std::move(value)) {}
};

// Expression nodes
// Phase 2.0 of the mvp TODOS
// enum class AssignmentOperator {
//   ASSIGN,    // =
//   PLUS_EQ,   // +=
//   MINUS_EQ,  // -=
//   MULT_EQ,   // *=
//   DIV_EQ,    // /=
//   MOD_EQ     // %=
// };
//
// class AssignmentNode : public AstNode {
//   std::string identifier;
//   AssignmentOperator op;
//   std::unique_ptr<ExpressionNode> expression;
//
//  public:
//   const std::string getName() const
//   {
//     return identifier;
//   }
//
//   AssignmentNode(const std::string& identifier, AssignmentOperator op,
//                  std::unique_ptr<ExpressionNode> expression)
//       : identifier(identifier), op(op), expression(std::move(expression))
//   {
//   }
// };

// Control flow nodes

// class WhileNode : public AstNode {
//   std::unique_ptr<ExpressionNode> condition;
//   std::unique_ptr<BlockNode> block;
//
//  public:
//   WhileNode(std::unique_ptr<ExpressionNode> condition,
//             std::unique_ptr<BlockNode> block)
//       : condition(std::move(condition)), block(std::move(block))
//   {
//   }
// };
//
// class IfNode : public AstNode {
//   std::unique_ptr<ExpressionNode> condition;
//   std::unique_ptr<BlockNode> thenBlock;
//   std::vector<
//       std::pair<std::unique_ptr<ExpressionNode>, std::unique_ptr<BlockNode>>>
//       elseIfBlocks;
//   std::unique_ptr<BlockNode> elseBlock;
//
//  public:
//   IfNode(std::unique_ptr<ExpressionNode> condition,
//          std::unique_ptr<BlockNode> thenBlock,
//          std::vector<std::pair<std::unique_ptr<ExpressionNode>,
//                                std::unique_ptr<BlockNode>>>
//              elseIfBlocks = {},
//          std::unique_ptr<BlockNode> elseBlock = nullptr)
//       : condition(std::move(condition)),
//         thenBlock(std::move(thenBlock)),
//         elseIfBlocks(std::move(elseIfBlocks)),
//         elseBlock(std::move(elseBlock))
//   {
//   }
// };
//
// class ForNode : public AstNode {
//   std::unique_ptr<VariableNode> initialization;
//   std::unique_ptr<ExpressionNode> condition;
//   std::unique_ptr<AssignmentNode> increment;
//   std::unique_ptr<BlockNode> block;
//
//  public:
//   ForNode(std::unique_ptr<VariableNode> initialization,
//           std::unique_ptr<ExpressionNode> condition,
//           std::unique_ptr<AssignmentNode> increment,
//           std::unique_ptr<BlockNode> block)
//       : initialization(std::move(initialization)),
//         condition(std::move(condition)),
//         increment(std::move(increment)),
//         block(std::move(block))
//   {
//   }
// };

// Expression-related nodes
enum class BinaryOperator {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  // MODULO,
  // AND,
  // OR,
  // XOR,
  // EQ,
  // NEQ,
  // LT,
  // GT,
  // LTE,
  // GTE
};

class BinaryExprNode : public ExpressionNode {
  BinaryOperator m_op;
  std::unique_ptr<ExpressionNode> m_lhs;
  std::unique_ptr<ExpressionNode> m_rhs;

 public:
  BinaryExprNode(BinaryOperator op, std::unique_ptr<ExpressionNode> lhs,
                 std::unique_ptr<ExpressionNode> rhs)
      : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}
};

//
// enum class UnaryOperator {
//   NEGATE,  // -
//   NOT      // !
// };
//
// class UnaryExprNode : public ExpressionNode {
//   UnaryOperator op;
//   std::unique_ptr<ExpressionNode> operand;
//
//  public:
//   UnaryExprNode(UnaryOperator op, std::unique_ptr<ExpressionNode> operand)
//       : op(op), operand(std::move(operand))
//   {
//   }
// };
//
// Literal nodes
class LiteralNode : public ExpressionNode {
 public:
  virtual ~LiteralNode() = default;
};

class NumericLiteralNode : public LiteralNode {
  int m_value;

 public:
  NumericLiteralNode(int value) : m_value(value) {}

  int getValue() const { return m_value; }
};

class StringLiteralNode : public LiteralNode {
  std::string m_value;

 public:
  StringLiteralNode(const std::string& value) : m_value(value) {}

  const std::string& getValue() const { return m_value; }
};

class BooleanLiteralNode : public LiteralNode {
  bool m_value;

 public:
  BooleanLiteralNode(bool value) : m_value(value) {}

  bool getValue() const { return m_value; }
};

// Return statement node
// class ReturnStatementNode : public AstNode {
//   std::unique_ptr<ExpressionNode> returnValue;
//
//  public:
//   ReturnStatementNode(std::unique_ptr<ExpressionNode> returnValue = nullptr)
//       : returnValue(std::move(returnValue))
//   {
//   }
// };
// Identifier reference node
// class IdentifierNode : public ExpressionNode {
//   std::string name;
//
//  public:
//   IdentifierNode(const std::string& name) : name(name) {}
//
//   const std::string& getName() const
//   {
//     return name;
//   }
// };
