#include "Resource.h"

Resource& Resource::create()
{
	static Resource res;
	return res;
}

void Resource::load(const std::string& path)
{
	tree.load(path);
}

void Resource::save(const std::string& path)
{
	tree.save(path);
}

void Resource::print()
{
	tree.print();
}

Iterator Resource::begin() 
{
	return tree.begin();
}

Iterator Resource::end()
{
	return tree.end();
}
