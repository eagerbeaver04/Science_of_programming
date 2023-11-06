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

Node* Node::rend()
{
    return this;
}

Node* Node::end()
{
    return nullptr;
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

void Node::addChildrenToParent()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->parent = parent;
        parent->children.push_back(std::move(children[i]));
    }
    clearThisFromParent();
}

void Node::clearThisFromParent()
{
    std::vector<std::unique_ptr<Node>>& tmp = parent->children;
    for (int i = 0; i < tmp.size(); i++)
        if (tmp[i].get() == this)
        {
            tmp[i].reset();
            tmp.erase(tmp.begin() + i);
            break;
        }
}

Iterator Node::createIteratorBegin()
{
    return Iterator(this->begin(), this);
}

Iterator Node::createIteratorEnd()
{
    return Iterator(this->end(), this);
}

Iterator Node::createIteratorRend()
{
    return Iterator(this->rend(), this);
}

void Node::next(Iterator& it)
{ 
    Node* tmp = nullptr;
    if (parent != nullptr)
    {
        int i = parent->numberInChildren(this);
        if (i == parent->children.size() - 1)
            tmp = parent;
        else
            tmp = parent->children[i + 1].get()->begin();
    }
    it.setValue(tmp); 
}