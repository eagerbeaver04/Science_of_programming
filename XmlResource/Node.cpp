#include "Node.h"

void Node::push(std::unique_ptr<Node> child)
{
    children.push_back(std::move(child));
}

std::string Node::toString(int depth)
{
    const std::string spaces = std::string(depth * 2, ' ');
    std::string result = "";
    result += spaces + "<" + tag + "> " + value + "\n";
    for (const auto& child : children)
        result += child->toString(depth + 1);
    result += spaces + "</" + tag + ">" + "\n";
    return result;
}

void Node::forEach(std::function<void(const Node&)> function)
{
    function(*this);
    for (const auto& child : children)
        child->forEach(function);
}