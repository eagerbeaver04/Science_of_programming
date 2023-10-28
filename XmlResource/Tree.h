#pragma once
#include "Node.h"

class Iterator
{
private:
	using pointer = Node*;
	using reference = Node&;

	pointer ptr;
	pointer root;

	void next();
public:

	Iterator(pointer ptr_, pointer root_) : ptr(ptr_), root(root_) {};
	reference operator*() { return *ptr; };
	pointer operator ->() { return ptr; };
	Iterator operator++ () { next(); return *this; };
	Iterator& operator++(int i) { Iterator tmp = *this; ++(*this); return tmp; };
	friend bool operator == (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
	friend bool operator != (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	void print();
};

class Tree
{
private:
    std::unique_ptr<Node> root;

    std::unique_ptr<Node> parseNode(const std::string& str, int& pos);
    std::string toString();
    std::string getNextTag(const std::string& str, int& pos);
    std::string getNextValue(const std::string& str, int& pos);
public:
    void parse(const std::string& xml);
    void load(const std::string& path);
    void save(const std::string& path);
    void print();
    void forEach(std::function<void(const Node&)> callback);

	Iterator begin() { return Iterator(root->begin(), root.get()); }
	Iterator end() { return Iterator(root->end(), root.get()); }
};




