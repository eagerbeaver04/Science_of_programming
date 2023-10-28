#include "Resource.h"

int main() 
{
    Tree* doc = new Tree();
    Resource& res = res.create();
    try 
    {
        res.load("input.txt");
        res.print();
        res.save("output.txt");
        for (auto it = res.begin(), end = res.end(); it != end; ++it)
            it->print();
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
    return 0;
};