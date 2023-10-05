#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Loader.h"

class Operations
{
public:
	Operations()
	{
		this->operations["+"] = std::make_unique<Operator>("+", 1, true, 2, [](double a, double b) { return a + b; });
		this->operations["-"] = std::make_unique<Operator>("-", 1, true, 2, [](double a, double b) { return a - b; });
		this->operations["*"] = std::make_unique<Operator>("*", 2, true, 2, [](double a, double b) { return a * b; });
		this->operations["/"] = std::make_unique<Operator>("/", 2, true, 2, [](double a, double b) {
			if (b)
				return a / b;
			std::cerr << std::endl << "Unavaliable operation: Division by zero" << std::endl;
			return a; });
		this->loader = Loader();
	};
	Operations(const std::string& folder, const std::string& extension) : Operations()
	{
		if (folder != "" && extension != "")
		{
			this->loader = Loader(folder, extension);
			this->loader.loadDll(this->operations, folder, extension);
		}
		else
			std::cout << std::endl << "Folder for extra operations is not download" << std::endl;
	};

	int getPriority(const std::string& symbol);
	bool getAssociativity(const std::string& symbol);
	int getBinary(const std::string& symbol);

	double calculation(const std::string& symbol, double a, double b);
	~Operations() = default;
	Operations(const Operations& A) = default;
	Operations(Operations&&) = default;
	Operations& operator = (const Operations& A) = default;
	Operations& operator=(Operations&&) = default;

private:
	std::map<std::string, std::unique_ptr<Operator>> operations;
	Loader loader;
};

#endif
