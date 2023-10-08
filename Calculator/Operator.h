#pragma once

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

	~Operator() = default;

	int getPriority()
	{
		return priority;
	}
	std::string getName()
	{
		return name;
	}
	int getBinary()
	{
		return binary;
	}
	bool getAssociativity()
	{
		return associativity;
	}
	std::function<double(double, double)> getOperation()
	{
		return operation;
	}
	double calculation(double a, double b)
	{
		return (operation)(a, b);
	}

};
