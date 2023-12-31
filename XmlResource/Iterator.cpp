#include "Node.h"

void Iterator::next()
{
    ptr->next(*this);
}

void Iterator::print()
{
    if(ptr)
        ptr->print();
}

Iterator Iterator::add(const std::string& tag, const std::string& value)
{
    if (ptr)
    {
        std::unique_ptr<Node> node = std::make_unique<Node>(tag, value, ptr);
        Iterator tmp(node.get(), root);
        this->ptr->push(std::move(node));
        return tmp;
    }
    std::cerr << "Invalid operation" << std::endl;
    return *this;
}

void Iterator::erase()
{
    ptr->addChildrenToParent();
}