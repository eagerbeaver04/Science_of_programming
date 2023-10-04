#include "Operations.h"

int Operations::getPriority(const std::string& symbol)
{
	if (this->operations.count(symbol) == 1)
		return this->operations[symbol]->getPriority();
	std::cerr << "Unavaliable operation: " << symbol << std::endl;
	return 1;
}

bool Operations::getAssociativity(const std::string& symbol)
{
	if (this->operations.count(symbol) == 1)
		return this->operations[symbol]->getAssociativity();
	std::cerr << "Unavaliable operation: " << symbol << std::endl;
	return true;
}

int Operations::getBinary(const std::string& symbol)
{
	if (this->operations.count(symbol) == 1)
		return this->operations[symbol]->getBinary();
	std::cerr << "Unavaliable operation: " << symbol << std::endl;
	return 2;
}

double Operations::calculation(const std::string& symbol, double a, double b)
{
	if (this->operations.count(symbol) == 1)
		return this->operations[symbol]->calculation(a,b);
	std::cerr << "Unavaliable operation: " << symbol << std::endl;
	return 0;
}