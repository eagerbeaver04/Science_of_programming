#include "Tree.h"

void Tree::parse(const std::string& str)
{
    int pos = 0;
    root = parseNode(str, pos);
}

void Tree::load(const std::string& path)
{
       std::ifstream file(path);
    if (!file)
        throw std::runtime_error("File not found\n");
    std::string line, result = "";
    while (std::getline(file, line))
        result += line;
    std::string::iterator it = std::remove(result.begin(), result.end(), '\n');
    result.erase(it, result.end());

    parse(result);
}

void Tree::save(const std::string& path)
{
    std::ofstream file(path);
    if (!file)
        throw std::runtime_error("File not found\n");
    file << toString();
}

void Tree::print()
{
    std::cout << toString() << std::endl;
}

void Tree::forEach(std::function<void(const Node&)> function)
{
    root->forEach(function);
}

std::unique_ptr<Node> Tree::parseNode(const std::string& str, int& pos)
{
    std::string tag = getNextTag(str, pos);
    std::string value = getNextValue(str, pos);
    std::unique_ptr<Node> node(new Node( tag, value));
    std::string next_tag = getNextTag(str, pos);
    while (next_tag != ("/" + tag) && pos < str.size())
    {
        pos -= next_tag.size() + 2;
        node->push(parseNode(str, pos));
        next_tag = getNextTag(str, pos);
    }
    return node;
}

std::string Tree::getNextTag(const std::string& str, int& pos)
{
    pos = str.find("<", pos) + 1;
    int end = str.find(">", pos);
    std::string tag = str.substr(pos, end - pos);
    pos = end + 1;
    return tag;
}

std::string Tree::getNextValue(const std::string& str, int& pos)
{
    int start = pos;
    pos = str.find("<", pos);
    return str.substr(start, pos - start);
}

std::string Tree::toString()
{
    return root->toString(0);
}

void Iterator::next()
{

    Node* father = nullptr;
    father = root->findParent(ptr);

    if (father != nullptr)
    {
        int i = father->numberInChildren(ptr);
        if (i == father->children.size() - 1)
        {
            ptr = father;
            return;
        }
        else
        {
            ptr = father->children[i + 1].get()->begin();
            return;
        }
        father = root->findParent(ptr);
    }
    ptr = ptr->begin();
    father = nullptr;
}

void Iterator::print()
{
    ptr->print();
}
