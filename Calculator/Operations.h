#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Loader.h"

static double sum(double a, double b)
{
	return a + b;
}

static double sub(double a, double b)
{
	return a - b;
}

static double mul(double a, double b)
{
	return a * b;
}

static double div_(double a, double b)
{
	if (b)
		return a / b;
	std::cerr << std::endl <<"Unavaliable operation: Division by zero"  << std::endl;
	return a;
}

class Operations
{
public:
	Operations()
	{
		this->operations["+"] = new Operator("+", 1, true, 2, sum);
		this->operations["-"] = new Operator("-", 1, true, 2, sub);
		this->operations["*"] = new Operator("*", 2, true, 2, mul);
		this->operations["/"] = new Operator("/", 2, true, 2, div_);
	};
	Operations(const std::string& folder, const std::string& extension): Operations()
	{
		Loader* loader = Loader::getInstance(folder, extension);
		loader->loadDll(this->operations, folder, extension);
	};

	int getPriority(const std::string& symbol);
	bool getAssociativity(const std::string& symbol);
	int getBinary(const std::string& symbol);

	double ñalculation(const std::string& symbol, double a, double b);
	~Operations() 
	{
		for (auto& op : operations)
			delete op.second;
		operations.clear();
	}
private:
	std::map<std::string, Operator*> operations;
};

#endif
