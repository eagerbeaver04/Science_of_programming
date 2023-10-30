#include "Iterator.h"

void Iterator::next()
{
    Node* tmp = ptr->next();
    if (tmp)
    {
        ptr = tmp;
        return;
    }
    else if(ptr)
        ptr = nullptr;
}

void Iterator::print()
{
    ptr->print();
}

bool Iterator::find(const std::function<bool(Node* node)>& function)
{
    return function(ptr);
}

Iterator Iterator::add(const std::string& tag, const std::string& value)
{
    std::unique_ptr<Node> node = std::make_unique<Node>(tag, value, ptr);
    Iterator tmp (node.get(), root);
    this->ptr->push(std::move(node));
    return tmp;
}

void Iterator::erase()
{
    ptr->addChildrenToParent();
}