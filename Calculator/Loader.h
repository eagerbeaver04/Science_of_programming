#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <filesystem>
#include <vector>
#include "Operator.h"

class Loader
{
private:
	std::vector< HINSTANCE> libraries;
	std::string folder;
	std::string extension;

public:
	Loader(const std::string& folder, const std::string& extension) : libraries({}), folder(folder), extension(extension) {};
	Loader() = default;

	~Loader()
	{
		for (const auto& lib : libraries)
			FreeLibrary(lib);
		libraries.clear();
	}
	void getOperatorFromDll(std::map<std::string, std::unique_ptr<Operator>>& operations, const HINSTANCE& load);
	void loadDll(std::map<std::string, std::unique_ptr<Operator>>& operations, const std::string& folder, const std::string& extension);

};
