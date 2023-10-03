#include "Loader.h"

Operator* Loader::getOperatorFromDll(const HINSTANCE& load)
{

	std::function<double(double, double)> Operation = (double (*) (double, double))GetProcAddress(load, "operation");
	std::function<int(void)>  Binary = (int (*) (void))GetProcAddress(load, "binary");
	std::function<int(void)>  Priority = (int (*) (void))GetProcAddress(load, "priority");
	std::function<std::string(void)> Name = (std::string (*) (void)) GetProcAddress(load, "name");
	std::function<bool(void)>  Associativity = (bool (*) (void))GetProcAddress(load, "associativity");

	Operator* op = new Operator(Name(), Priority(), Associativity(), Binary(), Operation);

	return op;
}

void Loader::loadDll(std::map<std::string, Operator*>& operation_list, const std::string& folder, const std::string& extension)
{
	std::vector<std::filesystem::path> files;

	for (const auto& entry : std::filesystem::directory_iterator(folder))
		if (entry.path().extension() == extension)
			files.push_back(entry.path().c_str());

	const wchar_t* widecFileName;
	HINSTANCE load;

	for (const auto& path : files)
	{
		widecFileName = path.c_str();
		load = LoadLibrary(widecFileName);
		this->libraries.push_back(load);

		if (load)
		{
			Operator* op = getOperatorFromDll(load);
			operation_list[op->getName()] = op;
			continue;
		}

		std::cerr << "Opening dll file " << path << " failure" << std::endl;
	}

}