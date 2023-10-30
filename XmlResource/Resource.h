#pragma once
#include "Tree.h"

class Resource
{
private:
	std::unique_ptr<Tree> tree;
	Resource() : tree(std::make_unique<Tree>()) {};
public:
	static std::unique_ptr<Resource> create();

	void load(const std::string& path);
	void save(const std::string& path);	
	void print();

	Iterator begin();
	Iterator end();
	Iterator rend();
	Iterator findByTag(const std::string& tag);
	Iterator findByValue(const std::string& value);
	Iterator find(const std::function<bool(Node* node)>& function);
	Iterator add(Iterator& it, std::unique_ptr<Node> node);
	bool erase(Iterator& it);

	~Resource() = default;
	Resource(const Resource&) = delete;
	Resource(Resource&&) = delete;
	Resource& operator = (const Resource&) = delete;
	Resource& operator = (Resource&&) = delete;

};

