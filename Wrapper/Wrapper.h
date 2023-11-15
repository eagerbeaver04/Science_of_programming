#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>

template <typename T>
bool defaultValue(const T& value) 
{
    return T();
}

template <typename T, typename... Pairs>
class Wrapper
{
private:
    using Fptr = int (T::*)(Pairs...);
    using argumentsList = std::unordered_map<std::string, int>;
    T* instancePointer;
    Fptr methodPointer;
    argumentsList arguments;

    std::vector<decltype(arguments.begin()->second)> values;

    template <std::size_t... Is>
    auto calculate(std::index_sequence<Is...>)
    {
        auto value = (instancePointer->*methodPointer)(values[Is]...);
        for (auto&& el : values)
            el = defaultValue(el);
        return value;
    };

public:
    Wrapper(T* instancePointer_, Fptr methodPointer_, argumentsList arguments_) : instancePointer(instancePointer_),
        methodPointer(methodPointer_)
    {
        for (auto&& pair : arguments_)
        {
            arguments[pair.first] = pair.second;
            values.push_back(pair.second);
        }
    }

    auto execute(const argumentsList& arguments_)
    {
        auto itStoreBegin = arguments.begin();
        auto itStoreEnd = arguments.end();
        auto itInput = arguments_.begin();
        auto itStore = itStoreBegin;
        for (int i = 0; i < values.size(); i++)
        {
            itStore = arguments.find(itInput->first);
            if (itStore == itStoreEnd)
            {
                std::cerr << "Undefined argument" << std::endl;
                return 0;
            }
            values[std::distance(itStoreBegin, itStore)] = itInput->second;
            itInput++;
        }
        return calculate(std::make_index_sequence<sizeof...(Pairs)>{});
    }
};