#include "Resource.h"

Resource& Resource::create()
{
	static Resource res;
	return res;
}

void Resource::load(const std::string& path)
{
	tree->load(path);
}

void Resource::save(const std::string& path)
{
	tree->save(path);
}