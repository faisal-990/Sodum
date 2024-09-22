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
	std::vector<Token> lex();
};

