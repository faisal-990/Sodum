#include "../include/parser/parser_v1.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/tokens.hpp"

Parser::Parser(const std::vector<Token>& token) : m_tokens(token), m_current(0)
{
  std::cout << "parser_v1 constructor initialized" << std::endl;
}

// helper methods for parser
Token Parser::consumeTok()
{
  if (m_current >= m_tokens.size()) return Token{TOKEN::TYPE::Eof, "", -1};
  return m_tokens[m_current++];
}

bool Parser::matchAhead(int ahead, TOKEN::TYPE expected)
{
  if (m_current + ahead >= m_tokens.size()) return false;

  return m_tokens[m_current + ahead].type == expected;
}

bool Parser::match(TOKEN::TYPE expected) const
{
  if (m_current >= m_tokens.size()) {
    if (TOKEN::TYPE::Eof) return true;
    return false;
  }
  return m_tokens[m_current].type == expected;
}

void Parser::Error(const std::string& message)
{
  int line = -1;

  if (m_current < m_tokens.size())
    line = m_tokens[m_current].line;
  else if (!m_tokens.empty())
    line = m_tokens.back().line;

  std::cerr << "Error: " << message << " at line " << line << std::endl;
}

void Parser::synchronize()
{
  while (m_current <= m_tokens.size()) {
    switch (m_tokens[m_current].type) {
      case TOKEN::TYPE::Semicolon:
        consumeTok();  // consume ';'
        return;

      case TOKEN::TYPE::Rbraces:
        return;  // let parseBlock handle it

      case TOKEN::TYPE::Int:
      case TOKEN::TYPE::Bool:
      case TOKEN::TYPE::String:
        return;  // new statement boundary

      default:
        consumeTok();  // DISCARD junk
    }
  }
}

void Parser::display()
{
  std::cout << "HELLO FROM Parser display , ready to print the entire ast tree";
}

// helper implementation ends here
// Xxxxxxxxxxxxxxxxxx-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*
    parseExpression:
  left = parseTerm()
  while (+ or -):
    left = new Binary(left, parseTerm())

parseTerm:
  left = parseFactor()
  while (* or /):
    left = new Binary(left, parseFactor())

parseFactor:
  literal OR ( expression )


  expression → term (("+" | "-") term)*
term       → factor (("*" | "/") factor)*
factor     → INT | "(" expression ")"


 */

std::unique_ptr<ExpressionNode> Parser::parseFactor()
{
  std::cout << "INSIDE THE parseFactor block\n";

  if (match(TOKEN::TYPE::LiteralInt)) {
    Token tok = consumeTok();
    return std::make_unique<NumericLiteralNode>(std::stoi(tok.lexeme));
  }

  if (match(TOKEN::TYPE::Lpar)) {
    consumeTok();  // consume '('

    auto expr = parseExpression();

    if (!match(TOKEN::TYPE::Rpar)) {
      Error("expected ')'");
      return nullptr;
    }

    consumeTok();  // consume ')'
    return expr;
  }

  Error("invalid factor");
  return nullptr;
}

std::unique_ptr<ExpressionNode> Parser::parseTerm()
{
  auto left = parseFactor();

  while (match(TOKEN::TYPE::Multiply) || match(TOKEN::TYPE::Divide)) {
    if (match(TOKEN::TYPE::Multiply)) {
      consumeTok();
      left = std::make_unique<BinaryExprNode>(
          BinaryOperator::MULTIPLY, std::move(left), std::move(parseFactor()));
    }
    else {
      consumeTok();
      left = std::make_unique<BinaryExprNode>(
          BinaryOperator::DIVIDE, std::move(left), std::move(parseFactor()));
    }
  }
  return left;
}

std::unique_ptr<ExpressionNode> Parser::parseExpression()
{
  std::cout << "INSIDE THE parseExpression block" << "\n";

  auto left = parseTerm();

  while (match(TOKEN::TYPE::Plus) || match(TOKEN::TYPE::Minus)) {
    if (match(TOKEN::TYPE::Plus)) {
      consumeTok();
      left = std::make_unique<BinaryExprNode>(
          BinaryOperator::ADD, std::move(left), std::move(parseTerm()));
    }
    else {
      consumeTok();
      left = std::make_unique<BinaryExprNode>(
          BinaryOperator::SUBTRACT, std::move(left), std::move(parseTerm()));
    }
  }

  return left;
}

std::unique_ptr<StatementNode> Parser::parseStatement()
{
  std::cout << "INSIDE THE parseStatement method" << "\n";

  // 1. Variable declaration (int x; | int x = expr;)
  if (match(TOKEN::TYPE::Int)) {
    consumeTok();  // consume 'int'

    Token name = consumeTok();  // identifier
    if (name.type != TOKEN::TYPE::Identifier) {
      Error("expected identifier after type");
      consumeTok();
      synchronize();
      return nullptr;
    }

    std::unique_ptr<ExpressionNode> initializer = nullptr;

    if (match(TOKEN::TYPE::Equal)) {
      consumeTok();  // '='
      initializer = parseExpression();
    }

    if (!match(TOKEN::TYPE::Semicolon)) {
      Error("expected ';' after variable declaration");
      consumeTok();
      synchronize();

      return nullptr;
    }
    consumeTok();  // ';'

    return std::make_unique<VariableDeclarationNode>(name.lexeme, "int",
                                                     std::move(initializer));
  }

  // 2. Assignment (x = expr;)
  if (match(TOKEN::TYPE::Identifier) && matchAhead(1, TOKEN::TYPE::Equal)) {

    Token name = consumeTok();  // identifier
    consumeTok();               // '='

    auto value = parseExpression();

    if (!match(TOKEN::TYPE::Semicolon)) {
      Error("expected ';' after assignment");

      consumeTok();
      synchronize();

      return nullptr;
    }
    consumeTok();  // ';'

    return std::make_unique<VariableAssignmentNode>(name.lexeme,
                                                    std::move(value));
  }

  // 3. Expression statement (expr;)
  auto expr = parseExpression();

  if (!match(TOKEN::TYPE::Semicolon)) {
    Error("expected ';' after expression");
    consumeTok();
    synchronize();

    return nullptr;
  }
  consumeTok();  // ';'

  return std::make_unique<ExpressionStatementNode>(std::move(expr));
}

std::unique_ptr<BlockNode> Parser::parseBlock()
{
  std::cout << "INSIDE THE parseBlock method" << "\n";
  // consume the { token
  consumeTok();
  std::vector<std::unique_ptr<StatementNode>> statements;

  while (m_tokens[m_current].type != TOKEN::TYPE::Rbraces) {
    statements.push_back(parseStatement());
  }
  // consume the } brace
  consumeTok();
  return std::make_unique<BlockNode>(std::move(statements));
}

std::unique_ptr<ProgramNode> Parser::parseProgram()
{
  std::cout << "INSIDE THE parseProgram method" << "\n";
  // parse and create a node object , and then typecast and return
  std::unique_ptr<BlockNode> body = parseBlock();
  // This is the point where the object is initialized and linked to its parent
  return std::make_unique<ProgramNode>(std::move(body));
}
