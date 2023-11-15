#pragma once
#include "Wrapper.h"

class Engine
{
private:
	using argumentList = std::unordered_map<std::string, int>;
	std::unordered_map < std::string, std::function<int(argumentList)>> commands;
public:

};