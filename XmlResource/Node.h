#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

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
public:
    Node(const std::string& tag, const std::string& value, Node* parent_ = nullptr) : tag(tag), value(value), parent(parent_) {};
    void push(std::unique_ptr<Node> child);
    std::string toString(int depth) const;
    void forEach(std::function<void(const Node&)> function);
    Node* next();
    Node* begin();
    Node* end();
    Node* rend();
    void print() const;
    std::string getValue() const;
    std::string getTag() const;
    void addChildrenToParent();
};