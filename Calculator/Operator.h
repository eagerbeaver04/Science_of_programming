#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <functional>

class Operator
{
private:
	std::string name;
	int priority;
	bool associativity;// true - left, false - right
	int binary;
	std::function<double(double, double)> operation;

public:
	Operator(const std::string& name, int priority, bool associativity,
		int binary, const std::function<double(double, double)>& operation)
		: name(name), priority(priority), associativity(associativity), binary(binary), operation(operation) {};

	Operator() = default;
	~Operator() = default;
	Operator(const Operator& A) = default;
	Operator(Operator&&) = default;
	Operator& operator = (const Operator& A) = default;
	Operator& operator=(Operator&&) = default;

	int getPriority()
	{
		return this->priority;
	}
	std::string getName()
	{
		return this->name;
	}
	int getBinary()
	{
		return this->binary;
	}
	bool getAssociativity()
	{
		return this->associativity;
	}
	std::function<double(double, double)> getOperation()
	{
		return this->operation;
	}
	double calculation(double a, double b)
	{
		return (this->operation)(a, b);
	}
};

#endif