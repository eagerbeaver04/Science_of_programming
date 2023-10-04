#include "Calculator.h"


int main(int argc, char** argv)
{
	//std::string folder = "./plugins";//for Visual Studio
	std::string folder = "..\\plugins";//for Cmake project
	std::string extension = ".dll";
	Calculator* app = app->getInstance(folder, extension);
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		app->setInput(input);
		app->calculation();
	}

}