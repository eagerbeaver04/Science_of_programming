#include "Tree.h"

int main() 
{
    Tree* doc = new Tree();
    try 
    {
        doc->load("input.txt");
        doc->print();
        doc->save("output.txt");
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
    return 0;
};