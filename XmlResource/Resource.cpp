#include "Resource.h"

std::unique_ptr<Resource> Resource::create()
{
	return std::unique_ptr<Resource>(new Resource());
}

bool Resource::load(const std::string& path)
{
	return tree->load(path);
}

void Resource::save(const std::string& path)
{
	tree->save(path);
}

void Resource::print() 
{
	tree->print();
}

Iterator Resource::begin() 
{
	return tree->begin();
}

Iterator Resource::end()
{
	return tree->end();
}

Iterator Resource::rend()
{
	return tree->rend();
}

Iterator Resource::findByTag(const std::string& tag)
{
	return tree->findByTag(tag);
}

Iterator Resource::findByValue(const std::string& value)
{
	return tree->findByValue(value);
}

Iterator Resource::add(Iterator& it, const std::string& tag, const std::string& value)
{
	return tree->add(it, tag, value);
}

bool Resource::erase(Iterator&  it)
{
	return tree->erase(it);
}