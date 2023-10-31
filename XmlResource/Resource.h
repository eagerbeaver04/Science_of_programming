#pragma once
#include "Tree.h"

class Resource
{
private:
	std::unique_ptr<Tree> tree;
	Resource() : tree(std::make_unique<Tree>()) {};
public:
	static std::unique_ptr<Resource> create();

	bool load(const std::string& path);
	void save(const std::string& path);	
	void print();

	Iterator begin();
	Iterator end();
	Iterator rend();
	Iterator findByTag(const std::string& tag);
	Iterator findByValue(const std::string& value);
	Iterator add(Iterator& it, const std::string& tag, const std::string& value);
	bool erase(Iterator& it);

	~Resource() = default;
	Resource(const Resource&) = delete;
	Resource(Resource&&) = delete;
	Resource& operator = (const Resource&) = delete;
	Resource& operator = (Resource&&) = delete;

};

