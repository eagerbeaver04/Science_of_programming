#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Parser.h"

class Calculator 
{
public:
	static Calculator* getInstance(const std::string& folder, const std::string& extension)
	{
		static Calculator* instance = new Calculator(folder, extension);
		return instance;
	}
	void setInput(const std::string& input)
	{
		this->input = input;
	}
	void calculation()
	{
		if (this->parser->shuntingYard(this->input, this->output))
			this->parser->executionOrder(this->output);
	}
private:
	Parser* parser;
	std::string input;
	std::string output;
	Calculator(const std::string& folder, const std::string& extension)
	{
		this->parser = new Parser(folder, extension);
		this->input = "";
		this->output = "";
	};
	~Calculator() 
	{
		delete parser;
	};
	Calculator(const Calculator&);
	Calculator& operator= (const Calculator&) {};
};

#endif