#pragma once
#include<vector>
#include <string>
#include <iostream>
#include <fstream>
#include<unordered_map>
#include "../include/tokens.hpp"
//**NOTE FOR ME ::
//while creating an object of the class new keyword will not be used 
//reason::new keyword allocates data on the heap which and provides a pointer //to that loaction which will have to be managed
//creating objects without new will allocate memeory in the stack which will be auto managed





class Lexer{
	//it should take in the source file 
	std::string source;
	//it should provide a std::vector of tokens
	std::vector<Token> tokens;

	public:
	//constructor that assigns the incoming file from main.cpp
	Lexer(const std::string& source);
	std::unordered_map<std::string,TOKEN::TYPE>keywordsMap;
	//it should have a main function that will return a std::vector of tokens
	std::vector<Token>lex(const std::string& source);
	//start will point at the beginning of the lexeme being scanned
	//current will move
	private:


	int start=0;
	int current=0;
	int line=1;
	
	//the main lex function
	void scanTokens();
	void scanNumber();
	void scanString();
	void scanIdentifier();
	bool endReached();
	char peek();
	char advance();
	bool isNumber(char c);
	bool isAlphabet(char c);
	bool isAlphanumeric(char c);
	std::string getString(std::string& source,int start,int current);
	void skipWhiteSpaces();
	bool match(char c);
	void displayError(std::string& buffer);
	

};


