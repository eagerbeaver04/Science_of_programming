#include "Engine.h"

class Subject
{
public:
    double f4(int a, double b)
    {
        return a - b;
    }
};

int main()
{
    Subject s1;
    Wrapper w(&s1, &Subject::f4, { {"1", 0}, {"2",0.5 } });

    Engine engine(&w);
    engine.registerCommand(&w, "command1");

    std::cout << "1-2= " << engine.execute("command1", { {"1", 1}, {"2", 2.0} }) << std::endl;

    std::cout << "3-2.5= " << engine.execute("command1", { {"1", 3}, {"2", 2.5} }) << std::endl;

    std::cout << "3-2.5= " << engine.execute("command1", { {"2", 2.5}, {"1", 3} }) << std::endl;

    return 0;
}
