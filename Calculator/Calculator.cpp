#include "Calculator.h"


int main(int argc, char** argv)
{
	std::string folder = "plugins";
	std::string extension = ".dll";
	Calculator app(folder, extension);
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		app.setInput(input);
		try
		{
			app.calculation();
		}
		catch (const std::runtime_error& error_message)
		{
			std::cerr << error_message.what() << std::endl;
		}
	}

	return 0;

}