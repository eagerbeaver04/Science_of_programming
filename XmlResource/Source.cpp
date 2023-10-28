#include "Resource.h"

int main() 
{
    Resource& res = res.create();
    try 
    {
        res.load("input.txt");
        res.print();
        res.save("output.txt");
        for (auto it = res.begin(), end = res.rend(); it != end; ++it)
            it->print();
        std::cout << std::endl;
        for (auto it = res.begin(), end = res.end(); it != end; ++it)
            it->print();
        std::cout << std::endl;
        res.findByValue("4").print();
        std::cout << std::endl;
        res.findByTag("BODY").print();
        std::cout << std::endl;
        auto iter = res.findByValue("10");
        std::unique_ptr<Node> b = std::make_unique<Node>("b", "11");
        res.add(iter, std::move(b));
        for (auto it = res.begin(), end = res.rend(); it != end; ++it)
            it->print();
 
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
    return 0;
};