#pragma once
#include "Node.h"

class Tree 
{
private:
    std::unique_ptr<Node> root_node;

    std::unique_ptr<Node> parse_node(const std::string& str, int& pos);
    std::string read_file(const std::string& path);
    void write_to_file(const std::string& path, const std::string& content);
    std::string to_string();
public:
    void parse(const std::string& xml);
    void load(const std::string& path);
    void save(const std::string& path);
    void print();
    void for_each(std::function<void(const Node&)> callback);
};

std::string get_next_tag(const std::string& str, int& pos);
std::string get_next_value(const std::string& str, int& pos);