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
  case '>': {
    if (match('=')) {
      tokens.push_back(new Token(TOKEN::GreaterEqual, ">=", line));
    }

    else {
      tokens.push_back(new Token(TOKEN::Greater, ">", line));
    }
    break;
  }
  case '<': {
    if (match('=')) {
      tokens.push_back(new Token(TOKEN::LesserEqual, "<=", line));
    }

    else {
      tokens.push_back(new Token(TOKEN::Lesser, "<", line));
    }
    break;
  }
  case '!': {
    if (match('=')) {
      tokens.push_back(new Token(TOKEN::NotEqual, "!=", line));
    }

    else {
      tokens.push_back(new Token(TOKEN::Not, "!", line));
    }
    break;
  }
  case '=': {
    if (match('=')) {
      tokens.push_back(new Token(TOKEN::EqualEqual, "==", line));
    }

    else {
      tokens.push_back(new Token(TOKEN::Equal, "=", line));
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
      // newline here
      line++; // Increment line if needed
    } else {
      if (match('=')) {
        tokens.push_back(new Token(TOKEN::DivideEqual, "/=", line));
      } else {
        tokens.push_back(new Token(TOKEN::Divide, "/", line));
      }
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
  // the end of file token
  tokens.push_back(new Token(TOKEN::EOF, ""));
  return tokens;
}
