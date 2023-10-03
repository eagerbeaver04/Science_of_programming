#ifndef SORTER_H
#define SORTER_H

#include "Operations.h"
#include <sstream>
#include <stack>

class Parser
{
public:
	bool shuntingYard(const std::string& input, std::string& output);
	bool executionOrder(const std::string& input);
	double calculation(const std::string& symbol, double a, double b);
	~Parser() 
	{
		delete  operations;
	}
	Parser()
	{
		this->operations = new Operations();
	}
	Parser(const std::string& folder, const std::string& extension)
	{
		this->operations = new Operations(folder, extension);
	}
private:
	Operations* operations;
	Parser(const Parser&);
	int opPriority(const std::string& symbol);
	bool opAssociativity(const std::string& c);
	int opBinary(const std::string& symbol);
	bool isOperator(const std::string& symbol);
	bool isFunction(const std::string& symbol);
	bool isIdent(const std::string& symbol);
	bool isIdent(char symbol);
	bool isLetter(char symbol);
	bool isLetter(const std::string& symbol);

};


#endif
