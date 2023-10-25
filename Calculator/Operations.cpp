#include "Operations.h"

int Operations::getPriority(const std::string& symbols)
{
	if (operations.count(symbols) == 0)
		throw std::runtime_error("Unavaliable operation: " + symbols);
	return operations[symbols]->getPriority();
}

bool Operations::getAssociativity(const std::string& symbols)
{
	if (operations.count(symbols) == 0)
		throw std::runtime_error("Unavaliable operation: " + symbols);
	return operations[symbols]->getAssociativity();
}

int Operations::getBinary(const std::string& symbols)
{
	if (operations.count(symbols) == 0)
		throw std::runtime_error("Unavaliable operation: " + symbols);
	return operations[symbols]->getBinary();
}

double Operations::calculation(const std::string& symbols, double a, double b)
{
	if (operations.count(symbols) == 0)
		throw std::runtime_error("Unavaliable operation: " + symbols);
	return operations[symbols]->calculation(a, b);
}

