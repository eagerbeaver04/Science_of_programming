#include "Node.h"

void Node::push(std::unique_ptr<Node> child)
{
    children.push_back(std::move(child));
}

std::string Node::toString(int depth) const
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
    for (auto&& child : children)
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

int Node::numberInChildren(Node* element) const 
{
    for (int i = 0; i < children.size(); i++)
        if (element == children[i].get())
            return i;
    return -2;
}

Node* Node::begin() 
{
    Node* father = this;
    while (father->children.size() != 0)
        father = father->children[0].get();
    return father;
}

Node* Node::end()
{
    return this;
}

void Node::print() const
{
    std::cout << tag << " value : " << value << std::endl;
}

std::string Node::getValue() const 
{
    return value;
}

std::string Node::getTag() const 
{
    return tag;
}

std::vector<std::unique_ptr<Node>>& Node::getChildren()
{
    return children;
}