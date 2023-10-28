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

Node* Node::findParent(Node* element)
{
    int length = children.size();
    if (length == 0)
        return nullptr;
    for (int i = 0; i < length; i++)
    {
        if (children[i].get() == element)
            return this;
        else
        {
            Node* node = children[i].get()->findParent(element);
            if (node != nullptr)
                return node;
            node = nullptr;
            continue;
        }
    }
    return nullptr;
}

int Node::numberInChildren(Node* element)
{
    for (int i = 0; i < children.size(); i++)
        if (element == children[i].get())
            return i;
    return -2;
}

Node* Node::begin()
{
    Node* father = new Node("", "");
    father = this;
    while (father->children.size() != 0)
        father = father->children[0].get();
    return father;
}

Node* Node::end()
{
    return this;
}

void Node::print()
{
    std::cout << tag << " value : " << value << std::endl;
}
