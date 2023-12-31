#include "Tree.h"

void Tree::parse(const std::string& str)
{
    int pos = 0;
    try
    {
        root = parseNode(str, pos, nullptr);
    }
    catch(std::runtime_error err)
    {
        std::cerr << err.what() << std::endl;
    }
}

bool Tree::load(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "File not found" << std::endl;
        return false;
    }
    std::string line, result = "";
    while (std::getline(file, line))
        result += line;
    std::string::iterator it = std::remove(result.begin(), result.end(), '\n');
    result.erase(it, result.end());

    parse(result);
    return true;
}

void Tree::save(const std::string& path)
{
    std::ofstream file(path);
    if (!file)
        return;
    file << toString();
}

void Tree::print() 
{
    std::cout << toString() << std::endl;
}

void Tree::forEach(const std::function<void(const Node&)>& function)
{
    root->forEach(function);
}

std::unique_ptr<Node> Tree::parseNode(const std::string& str, int& pos, Node* parent)
{
    std::string tag = getNextTag(str, pos);
    std::string value = getNextValue(str, pos);
    std::unique_ptr<Node> node(new Node(tag, value, parent));
    std::string next_tag = getNextTag(str, pos);
    while (next_tag != ("/" + tag) && pos < str.size())
    {
        pos -= next_tag.size() + 2;
        if (pos == -1)
            throw std::runtime_error("tags were mismatched");
        node->push(parseNode(str, pos, node.get()));
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

Iterator Tree::findByValue(const std::string& value)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
        if (it->getValue() == value)
            return it;
    return this->rend();
}

Iterator Tree::findByTag(const std::string& tag)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
        if (it->getTag() == tag)
            return it;
    return this->rend();
}

Iterator Tree::add(Iterator& it, const std::string& tag, const std::string& value)
{
   return it.add(tag, value);
}

bool Tree::erase(Iterator& it)
{
    if (it == Iterator(root.get(), root.get()))
        return false;
    if (it == Iterator(nullptr,nullptr))
        return false;
    it.erase();
    return true;
}
 