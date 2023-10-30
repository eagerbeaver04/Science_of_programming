#pragma once
#include "Node.h"
class Iterator
{
private:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Node;
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
	friend bool operator == (const Iterator& a, const Iterator& b) { return (a.ptr == b.ptr) && (a.root == b.root); };
	friend bool operator != (const Iterator& a, const Iterator& b) { return (a.ptr != b.ptr) || (a.root != b.root); };
	bool find(const std::function<bool(Node* node)>& function);
	void add(std::unique_ptr<Node>);
	bool erase();
	void print();
};