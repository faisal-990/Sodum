#include "../include/lexer/lexer.hpp"

#include <fstream>
#include <string>

#include "../include/tokens.hpp"

bool Lexer::endReached() { return current >= source.size(); }

char Lexer::peek() { return source[current]; }

char Lexer::advance() { return source[current++]; }

bool Lexer::isNumber(char c) { return (c >= '0' && c <= '9'); }

bool Lexer::isAlphabet(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isAlphanumeric(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

std::string Lexer::getString(std::string &source, int start, int current) {
  return source.substr(start, current - start);
}
// function to scan numbers
void Lexer::scanNumber() {
  while (!endReached() && isNumber(peek())) {
    advance();
  }
  std::string buffer = source.substr(start, current);
  tokens.push_back(Token(TOKEN::NumberInt, buffer, line));
}
// function to display error message
void Lexer::displayError(std::string &buffer) {
  std::cerr << "ERROR:" << buffer << std::endl;
}
// function to scan strings
void Lexer::scanString() {
  while (peek() != '"' && !endReached()) {
    if (peek() == '\n')
      line++;
    advance();
  }
  if (endReached()) {
    std::string buffer = "unterminated string";
    displayError(buffer);
    return;
  }
  advance();
  std::string buffer = source.substr(start + 1, current - 1);
  tokens.push_back(Token(TOKEN::String, buffer, line));
}
void Lexer::skipWhiteSpaces() {
  while (!endReached() && source[current] == ' ') {
    current++;
  }
}

bool Lexer::match(char expected) {
  if (endReached())
    return false;
  if (source[current] == expected) {
    current++;
    return true;
  }
  return false;
}
void Lexer::scanTokens() {
  skipWhiteSpaces();
  char ch = advance();
  // match for numbers
  if (isNumber(ch)) {
    scanNumber();
  }
  // match all the single tokens
  switch (ch) {
  case '(':
    tokens.push_back(Token(TOKEN::Lpar, "(", line));
    break;
  case ')':
    tokens.push_back(Token(TOKEN::Rpar, ")", line));
    break;
  case '{':
    tokens.push_back(Token(TOKEN::Lbraces, "{", line));
    break;
  case '}':
    tokens.push_back(Token(TOKEN::Rbraces, "}", line));
    break;
  case ';':
    tokens.push_back(Token(TOKEN::Semicolon, ";", line));
    break;
  case '+': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::PlusEqual, "+=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Plus, "+", line));
    }
    break;
  }
  case '-': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::MinusEqual, "-=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Minus, "+", line));
    }
    break;
  }
  case '*': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::MultiplyEqual, "*=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Multiply, "*", line));
    }
    break;
  }
  case '%': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::ModulusEqual, "%=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Modulus, "%", line));
    }
    break;
  }
  case '>': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::GreaterEqual, ">=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Greater, ">", line));
    }
    break;
  }
  case '<': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::LesserEqual, "<=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Lesser, "<", line));
    }
    break;
  }
  case '!': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::NotEqual, "!=", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Not, "!", line));
    }
    break;
  }
  case '=': {
    if (match('=')) {
      tokens.push_back(Token(TOKEN::EqualEqual, "==", line));
    }

    else {
      tokens.push_back(Token(TOKEN::Equal, "=", line));
    }
    break;
  }
  case '/': {
    if (match('/')) {
      // It's a single-line comment
      while (!endReached() && advance() != '\n') {
        // Do nothing, just skip the comment
      }
      // Optionally, you can increment the line number if you encounter a
      // line here
      line++; // Increment line if needed
    } else {
      if (match('=')) {
        tokens.push_back(Token(TOKEN::DivideEqual, "/=", line));
      } else {
        tokens.push_back(Token(TOKEN::Divide, "/", line));
      }
    }
    break;
  }
  case '|': {
    if (match('|')) {
      tokens.push_back(Token(TOKEN::BitwiseOr, "||", line));

    } else {
      // report error usage
      tokens.push_back(Token(TOKEN::Error, "single | usage", line));
    }
    break;
  }
  case '&': {
    if (match('&')) {
      tokens.push_back(Token(TOKEN::BitwiseAnd, "&&", line));

    } else {
      tokens.push_back(Token(TOKEN::Error, "single & usage", line));
    }
    break;
  }
    // handling literals
    // firstly handling string literals
  case '"':
    scanString();
    break;
    // numeric literals have been handled at the beginning of scanTokens()
  }
}

// the main lex function that will return the vector of tokens
std::vector<Token> Lexer::lex(const std::string &source) {
  // till the end of file is not reached keep scanning and assigning tokens
  while (!endReached()) {
    start = current;
    scanTokens();
  }
  // the end of file token
  tokens.push_back(Token(TOKEN::Eof, "", line));
  return tokens;
}
