#pragma once

#include "Operations.h"
#include <sstream>
#include <stack>

class Parser
{
private:
	std::unique_ptr<Operations> operations;

	int opPriority(const std::string& symbol);
	bool opAssociativity(const std::string& c);
	int opBinary(const std::string& symbol);
	bool isOperator(const std::string& symbol);
	bool isFunction(const std::string& symbol);
	bool isIdent(const std::string& symbol);
	bool isIdent(char symbol);
	bool isLetter(char symbol);
	bool isLetter(const std::string& symbol);
	void parenthesesBalance(std::stack<std::string>& operations_, std::string& output);
	void operationPriorityArrangment(std::stack<std::string>& operations_, std::string& current_symbol, std::string& output);

public:
	void parse(const std::string& input, std::string& output);
	void evaluate(const std::string& input);
	double calculation(const std::string& symbol, double a, double b);

	Parser(const std::string& folder, const std::string& extension) :
		operations(std::make_unique<Operations>(folder, extension)) {};

};


