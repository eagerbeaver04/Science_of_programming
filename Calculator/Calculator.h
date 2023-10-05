#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Parser.h"

class Calculator
{
private:
	std::unique_ptr<Parser> parser;
	std::string input;
	std::string output;
public:
	Calculator(const std::string& folder, const std::string& extension)
	{
		this->parser = std::make_unique<Parser>(folder, extension);
		this->input = "";
		this->output = "";
	};
	~Calculator() = default;
	Calculator() = default;
	Calculator(const Calculator&) = default;
	Calculator(Calculator&&) = default;
	Calculator& operator=(Calculator const&) = default;
	Calculator& operator=(Calculator&&) = default;

	void setInput(const std::string& input)
	{
		this->input = input;
	}
	void calculation()
	{
		if (this->parser->shuntingYard(this->input, this->output))
			this->parser->executionOrder(this->output);
	}
};

#endif