#pragma once
#include "Wrapper.h"

class Engine
{
private:
	using argumentList = std::unordered_map<std::string, int>;
	std::unordered_map < std::string, std::function<int(argumentList)>> commands;
public:
	template<typename T, typename... Pairs>
	void registerCommand(Wrapper<T, Pairs...>* instance, const std::string& name)
	{
		commands[name] = [instance](const argumentList& arguments)
		{
			return instance(arguments);
		};
	}
};