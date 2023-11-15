#include "Engine.h"

class Subject
{
public:
    int f3(int a, int b)
    {
        return a - b;
    }
};

int main()
{
    Subject s1;
    Wrapper w(&s1, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;
    engine.registerCommand(&w, "command1");

    int a = engine.execute("command1", {{"arg1", 1}, {"arg2", 2}});
    std::cout << "1-2= " << a << std::endl;
    int b = engine.execute("command1", {{"arg1", 3}, {"arg2", 2}});
    std::cout << "3-2= " << b << std::endl;
    int c = engine.execute("command1", {{"arg2", 2}, {"arg1", 3}});
    std::cout << "3-2= " << c << std::endl;

    return 0;
}