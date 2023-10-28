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

Iterator Resource::rend()
{
	return tree.rend();
}

Iterator Resource::findByTag(const std::string& tag)
{
	return tree.findByTag(tag);
}

Iterator Resource::findByValue(const std::string& value)
{
	return tree.findByValue(value);
}

Iterator Resource::find(const std::function<bool(Node* node)>& function)
{
	return tree.find(function);
}

Iterator Resource::add(Iterator it, std::unique_ptr<Node> node)
{
	return tree.add(it, std::move(node));
}

bool Resource::erase(Iterator it)
{
	return tree.erase(it);
}