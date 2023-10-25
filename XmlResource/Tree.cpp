#include "Tree.h"

void Tree::parse(const std::string& str) 
{
    int pos = 0;
    root_node = parse_node(str, pos);
}

void Tree::load(const std::string& path)
{
    parse(read_file(path));
}

void Tree::save(const std::string& path)
{
    write_to_file(path, to_string());
}

void Tree::print() 
{
    std::cout << to_string() << std::endl;
}

void Tree::for_each(std::function<void(const Node&)> function)
{
    root_node->for_each(function);
}

std::unique_ptr<Node> Tree::parse_node(const std::string& str, int& pos) 
{
    std::string tag = get_next_tag(str, pos);
    std::string value = get_next_value(str, pos);
    std::unique_ptr<Node> node(new Node(tag, value));
    std::string next_tag = get_next_tag(str, pos);
    while (next_tag != ("/" + tag) && pos < str.size())
    {
        pos -= next_tag.size() + 2;
        node->push(parse_node(str, pos));
        next_tag = get_next_tag(str, pos);
    }
    return node;
}

std::string get_next_tag(const std::string& str, int& pos)
{
    pos = str.find("<", pos) + 1;
    int end = str.find(">", pos);
    std::string tag = str.substr(pos, end - pos);
    pos = end + 1;
    return tag;
}

std::string get_next_value(const std::string& str, int& pos) 
{
    int start = pos;
    pos = str.find("<", pos);
    return str.substr(start, pos - start);
}

std::string Tree::read_file(const std::string& path) 
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("File not found\n");
    std::string line, result= "";
    while(std::getline(file, line))
        result += line;
    std::string::iterator it = std::remove(result.begin(), result.end(), '\n');
    result.erase(it, result.end());
    return result;
}

void Tree::write_to_file(const std::string& path, const std::string& content)
{
    std::ofstream file(path);
    if (!file)
        throw std::runtime_error("File not found\n");
    file << content;
}

std::string Tree::to_string()
{
    return root_node->to_string(0);
}
