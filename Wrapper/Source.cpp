#include "Engine.h"

class Subject
{
public:
    double f3(int a, double b, int c)
    {
        return -1*(a + b + c) / 3;
    }
    double f4(int a, double b, int c)
    {
        return (a + b + c)/3;
    }
};

int main()
{
    Subject s1;
    Wrapper w1(&s1, &Subject::f4, { {"arg1", 0}, {"arg2",0 },{"arg3",0 } });
    Wrapper w2(&s1, &Subject::f3, { {"arg1", 0}, {"arg2",0 },{"arg3",0 } });

    Engine engine(&w1);
    engine.registerCommand(&w1, "command1");
    engine.registerCommand(&w2, "command2");

    std::cout << "(1+2.5+1)/3= " << engine.execute("command1", { {"arg1", 1}, {"arg2", 2.5}}) << std::endl;

    std::cout << "-1* (1+2.5+1)/3= " << engine.execute("command2", { {"arg1", 1}, {"arg2", 2.5}, {"arg3",1 } }) << std::endl;

    std::cout << "(1+2.5+1)/3= " << engine.execute("command1", { {"arg3", 1} , {"arg1", 1}, {"arg2", 2.5} }) << std::endl;

    return 0;
}
