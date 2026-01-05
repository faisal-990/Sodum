// #include "../include/parser/parser.hpp"
//
// #include <iostream>
// #include <iterator>
// #include <memory>
// #include <set>
// #include <string>
// #include <utility>
// #include <vector>
//
// #include "../include/lexer/lexer.hpp"
// #include "../include/parser/ast.hpp"
// #include "../include/tokens.hpp"
//
// Parser::Parser(const std::vector<Token>& tokens) : current(0), tokens(tokens)
// {
//   dataTypes.insert(TOKEN::Int);
//   dataTypes.insert(TOKEN::Bool);
//   dataTypes.insert(TOKEN::String);
// }
//
// std::unique_ptr<AstNode> Parser::ParseProgram() {
//   std::vector<std::unique_ptr<AstNode>> nodes;
//
//   while (current < tokens.size()) {
//     if (match(TOKEN::TYPE::Main)) {
//       auto mainNode = ParseMain();
//       if (mainNode) nodes.push_back(std::move(mainNode));
//     } else if (match(TOKEN::TYPE::Int) || match(TOKEN::TYPE::Bool) ||
//
//                match(TOKEN::TYPE::String)) {
//       auto varNode = ParseVariable();
//       if (varNode) nodes.push_back(std::move(varNode));
//     } else if (match(TOKEN::TYPE::Function)) {
//       auto funcNode = ParseFunction();
//       if (funcNode) nodes.push_back(std::move(funcNode));
//     } else {
//       Error("Unexpected token at program level");
//       synchronize();
//       continue;
//     }
//
//     std::cout << "HEllo from inside the parse program function" << std::endl;
//   }
//
//   return std::make_unique<ProgramNode>(std::move(nodes));
// }
//
// std::unique_ptr<AstNode> Parser::ParseMain() {
//   consumeTok();  // consume 'main'
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lpar)) {
//     LogError("(", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rpar)) {
//     LogError(")", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lbraces)) {
//     LogError("{", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   auto block = ParseBlock();
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rbraces)) {
//     LogError("}", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   return block ? std::make_unique<MainNode>(std::move(block)) : nullptr;
// }
//
// std::unique_ptr<AstNode> Parser::ParseFunction() {
//   consumeTok();  // consume 'function'
//
//   if (!consumeIfMatch(TOKEN::TYPE::Identifier)) {
//     LogError("function name", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//   std::string funcName = tokens[current - 1].lexeme;
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lpar)) {
//     LogError("(", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   // Parse parameters
//   std::vector<std::pair<std::string, std::string>> params;
//   bool firstParam = true;
//
//   while (!match(TOKEN::TYPE::Rpar)) {
//     if (!firstParam) {
//       if (!consumeIfMatch(TOKEN::TYPE::Comma)) {
//         LogError(",", tokens[current].lexeme, tokens[current].line);
//         return nullptr;
//       }
//     }
//
//     if (dataTypes.find(tokens[current].type) == dataTypes.end()) {
//       LogError("type", tokens[current].lexeme, tokens[current].line);
//       return nullptr;
//     }
//     std::string type = tokens[current].lexeme;
//     consumeTok();
//
//     if (!consumeIfMatch(TOKEN::TYPE::Identifier)) {
//       LogError("parameter name", tokens[current].lexeme,
//       tokens[current].line); return nullptr;
//     }
//     std::string paramName = tokens[current - 1].lexeme;
//
//     params.push_back({type, paramName});
//     firstParam = false;
//   }
//
//   consumeTok();  // consume ')'
//
//   if (consumeIfMatch(TOKEN::TYPE::Semicolon)) {
//     return std::make_unique<FunctionDeclarationNode>(funcName, params);
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lbraces)) {
//     LogError("{", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   auto body = ParseBlock();
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rbraces)) {
//     LogError("}", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   return std::make_unique<FunctionDefinitionNode>(funcName, params,
//                                                   std::move(body));
// }
//
// std::unique_ptr<AstNode> Parser::ParseBlock() {
//   std::vector<std::unique_ptr<AstNode>> statements;
//
//   while (current < tokens.size() && !match(TOKEN::TYPE::Rbraces)) {
//     std::unique_ptr<AstNode> statement;
//
//     if (match(TOKEN::TYPE::Identifier)) {
//       statement = ParseIdentifier();
//     } else if (match(TOKEN::TYPE::If)) {
//       statement = ParseIf();
//     } else if (match(TOKEN::TYPE::For)) {
//       statement = ParseFor();
//     } else if (match(TOKEN::TYPE::While)) {
//       statement = ParseWhile();
//     } else if (match(TOKEN::TYPE::Return)) {
//       statement = ParseReturn();
//     } else if (dataTypes.find(tokens[current].type) != dataTypes.end()) {
//       statement = ParseVariable();
//     } else {
//       Error("Unexpected token in block");
//       synchronize();
//       continue;
//     }
//
//     if (statement) {
//       statements.push_back(std::move(statement));
//     }
//
//     if (!consumeIfMatch(TOKEN::TYPE::Semicolon) &&
//         (tokens[current].type != TOKEN::TYPE::If) &&
//         (tokens[current].type != TOKEN::TYPE::While) &&
//         (tokens[current].type != TOKEN::TYPE::For)) {
//       LogError(";", tokens[current].lexeme, tokens[current].line);
//       synchronize();
//     }
//   }
//
//   return std::make_unique<BlockNode>(std::move(statements));
// }
//
// std::unique_ptr<AstNode> Parser::ParseVariable() {
//   TOKEN::TYPE type = tokens[current].type;
//   consumeTok();  // consume type
//
//   if (!consumeIfMatch(TOKEN::TYPE::Identifier)) {
//     LogError("variable name", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//   std::string name = tokens[current - 1].lexeme;
//
//   std::unique_ptr<ExpressionNode> initializer = nullptr;
//   if (consumeIfMatch(TOKEN::TYPE::Equal)) {
//     initializer = ParseExpression();
//     if (!initializer) {
//       return nullptr;
//     }
//   } else {
//     return std::make_unique<VariableDeclarationNode>(type, name);
//   }
//
//   return std::make_unique<VariableDefinitionNode>(type, name,
//                                                   std::move(initializer));
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseExpression() {
//   return ParseAssignment();
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseAssignment() {
//   auto expr = ParseLogicalOR();
//
//   if (match(TOKEN::TYPE::Equal)) {
//     consumeTok();
//     auto value = ParseAssignment();
//     if (!value) return nullptr;
//
//     if (tokens[current].type == TOKEN::TYPE::Identifier) {
//       Error("Invalid assignment target");
//       return nullptr;
//     }
//
//     return std::make_unique<AssignmentNode>(
//         static_cast<VariableNode*>(expr.get())->getName(), std::move(value));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseLogicalOR() {
//   auto expr = ParseLogicalAND();
//
//   while (match(TOKEN::TYPE::BitwiseOr)) {
//     Token op = consumeTok();
//     auto right = ParseLogicalAND();
//     std::make_unique<BinaryExprNode>(std::move(expr), op, std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseLogicalAND() {
//   auto expr = ParseEquality();
//
//   while (match(TOKEN::TYPE::BitwiseAnd)) {
//     Token op = consumeTok();
//     auto right = ParseEquality();
//     expr =
//         std::make_unique<BinaryExprNode>(std::move(expr), op,
//         std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseEquality() {
//   auto expr = ParseComparison();
//
//   while (match(TOKEN::TYPE::Equal) || match(TOKEN::TYPE::NotEqual)) {
//     Token op = consumeTok();
//     auto right = ParseComparison();
//     expr =
//         std::make_unique<BinaryExprNode>(std::move(expr), op,
//         std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseComparison() {
//   auto expr = ParseTerm();
//
//   while (match(TOKEN::TYPE::Lesser) || match(TOKEN::TYPE::LesserEqual) ||
//          (match(TOKEN::TYPE::EqualEqual)) || (match(TOKEN::TYPE::NotEqual))
//          || match(TOKEN::TYPE::Greater) || match(TOKEN::TYPE::GreaterEqual))
//          {
//     Token op = consumeTok();
//     auto right = ParseTerm();
//     expr =
//         std::make_unique<BinaryExprNode>(std::move(expr), op,
//         std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseTerm() {
//   auto expr = ParseFactor();
//
//   while (match(TOKEN::TYPE::Plus) || match(TOKEN::TYPE::Minus)) {
//     Token op = consumeTok();
//     auto right = ParseFactor();
//     expr =
//         std::make_unique<BinaryExprNode>(std::move(expr), op,
//         std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseFactor() {
//   auto expr = ParseUnary();
//
//   while (match(TOKEN::TYPE::Multiply) || match(TOKEN::TYPE::Divide)) {
//     Token op = consumeTok();
//     auto right = ParseUnary();
//     expr =
//         std::make_unique<BinaryExprNode>(std::move(expr), op,
//         std::move(right));
//   }
//
//   return expr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseUnary() {
//   if (match(TOKEN::TYPE::Not) || match(TOKEN::TYPE::Minus)) {
//     Token op = consumeTok();
//     auto right = ParseUnary();
//     return std::make_unique<UnaryExprNode>(op, std::move(right));
//   }
//
//   return ParsePrimary();
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParsePrimary() {
//   if (match(TOKEN::TYPE::LiteralInt)) {
//     Token token = consumeTok();
//     return std::make_unique<NumericLiteralNode>(
//         std::stod(tokens[current].lexeme));
//   }
//
//   if (match(TOKEN::TYPE::String)) {
//     Token token = consumeTok();
//   }
//
//   if (match(TOKEN::TYPE::True) || match(TOKEN::TYPE::False)) {
//     Token token = consumeTok();
//     return std::make_unique<BooleanLiteralNode>(tokens[current].type ==
//                                                 TOKEN::TYPE::True);
//   }
//
//   if (match(TOKEN::TYPE::Identifier)) {
//     std::string name = tokens[current].lexeme;
//     consumeTok();
//
//     if (match(TOKEN::TYPE::Lpar)) {
//       return ParseFunctionCall(name);
//     }
//
//     return std::make_unique<VariableNode>(name);
//   }
//
//   if (match(TOKEN::TYPE::Lpar)) {
//     consumeTok();
//     auto expr = ParseExpression();
//
//     if (!consumeIfMatch(TOKEN::TYPE::Rpar)) {
//       LogError(")", tokens[current].lexeme, tokens[current].line);
//       return nullptr;
//     }
//
//     return expr;
//   }
//
//   Error("Expected expression");
//   return nullptr;
// }
//
// std::unique_ptr<ExpressionNode> Parser::ParseFunctionCall(
//     const std::string& name) {
//   consumeTok();  // consume '('
//
//   std::vector<std::unique_ptr<ExpressionNode>> arguments;
//   bool firstArg = true;
//
//   while (!match(TOKEN::TYPE::Rpar)) {
//     if (!firstArg) {
//       if (!consumeIfMatch(TOKEN::TYPE::Comma)) {
//         LogError(",", tokens[current].lexeme, tokens[current].line);
//         return nullptr;
//       }
//     }
//
//     auto arg = ParseExpression();
//     if (!arg) return nullptr;
//
//     arguments.push_back(std::move(arg));
//     firstArg = false;
//   }
//
//   consumeTok();  // consume ')'
//
//   return std::make_unique<FunctionCallNode>(name, std::move(arguments));
// }
//
// std::unique_ptr<AstNode> Parser::ParseIf() {
//   consumeTok();  // Consume "if"
//
//   if (!match(TOKEN::TYPE::Lpar)) {
//     LogError("Expected '(' after 'if'", tokens[current].lexeme,
//              tokens[current].line);
//     synchronize();
//     return nullptr;
//   }
//   consumeTok();
//
//   auto ifCondition = ParseExpression();
//   if (!ifCondition) {
//     return nullptr;
//   }
//
//   if (!match(TOKEN::TYPE::Rpar)) {
//     LogError("Expected ')' after condition", tokens[current].lexeme,
//              tokens[current].line);
//     synchronize();
//     return nullptr;
//   }
//   consumeTok();
//
//   if (!match(TOKEN::TYPE::Lbraces)) {
//     LogError("Expected '{' after if condition", tokens[current].lexeme,
//              tokens[current].line);
//     synchronize();
//     return nullptr;
//   }
//   consumeTok();
//
//   auto thenBlock = ParseBlock();
//   if (!thenBlock) {
//     return nullptr;
//   }
//
//   std::vector<
//       std::pair<std::unique_ptr<ExpressionNode>, std::unique_ptr<AstNode>>>
//       elseIfBlocks;
//
//   while (match(TOKEN::TYPE::ElseIf)) {
//     consumeTok();
//
//     if (!match(TOKEN::TYPE::Lpar)) {
//       LogError("Expected '(' after 'else if'", tokens[current].lexeme,
//                tokens[current].line);
//       synchronize();
//       return nullptr;
//     }
//     consumeTok();
//
//     auto elseIfCondition = ParseExpression();
//     if (!elseIfCondition) {
//       return nullptr;
//     }
//
//     if (!match(TOKEN::TYPE::Rpar)) {
//       LogError("Expected ')' after else-if condition",
//       tokens[current].lexeme,
//                tokens[current].line);
//       synchronize();
//       return nullptr;
//     }
//     consumeTok();
//
//     if (!match(TOKEN::TYPE::Lbraces)) {
//       LogError("Expected '{' after else-if condition",
//       tokens[current].lexeme,
//                tokens[current].line);
//       synchronize();
//       return nullptr;
//     }
//     consumeTok();
//
//     auto elseIfBlock = ParseBlock();
//     if (!elseIfBlock) {
//       return nullptr;
//     }
//
//     elseIfBlocks.emplace_back(std::move(elseIfCondition),
//                               std::move(elseIfBlock));
//   }
//
//   std::unique_ptr<AstNode> elseBlock;  // Changed from BlockNode to AstNode
//   if (match(TOKEN::TYPE::Else)) {
//     consumeTok();
//
//     if (!match(TOKEN::TYPE::Lbraces)) {
//       LogError("Expected '{' after 'else'", tokens[current].lexeme,
//                tokens[current].line);
//       synchronize();
//       return nullptr;
//     }
//     consumeTok();
//
//     elseBlock = ParseBlock();
//     if (!elseBlock) {
//       return nullptr;
//     }
//   }
//
//   return std::make_unique<IfNode>(std::move(ifCondition),
//   std::move(thenBlock),
//                                   std::move(elseIfBlocks),
//                                   std::move(elseBlock));
// }
//
// std::unique_ptr<AstNode> Parser::ParseWhile() {
//   consumeTok();  // consume 'while'
//   if (!consumeIfMatch(TOKEN::TYPE::Lpar)) {
//     LogError("(", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   auto condition = ParseExpression();
//   if (!condition) return nullptr;
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rpar)) {
//     LogError(")", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lbraces)) {
//     LogError("{", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   auto body = ParseBlock();
//   if (!body) return nullptr;
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rbraces)) {
//     LogError("}", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   return std::make_unique<WhileNode>(std::move(condition), std::move(body));
// }
//
// std::unique_ptr<AstNode> Parser::ParseFor() {
//   consumeTok();  // consume 'for'
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lpar)) {
//     LogError("(", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   // Initializer
//   std::unique_ptr<AstNode> initializer = nullptr;
//   if (!match(TOKEN::TYPE::Semicolon)) {
//     if (match(TOKEN::TYPE::Int) || match(TOKEN::TYPE::Bool) ||
//         match(TOKEN::TYPE::String)) {
//       initializer = ParseVariable();
//     } else {
//       initializer = ParseExpression();
//     }
//
//     if (!initializer) return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Semicolon)) {
//     LogError(";", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   // Condition
//   std::unique_ptr<ExpressionNode> condition = nullptr;
//   if (!match(TOKEN::TYPE::Semicolon)) {
//     condition = ParseExpression();
//     if (!condition) return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Semicolon)) {
//     LogError(";", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   // Increment
//   std::unique_ptr<ExpressionNode> increment = nullptr;
//   if (!match(TOKEN::TYPE::Rpar)) {
//     increment = ParseExpression();
//     if (!increment) return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rpar)) {
//     LogError(")", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   if (!consumeIfMatch(TOKEN::TYPE::Lbraces)) {
//     LogError("{", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   auto body = ParseBlock();
//   if (!body) return nullptr;
//
//   if (!consumeIfMatch(TOKEN::TYPE::Rbraces)) {
//     LogError("}", tokens[current].lexeme, tokens[current].line);
//     return nullptr;
//   }
//
//   return std::make_unique<ForNode>(std::move(initializer),
//   std::move(condition),
//                                    std::move(increment), std::move(body));
// }
//
// std::unique_ptr<AstNode> Parser::ParseReturn() {
//   consumeTok();  // consume 'return'
//
//   std::unique_ptr<ExpressionNode> value = nullptr;
//   if (!match(TOKEN::TYPE::Semicolon)) {
//     value = ParseExpression();
//     if (!value) return nullptr;
//   }
//
//   return std::make_unique<ReturnNode>(std::move(value));
// }
//
// std::unique_ptr<AstNode> Parser::ParseIdentifier() {
//   std::string name = tokens[current].lexeme;
//   consumeTok();  // consume identifier
//
//   if (match(TOKEN::TYPE::Lpar)) {
//     auto funcCall = ParseFunctionCall(name);
//     if (!funcCall) return nullptr;
//     return std::make_unique<ExpressionStatementNode>(std::move(funcCall));
//   }
//
//   if (match(TOKEN::TYPE::Equal)) {
//     consumeTok();  // consume '='
//     auto value = ParseExpression();
//     if (!value) return nullptr;
//     return std::make_unique<AssignmentNode>(name, std::move(value));
//   }
//
//   Error("Expected function call or assignment");
//   return nullptr;
// }
//
// // for graceful error/unknown token handling
// // this helps the parser recover from error and come into a sane state
// // where parsing can resume
// void Parser::synchronize() {
//   consumeTok();
//
//   while (current < tokens.size()) {
//     if (tokens[current - 1].type == TOKEN::TYPE::Semicolon) return;
//
//     switch (tokens[current].type) {
//       case TOKEN::TYPE::Function:
//       case TOKEN::TYPE::If:
//       case TOKEN::TYPE::While:
//       case TOKEN::TYPE::For:
//       case TOKEN::TYPE::Return:
//       case TOKEN::TYPE::Int:
//       case TOKEN::TYPE::Bool:
//       case TOKEN::TYPE::String:
//         return;
//       default:
//         consumeTok();
//     }
//   }
// }
//
// // Helper methods implementations
// bool Parser::match(TOKEN::TYPE type) {
//   if (current >= tokens.size()) return false;
//   return tokens[current].type == type;
// }
//
// Token Parser::peek() {
//   if (current + 1 >= tokens.size()) {
//     return Token{TOKEN::TYPE::Eof, "", tokens[current].line};
//   }
//   return tokens[current + 1];
// }
//
// Token Parser::consumeTok() {
//   if (current >= tokens.size()) {
//     return Token{TOKEN::TYPE::Eof, "", tokens.back().line};
//   }
//   return tokens[current++];
// }
//
// bool Parser::consumeIfMatch(TOKEN::TYPE type) {
//   if (match(type)) {
//     consumeTok();
//     return true;
//   }
//   return false;
// }
//
// void Parser::LogError(const std::string& expected, const std::string& got,
//                       int line) {
//   std::cerr << "Expected '" << expected << "' at line " << line
//             << " but got
//       '" << got << "' instead\n ";
// }
//
// void Parser::Error(const std::string& message) {
//   std::cerr << "Error: " << message << " at line " << tokens[current].line
//             << "\n";
// }
