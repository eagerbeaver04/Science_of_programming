#include "Resource.h"

int main()
{
	std::unique_ptr<Resource> res = Resource::create();
	if (res->load("input.txt"))
	{
		res->print();
		res->save("output.txt");
		for (auto it = res->begin(), end = res->rend(); it != end; ++it)
			it->print();
		std::cout << std::endl;
		for (auto it = res->begin(), end = res->end(); it != end; ++it)
			it->print();
		std::cout << std::endl << "value = 4 => ";
		res->findByValue("4").print();
		std::cout << std::endl << "tag = BODY => ";
		res->findByTag("BODY").print();
		std::cout << std::endl;
		auto iter = res->findByValue("10");
		res->add(iter, "b", "11");
		res->print();
		iter = res->findByTag("BODY");
		res->erase(iter);
		res->print();
	}
	return 0;
};