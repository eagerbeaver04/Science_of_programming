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
public:
    Node(const std::string& tag, const std::string& value) : tag(tag), value(value) {};

    void push(std::unique_ptr<Node> child);
    std::string toString(int depth);
    void forEach(std::function<void(const Node&)> function);
    Node* findParent(Node* element);
    int numberInChildren(Node* element);
    Node* begin();
    Node* end();
    void print();
    std::string getValue();
    std::string getTag();
    std::vector<std::unique_ptr<Node>>& getChildren();
};