#include "../include/lexer/lexer.hpp"
#include "../include/tokens.hpp"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

Lexer::Lexer(const std::string &source)
    : source(source), current(0), start(0), line(1) {
  // Initialize the keywordsMap inside the constructor
  keywordsMap["for"] = TOKEN::For;
  keywordsMap["if"] = TOKEN::If;
  keywordsMap["elseif"] = TOKEN::ElseIf;
  keywordsMap["else"] = TOKEN::Else;
  keywordsMap["while"] = TOKEN::While;
  keywordsMap["ret"] = TOKEN::Return;
  keywordsMap["return"] = TOKEN::Return;
  keywordsMap["break"] = TOKEN::Break;
  keywordsMap["function"] = TOKEN::Function;
  keywordsMap["int"] = TOKEN::Int;
  keywordsMap["str"] = TOKEN::String;
  keywordsMap["output"] = TOKEN::Output;
  keywordsMap["main"] = TOKEN::Main;
  keywordsMap["True"] = TOKEN::True;
  keywordsMap["False"] = TOKEN::False;
  keywordsMap["string"] = TOKEN::String;
  keywordsMap["bool"] = TOKEN::Bool;
}

bool Lexer::endReached() { return current >= source.size(); }

char Lexer::peek() { return endReached() ? '\0' : source[current]; }

char Lexer::advance() { return source[current++]; }

bool Lexer::match(char expected) {
  if (endReached() || source[current] != expected)
    return false;
  current++;
  return true;
}

void Lexer::skipWhiteSpaces() {
  while (!endReached()) {
    char c = peek();
    if (c == ' ' || c == '\t' || c == '\r') {
      advance();
    } else if (c == '\n') {
      line++;
      advance();
    } else {
      break;
    }
  }
}

void Lexer::scanIdentifier() {
  while (std::isalnum(peek()) || peek() == '_') {
    advance();
  }
  std::string text = source.substr(start, current - start);
  TOKEN::TYPE type =
      keywordsMap.count(text) ? keywordsMap[text] : TOKEN::Identifier;
  tokens.emplace_back(type, text, line);
  return;
}

void Lexer::scanNumber() {
  while (std::isdigit(peek())) {
    advance();
  }

  tokens.emplace_back(TOKEN::LiteralInt, source.substr(start, current - start),
                      line);
  return;
}

void Lexer::scanString() {
  while (peek() != '"' && !endReached()) {
    if (peek() == '\n') {
      line++;
      // i dont want to process new line
      current++;
      continue;
    }
    advance();
  }

  if (endReached()) {
    tokens.emplace_back(TOKEN::Error, "Unterminated string", line);
    return;
  }

  advance(); // Closing quote
  std::string value = source.substr(start + 1, current - start - 2);
  tokens.emplace_back(TOKEN::LiteralString, value, line);
  return;
}

void Lexer::scanTokens() {
  skipWhiteSpaces();
  start = current;

  if (endReached())
    return;

  char c = advance();

  if (std::isalpha(c) || c == '_') {
    scanIdentifier();
  } else if (std::isdigit(c)) {
    scanNumber();
  } else {
    switch (c) {
    case '(':
      tokens.emplace_back(TOKEN::Lpar, "(", line);
      break;
    case ')':
      tokens.emplace_back(TOKEN::Rpar, ")", line);
      break;
    case '{':
      tokens.emplace_back(TOKEN::Lbraces, "{", line);
      break;
    case '}':
      tokens.emplace_back(TOKEN::Rbraces, "}", line);
      break;
    case ';':
      tokens.emplace_back(TOKEN::Semicolon, ";", line);
      break;
    case '+':
      tokens.emplace_back(match('=') ? TOKEN::PlusEqual : TOKEN::Plus,
                          source.substr(start, current - start), line);
      break;
    case '-':
      tokens.emplace_back(match('=') ? TOKEN::MinusEqual : TOKEN::Minus,
                          source.substr(start, current - start), line);
      break;
    case '*':
      tokens.emplace_back(match('=') ? TOKEN::MultiplyEqual : TOKEN::Multiply,
                          source.substr(start, current - start), line);
      break;
    case '/':
      if (match('/')) {
        // Comment
        while (peek() != '\n' && !endReached())
          advance();
      } else {
        tokens.emplace_back(match('=') ? TOKEN::DivideEqual : TOKEN::Divide,
                            source.substr(start, current - start), line);
      }
      break;
    case '%':
      tokens.emplace_back(match('=') ? TOKEN::ModulusEqual : TOKEN::Modulus,
                          source.substr(start, current - start), line);
      break;
    case '>':
      tokens.emplace_back(match('=') ? TOKEN::GreaterEqual : TOKEN::Greater,
                          source.substr(start, current - start), line);
      break;
    case '<':
      tokens.emplace_back(match('=') ? TOKEN::LesserEqual : TOKEN::Lesser,
                          source.substr(start, current - start), line);
      break;
    case '!':
      tokens.emplace_back(match('=') ? TOKEN::NotEqual : TOKEN::Not,
                          source.substr(start, current - start), line);
      break;
    case '=':
      tokens.emplace_back(match('=') ? TOKEN::EqualEqual : TOKEN::Equal,
                          source.substr(start, current - start), line);
      break;
    case '|':
      tokens.emplace_back(match('|') ? TOKEN::BitwiseOr : TOKEN::Error,
                          source.substr(start, current - start), line);
      break;
    case '&':
      tokens.emplace_back(match('&') ? TOKEN::BitwiseAnd : TOKEN::Error,
                          source.substr(start, current - start), line);
      break;
    case '"':
      scanString();
      break;
    default:
      tokens.emplace_back(TOKEN::Error, std::string(1, c), line);
      break;
    }
  }
}

std::vector<Token> Lexer::lex(const std::string &source) {
  tokens.clear();
  while (!endReached()) {
    scanTokens();
  }
  tokens.emplace_back(TOKEN::Eof, "", line);
  return tokens;
}

void Lexer::display() {
  std::cout << "List of Tokens generated are:\n";
  for (const auto &token : tokens) {
    std::cout << token << '\n';
  }
  std::cout << "End of Tokens\n";
}
