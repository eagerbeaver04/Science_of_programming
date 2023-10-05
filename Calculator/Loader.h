#ifndef LOADER_H
#define LOADER_H

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
	Loader(const std::string& folder, const std::string& extension)
	{
		this->libraries;
		this->folder = folder;
		this->extension = extension;
	}

	Loader() = default;
	Loader(const Loader&) = default;
	Loader(Loader&&) = default;
	Loader& operator=(Loader const&) = default;
	Loader& operator=(Loader&&) = default;

	~Loader()
	{
		for (const auto& lib : libraries)
			FreeLibrary(lib);
		libraries.clear();
	}
	std::unique_ptr<Operator> getOperatorFromDll(const HINSTANCE& load);
	void loadDll(std::map<std::string, std::unique_ptr<Operator>>& operations, const std::string& folder, const std::string& extension);

};

#endif
