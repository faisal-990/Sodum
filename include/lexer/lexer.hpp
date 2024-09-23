#pragma once
#include<vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../include/tokens.hpp"

class Lexer{
	//it should take in the source file 
	std::string source;
	//it should provide a std::vector of tokens
	std::vector<Token> tokens;

	public:
	//constructor that assigns the incoming file from main.cpp
	Lexer(const std::string& source)
	: source(source) {}
	//it should have a main function that will return a std::vector of tokens
	std::vector<Token>lex();
	//start will point at the beginning of the lexeme being scanned
	//current will move
	private:


	int start=0;
	int current=0;
	int line=1;
	
	//the main lex function
	std::vector<Token> lex();
	bool endReached();
	chat peek();
	std::string advance();
	bool isNumber();
	bool isAlphabet();
	bool isAlphanumeric();
	std:: getString(std::string& source,start,end);
	void skipWhiteSpaces();
	bool match();


};

