#include "Loader.h"

Operator* Loader::getOperatorFromDll(std::filesystem::path path)
{
	const wchar_t* widecFileName = path.c_str();

	HINSTANCE load;
	load = LoadLibrary(widecFileName);
	this->libraries.push_back(load);

	typedef double (*double_fun_2) (double, double);
	typedef int (*int_fun) (void);
	typedef std::string(*str_fun) (void);
	typedef bool (*bool_fun) (void);

	double_fun_2 Operation;
	int_fun Binary;
	int_fun Priority;
	str_fun Name;
	bool_fun Associativity;

	Operation = (double_fun_2)GetProcAddress(load, "operation");
	Binary = (int_fun)GetProcAddress(load, "binary");
	Priority = (int_fun)GetProcAddress(load, "priority");
	Name = (str_fun)GetProcAddress(load, "name");
	Associativity = (bool_fun)GetProcAddress(load, "associativity");

	Operator* op = new Operator(Name(), Priority(), Associativity(), Binary(), Operation);

	return op;
}

void Loader::loadDll(std::map<std::string, Operator*>& operation_list, const std::string& folder, const std::string& extension)
{
	std::vector<std::filesystem::path> files;

	for (const auto& entry : std::filesystem::directory_iterator(folder))
		if (entry.path().extension() == extension)
			files.push_back(entry.path().c_str());

	for (const auto& path : files)
	{
		Operator* op = getOperatorFromDll(path);
		operation_list[op->getName()] = op;
	}

}