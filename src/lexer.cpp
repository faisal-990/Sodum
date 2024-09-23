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
  return source.substr(start, end);
}

void Lexer::skipWhiteSpaces() {
  while (source[current] == '') {
    current++;
  }
}

bool Lexer::match(char expected) {
  if (endReached()) return false;
  if (source[current] == expected) {
    current++;
    return true;
  }
  return false;
}
void scanTokens() {
  skipWhiteSpaces();
  char ch = advance();
  // match all the single tokens
  switch (ch) {
    case '(':
      tokens.push_back(new Token(TOKEN::Lpar, "(", line));
      break;
    case ')':
      tokens.push_back(new Token(TOKEN::Rpar, ")", line));
      break;
    case '{':
      tokens.push_back(new Token(TOKEN::Lbraces, "{", line));
      break;
    case '}':
      tokens.push_back(new Token(TOKEN::Rbraces, "}", line));
      break;
    case ';':
      tokens.push_back(new Token(TOKEN::Semicolon, ";", line));
      break;
    case '+': {
      if (match('=')) {
        tokens.push_back(new Token(TOKEN::PlusEqual, "+=", line));
      }

      else {
        tokens.push_back(new Token(TOKEN::Plus, "+", line));
      }
      break;
    }
    case '-': {
      if (match('=')) {
        tokens.push_back(new Token(TOKEN::MinusEqual, "-=", line));
      }

      else {
        tokens.push_back(new Token(TOKEN::Minus, "+", line));
      }
      break;
    }
    case '*': {
      if (match('=')) {
        tokens.push_back(new Token(TOKEN::MultiplyEqual, "*=", line));
      }

      else {
        tokens.push_back(new Token(TOKEN::Multiply, "*", line));
      }
      break;
    }
    case '%': {
      if (match('=')) {
        tokens.push_back(new Token(TOKEN::ModulusEqual, "%=", line));
      }

      else {
        tokens.push_back(new Token(TOKEN::Modulus, "%", line));
      }
      break;
    }
  }
}

// the main lex function that will return the vector of tokens
std::vector<Token> Lexer::lex(const std::string &source) {
  // till the end of file is not reached keep scanning and assigning tokens
  while (!endReached()) {
    start = current;
    scanTokens();
  }
}
