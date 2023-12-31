#pragma once
#include "Node.h"

class Tree
{
private:
    std::unique_ptr<Node> root;
    std::unique_ptr<Node> parseNode(const std::string& str, int& pos, Node* parent);
    std::string toString();
    std::string getNextTag(const std::string& str, int& pos);
    std::string getNextValue(const std::string& str, int& pos);
public:
    void parse(const std::string& xml);
    bool load(const std::string& path);
    void save(const std::string& path);
    void print();
    void forEach(const std::function<void(const Node&)>& function);
	Iterator begin() { return root->createIteratorBegin(); }
	Iterator rend() { return root->createIteratorRend(); }
	Iterator end() { return root->createIteratorEnd(); }
	Iterator add(Iterator& it, const std::string& tag, const std::string& value);
	Iterator findByValue(const std::string& value);
	Iterator findByTag(const std::string& tag);
	bool erase(Iterator& it);
};




