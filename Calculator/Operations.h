#pragma once

#include "Loader.h"

class Operations
{

private:
	std::map<std::string, std::unique_ptr<Operator>> operations;
	Loader loader;
public:
	Operations()
	{
		operations["+"] = std::make_unique<Operator>("+", 1, true, 2, [](double a, double b) { return a + b; });
		operations["-"] = std::make_unique<Operator>("-", 1, true, 2, [](double a, double b) { return a - b; });
		operations["*"] = std::make_unique<Operator>("*", 2, true, 2, [](double a, double b) { return a * b; });
		operations["/"] = std::make_unique<Operator>("/", 2, true, 2, [](double a, double b) {
			if (b)
				return a / b;
			throw std::runtime_error("Unavaliable operation: Division by zero"); });
		loader = Loader();
	};
	Operations(const std::string& folder, const std::string& extension) : Operations()
	{
		if (folder != "" && extension != "")
		{
			loader = Loader(folder, extension);
			loader.loadDll(operations, folder, extension);
		}
		else
			std::cerr << std::endl << "Folder for extra operations is not download" << std::endl;
	};

	int getPriority(const std::string& symbol);
	bool getAssociativity(const std::string& symbol);
	int getBinary(const std::string& symbol);

	double calculation(const std::string& symbol, double a, double b);

	~Operations() = default;
	Operations(const Operations&) = default;
	Operations(Operations&&) = default;
	Operations& operator = (const Operations&) = default;
	Operations& operator = (Operations&&) = default;

};

