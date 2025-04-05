#pragma once
#include <ostream>
#include <string>

namespace TOKEN {
enum TYPE : char {
  // keywords
  If,
  ElseIf,
  Else,
  While,
  For,
  Return,
  Break,
  Function,
  Int,
  Bool,
  String,
  Output,
  Main,

  // operators
  Plus,
  Minus,
  Multiply,
  Divide,
  Modulus,
  PlusEqual,
  MinusEqual,
  MultiplyEqual,
  DivideEqual,
  ModulusEqual,

  // logical
  EqualEqual,
  NotEqual,
  Not,
  Greater,
  Smaller,
  GreaterEqual,
  LesserEqual,
  Lesser,

  // assignment
  Equal,

  // bitwise
  BitwiseAnd,
  BitwiseOr,
  // BitwiseNot, already implemented in logical section

  // boolean
  True,
  False,

  // Delemitters
  Lpar,  //(
  Rpar,  //)
  Lbraces,
  Rbraces,

  Semicolon,
  Comma,

  // Identifiers
  Identifier,

  // comments
  SingleLineComments,

  // literals
  LiteralInt,
  LiteralBoolean,
  LiteralString,

  // error
  Error,
  UnknownToken,

  // end
  Eof,

};

}

class Token {
 public:
  TOKEN::TYPE type;
  std::string lexeme;
  int line = -1;

  // Constructor
  Token(TOKEN::TYPE type, std::string lexeme, int line)
      : type(type), lexeme(lexeme), line(line) {}

  static std::string token_to_string(TOKEN::TYPE token) {
    switch (token) {
      // Keywords
      case TOKEN::If:
        return "if";
      case TOKEN::ElseIf:
        return "elseif";
      case TOKEN::Else:
        return "else";
      case TOKEN::While:
        return "while";
      case TOKEN::For:
        return "for";
      case TOKEN::Return:
        return "return";
      case TOKEN::Break:
        return "break";
      case TOKEN::Function:
        return "function";
      case TOKEN::Int:
        return "int";
      case TOKEN::Bool:
        return "bool";
      case TOKEN::String:
        return "string";
      case TOKEN::Output:
        return "output";
      case TOKEN::Main:
        return "main";

      // Operators
      case TOKEN::Plus:
        return "+";
      case TOKEN::Minus:
        return "-";
      case TOKEN::Multiply:
        return "*";
      case TOKEN::Divide:
        return "/";
      case TOKEN::Modulus:
        return "%";
      case TOKEN::PlusEqual:
        return "+=";
      case TOKEN::MinusEqual:
        return "-=";
      case TOKEN::MultiplyEqual:
        return "*=";
      case TOKEN::DivideEqual:
        return "/=";
      case TOKEN::ModulusEqual:
        return "%=";

      // Logical
      case TOKEN::EqualEqual:
        return "==";
      case TOKEN::NotEqual:
        return "!=";
      case TOKEN::Not:
        return "!";
      case TOKEN::Greater:
        return ">";
      case TOKEN::Smaller:
        return "<";
      case TOKEN::GreaterEqual:
        return ">=";
      case TOKEN::LesserEqual:
        return "<=";
      case TOKEN::Lesser:
        return "<";

      // Assignment
      case TOKEN::Equal:
        return "=";

      // Bitwise
      case TOKEN::BitwiseAnd:
        return "&";
      case TOKEN::BitwiseOr:
        return "|";

      // Boolean
      case TOKEN::True:
        return "true";
      case TOKEN::False:
        return "false";

      // Delimiters
      case TOKEN::Lpar:
        return "(";
      case TOKEN::Rpar:
        return ")";
      case TOKEN::Lbraces:
        return "{";
      case TOKEN::Rbraces:
        return "}";
      case TOKEN::Semicolon:
        return ";";
      case TOKEN::Comma:
        return ",";
      // Identifiers
      case TOKEN::Identifier:
        return "identifier";

      // Comments
      case TOKEN::SingleLineComments:
        return "//";

      // Literals
      case TOKEN::LiteralInt:
        return "int literal";
      case TOKEN::LiteralBoolean:
        return "boolean literal";
      case TOKEN::LiteralString:
        return "string literal";

      // Error
      case TOKEN::Error:
        return "error";
      case TOKEN::UnknownToken:
        return "unknown token";

      // End of file
      case TOKEN::Eof:
        return "EOF";

      // Default case for any unrecognized token
      default:
        return "Unknown Token";
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "Lexeme: " << token.lexeme
       << ", Type: " << token_to_string(token.type) << ", Line: " << token.line;
    return os;
  }
};
