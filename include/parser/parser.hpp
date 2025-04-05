#pragma once
#include <fstream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../include/parser/ast.hpp"
#include "../include/tokens.hpp"
#include "lexer/lexer.hpp"

class Parser {
  // things that the parser class must possess
 public:
  std::vector<Token> tokens;
  size_t current;
  Parser(const std::vector<Token> &tokens);
  std::unordered_set<TOKEN::TYPE> dataTypes;

 private:
  std::unique_ptr<ExpressionNode> ParseAssignment();
  std::unique_ptr<AstNode> ParseIdentifier();
  std::unique_ptr<AstNode> ParseProgram();
  std::unique_ptr<AstNode> ParseMain();
  std::unique_ptr<AstNode> ParseFunction();
  std::unique_ptr<ExpressionNode> ParseFunctionCall(const std::string &name);
  std::unique_ptr<AstNode> ParseBlock();
  std::unique_ptr<AstNode> ParseVariable();
  std::unique_ptr<ExpressionNode> ParseExpression();
  std::unique_ptr<ExpressionNode> ParseLogicalOR();
  std::unique_ptr<ExpressionNode> ParseLogicalAND();
  std::unique_ptr<ExpressionNode> ParseEquality();
  std::unique_ptr<ExpressionNode> ParseComparison();
  std::unique_ptr<ExpressionNode> ParseTerm();
  std::unique_ptr<ExpressionNode> ParseFactor();
  std::unique_ptr<ExpressionNode> ParseUnary();
  std::unique_ptr<ExpressionNode> ParsePrimary();
  std::unique_ptr<AstNode> ParseIf();
  std::unique_ptr<AstNode> ParseWhile();
  std::unique_ptr<AstNode> ParseFor();
  std::unique_ptr<AstNode>
  ParseReturn();  // since i have not given a specific return type this
                  // function will handle it explicitely
  Token synchronize();
  Token consumeTok();
  bool match(TOKEN::TYPE expected);
  Token peek();
  void LogError(const std::string &expected, const std::string &got, int line);
  bool consumeIfMatch(TOKEN::TYPE expected);
  void Error(const std::string &message);
};
