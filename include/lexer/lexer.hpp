#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include"../include/tokens.hpp"
class Lexer
{
	//it needs 3 basic info for each buffer
	//the token type it belongs to
	//the literal string of what is is 
	//the line number of that buffer
	public:
		TOKEN::TYPE type;
		std::string buffer_name;
		int line;
		Lexer(TOKEN::TYPE type,std::string buffer_name,int line)
		{
			this->type=type;
			this->buffer_name=buffer_name;
			this->line=line;
		}
};
