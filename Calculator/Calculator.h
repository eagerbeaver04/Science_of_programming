#pragma once

#include "Parser.h"

class Calculator
{
private:
	std::unique_ptr<Parser> parser;
	std::string input;
	std::string output;

public:
	Calculator(const std::string& folder, const std::string& extension) :
		parser(std::make_unique<Parser>(folder, extension)), input(""), output("") {};

	~Calculator() = default;

	void setInput(const std::string& input_)
	{
		input = input_;
	}
	void calculation()
	{
		parser->parse(input, output);
		parser->evaluate(output);
	}

};