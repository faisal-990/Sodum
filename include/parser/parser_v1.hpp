#pragma once

#include <memory>
#include <vector>

#include "../../include/tokens.hpp"
#include "../parser/ast_v1.1.hpp"

/*
  MVP grammar:

    program   → block
    block     → "{" statement* "}"
    statement → var_decl | assignment | expr_stmt
    expression→ term (("+"|"-") term)*
    term      → factor (("*"|"/") factor)*

   Program
     └── Block
          ├── Statement (variable declaration)
          ├── Statement (assignment)
          └── Statement (expression statement)

   Expression
     ├── BinaryExpr (+, -, *, /)
     ├── IdentifierExpr
     └── LiteralExpr

----------------------------------------------------
 High-level rules:
  - Everything is a program
  - A program contains exactly one block
  - A block contains zero or more statements
  - Statements MAY contain expressions
  - Expressions NEVER contain statements
----------------------------------------------------
*/

class Parser {
 public:
  Parser(const std::vector<Token>& tokens);

  // Entry point: program → block
  std::unique_ptr<ProgramNode> parseProgram();
  void display();

  bool hasError()
  {
    return m_hasError;
  }

 private:
  // passing error info to next pipeline stages

  // ---------- statements ----------
  std::unique_ptr<BlockNode> parseBlock();          // "{" statement* "}"
  std::unique_ptr<StatementNode> parseStatement();  // decides statement type

  std::unique_ptr<StatementNode> parseVariableDecl();         // int a = 10;
  std::unique_ptr<StatementNode> parseVariableAssignment();   // a = expr;
  std::unique_ptr<StatementNode> parseExpressionStatement();  // expr;

  // ---------- expressions ----------
  std::unique_ptr<ExpressionNode> parseExpression();  // + -
  std::unique_ptr<ExpressionNode> parseTerm();        // * /
  std::unique_ptr<ExpressionNode> parseFactor();      // literal | id | (...)

  // ---------- helpers ----------
  bool match(TOKEN::TYPE expected) const;
  Token peek() const;
  Token consumeTok();
  bool consumeIfMatch(TOKEN::TYPE expected);
  void Error(const std::string& message);
  bool matchAhead(int ahead, TOKEN::TYPE expected);
  void synchronize();

 private:
  std::vector<Token> m_tokens;
  size_t m_current;
  bool m_hasError = false;
};
