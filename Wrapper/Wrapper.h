#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <tuple>


template<typename T, typename... Pairs>
class Wrapper 
{
private: 
	using Fptr = int(T::*)(Pairs...);
	using argumentsList = std::unordered_map<std::string, int>;
	T* instancePointer;
	Fptr methodPointer;
	argumentsList arguments;

	std::vector<decltype(arguments.begin()->second)> values;

	template<std::size_t... Is>
	int execute(std::index_sequence<Is...>)
	{
		return (instancePointer->*methodPointer)(values[Is]...);
	};
public:

	Wrapper(T* instancePointer_, Fptr methodPointer_, argumentsList arguments_) :instancePointer(instancePointer_),
		methodPointer(methodPointer_), arguments()
	{
		for (auto&& pair : arguments_)
			values.push_back(pair.second);
	}
	auto execute(const argumentsList& arguments_)
	{
		auto it = arguments_.begin();
		for (int i = 0; i < values.size(); i++)
		{
			values[i] = it->second;
			it++;
		}

		return execute(std::make_index_sequence<sizeof...(Pairs)>{});
	}

};