#include "Iterator.h"

void Iterator::next()
{
    Node* father = nullptr;
    father = root->findParent(ptr);

    if (father != nullptr)
    {
        int i = father->numberInChildren(ptr);
        if (i == father->getChildren().size() - 1)
        {
            ptr = father;
            return;
        }
        else
        {
            ptr = father->getChildren()[i + 1].get()->begin();
            return;
        }
        father = root->findParent(ptr);
    }
    ptr = root->end();
    father = nullptr;
}

void Iterator::print()
{
    ptr->print();
}

bool Iterator::find(const std::function<bool(Node* node)>& function)
{
    return function(ptr);
}

void Iterator::add(std::unique_ptr<Node> node)
{
    this->ptr->push(std::move(node));
}

bool Iterator::erase()
{
    std::vector <std::unique_ptr<Node>>& tmp = ptr->getChildren();
    std::vector <std::unique_ptr<Node>>& parent_children = root->findParent(ptr)->getChildren();
    for (int i = 0; i < tmp.size(); i++)
        parent_children.push_back(std::move(tmp[i]));
    for (int i = 0; i < parent_children.size(); i++)
        if (parent_children[i].get() == ptr)
        {
            parent_children[i].reset();
            parent_children.erase(parent_children.begin() + i);
            break;
        }
    return true;
}