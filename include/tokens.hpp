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
	Start,

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

	//logical
	EqualEqual,
	NotEqual,
	Greater,
	Smaller,
	GreaterEqual,
	LesserEqual,


	//assignment
	Equal,


	//bitwise
	BitwiseAnd,
	BitwiseOr,
	BitwiseNot,

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
	Char,
	String,

	//error
	Error,
	UnknownToken,

	//end
	Eof,


};

}

