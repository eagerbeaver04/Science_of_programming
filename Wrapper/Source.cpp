#include "Engine.h"


class Subject
{
public:
	int f3(int a, int b)
	{
		return a + b;
	}
};


int main()
{
	Subject s1;
	Wrapper w(&s1, &Subject::f3, { { "arg1", 0 }, {"arg2", 0} });


	return 0;
}