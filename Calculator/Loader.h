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
public:
	static Loader* getInstance(const std::string& folder, const std::string& extension)
	{
		static Loader* instance = new Loader(folder, extension);
		return instance;
	}
	Operator* getOperatorFromDll(std::filesystem::path path);
	void loadDll(std::map<std::string, Operator*>& operations, const std::string& folder, const std::string& extension);
private:
	std::vector< HINSTANCE> libraries;
	std::string folder;
	std::string extension;

	Loader(const std::string& folder, const std::string& extension)
	{
		this->libraries;
		this->folder = folder;
		this->extension = extension;
	}
	Loader()
	{
		this->libraries;
		this->folder = "";
		this->extension = "";
	}
	~Loader()
	{
		for (const auto& lib : libraries)
			FreeLibrary(lib);
		libraries.clear();
	}
};

#endif
