#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

class Iterator;

class Node 
{
private:
    std::string tag;
    std::string value;
    std::vector<std::unique_ptr<Node>> children;
    Node* parent;
    //There is raw pointer because child does not manage parent. 
    // Only parent manage his children.
    //Also this field is private and this fact prohibit extern access.
    int numberInChildren(Node* element) const;
    void clearThisFromParent();
    Node* begin();
    Node* end();
    Node* rend();
public:
    Node(const std::string& tag, const std::string& value, Node* parent_ = nullptr) : tag(tag), value(value), parent(parent_) {};
    void push(std::unique_ptr<Node> child);
    std::string toString(int depth) const;
    void forEach(std::function<void(const Node&)> function);
    Node* next();
    Iterator createIteratorBegin();
    Iterator createIteratorEnd();
    Iterator createIteratorRend();
    void print() const;
    std::string getValue() const;
    std::string getTag() const;
    void addChildrenToParent();
};


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
    // There are raw pointers because instance of Iterator class does not manage objects.
    //These pointers are needed only for enumaration. 
    //Also these fields are private and this fact prohibit extern access.

    void next();
public:
    Iterator(pointer ptr_, pointer root_) : ptr(ptr_), root(root_) {};
    reference operator*() { return *ptr; };
    pointer operator ->() { return ptr; };
    Iterator operator++ () { next(); return *this; };
    Iterator& operator++(int i) { Iterator tmp = *this; ++(*this); return tmp; };
    friend bool operator == (const Iterator& a, const Iterator& b) { return (a.ptr == b.ptr) && (a.root == b.root); };
    friend bool operator != (const Iterator& a, const Iterator& b) { return (a.ptr != b.ptr) || (a.root != b.root); };
    Iterator add(const std::string& tag, const std::string& value);
    void erase();
    void print();
};

