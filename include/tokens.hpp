#pragma once

#include<string>
namespace TOKEN{
enum TYPE:char{
	//keywords
	If,
	ElseIF,
	Else,
	While,
	Return,
	Break,
	Function,
	Int,
	Output,
	Main,

	//operators
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

	//logical
	EqualEqual,
	NotEqual,
	Not,
	Greater,
	Smaller,
	GreaterEqual,
	LesserEqual,
	Lesser,


	//assignment
	Equal,


	//bitwise
	BitwiseAnd,
	BitwiseOr,
	//BitwiseNot, already implemented in logical section

	//boolean
	True,
	False,

	//Delemitters
	Lpar, //(
	Rpar, //)
	Lbraces,
	Rbraces,
	Semicolon,


	//Identifiers
	Identifier,


	//comments
	SingleLineComments,

	//literals
	NumberInt,
	Boolean,
	String,

	//error
	Error,
	UnknownToken,

	//end
	Eof,


};

}


class Token {
public:
    TOKEN::TYPE type;
    std::string lexeme;
    int line=-1;

    // Constructor
    Token(TOKEN::TYPE type, std::string lexeme, int line) 
        : type(type), lexeme(lexeme), line(line) {}
    

    // Method to convert Lexer details to string
    std::string toString() const {
        return "tokenType: " + std::to_string(static_cast<int>(type)) + 
               " lexeme: " + lexeme + 
               " lineNo.: " + std::to_string(line);
    }
};
