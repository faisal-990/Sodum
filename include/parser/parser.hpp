#pragma once 

#include "tokens.hpp"
#include "lexer/lexer.hpp"
#include <string>
#include <map>
#include <vector>
#include <fstream>

class Parser{
	//things that the parser class must possess
	public:
		std::vector<Token>tokens;
		size_t current =0;
		Parser(std::vector<Token>tokens):
			tokens(tokens) {}
	private:
		//implemmenting a recurisve decent parser
		//each non terminal rule in the grammar will correspond to a function starting form the biggest source up
		//to the individual terminals
		
	};
