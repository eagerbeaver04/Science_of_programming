#include "Tree.h"

void Tree::parse(const std::string& str)
{
    int pos = 0;
    root = std::move(std::make_unique<Node>("", ""));
    std::unique_ptr<Node> root1 =  parseNode(str, pos);
    root->push(std::move(root1));
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

void Tree::forEach(const std::function<void(const Node&)>& function)
{
    getRoot()->forEach(function);
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
    return getRoot()->toString(0);
}

Iterator Tree::findByValue(const std::string& value)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
        if (it->getValue() == value)
            return it;
    return this->end();
}

Iterator Tree::findByTag(const std::string& tag)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
        if (it->getTag() == tag)
            return it;
    return this->end();
}

Iterator Tree::find(const std::function<bool (Node* node)>& function)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
        if (it.find(function))
            return it;
    return this->end();
}

Iterator Tree::add(Iterator& it, std::unique_ptr<Node> node)
{
    it.add(std::move(node));
    return Iterator(getRoot(), node.get());
}

bool Tree::erase(Iterator& it)
{
    if (it == Iterator(root.get(), root.get()))
        return false;
    if (it == Iterator(getRoot(), getRoot()))
        return false;
    return it.erase();
}
 