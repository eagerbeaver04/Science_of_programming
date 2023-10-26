#pragma once
#include "Node.h"

class Tree
{
private:
    std::unique_ptr<Node> root_node;

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
};


