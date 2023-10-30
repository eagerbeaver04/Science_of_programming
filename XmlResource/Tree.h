#pragma once
#include "Iterator.h"

class Tree
{
private:
    std::unique_ptr<Node> root;
    std::unique_ptr<Node> parseNode(const std::string& str, int& pos);
    std::string toString();
    std::string getNextTag(const std::string& str, int& pos);
    std::string getNextValue(const std::string& str, int& pos);
	Node* getRoot() {return  root->getChildren()[0].get(); };
public:
    void parse(const std::string& xml);
    void load(const std::string& path);
    void save(const std::string& path);
    void print();
    void forEach(const std::function<void(const Node&)>& function);
	Iterator begin() { return Iterator(getRoot()->begin(), root.get()); }
	Iterator rend() { return Iterator(getRoot()->end(), root.get()); }
	Iterator end() { return Iterator(root.get()->end(), root.get()); }
	Iterator find(const std::function<bool(Node* node)>& function);
	Iterator add(Iterator& it, std::unique_ptr<Node>);
	Iterator findByValue(const std::string& value);
	Iterator findByTag(const std::string& tag);
	bool erase(Iterator& it);
};




