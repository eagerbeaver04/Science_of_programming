#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

class Node {
public:
    std::string tag;
    std::string value;
    std::vector<std::unique_ptr<Node>> children;

    Node(const std::string& tag, const std::string& value) : tag(tag), value(value) {};

    void push(std::unique_ptr<Node> child);
    std::string toString(int depth);
    void forEach(std::function<void(const Node&)> function);
};