#ifndef PARSER_H
#define PARSER_H

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

public:
	bool shuntingYard(const std::string& input, std::string& output);
	bool executionOrder(const std::string& input);
	double calculation(const std::string& symbol, double a, double b);

	Parser(const std::string& folder, const std::string& extension) :
		operations(std::make_unique<Operations>(folder, extension)) {};

	~Parser() = default;
	Parser(const Parser&) = default;
	Parser(Parser&&) = default;
	Parser& operator=(Parser const&) = default;
	Parser& operator=(Parser&&) = default;
};


#endif
