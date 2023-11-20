#pragma once
#include "Wrapper.h"

template <typename T, typename F, typename... Pairs>
class Engine
{
private:
    using ArgumentUniqueType = variant_t<Pairs...>;
    using ArgumentsList = std::unordered_map<std::string, ArgumentUniqueType>;
    std::unordered_map<std::string, std::function<F(const ArgumentsList&)>> commands;

public:
    Engine(Wrapper<T, F, Pairs...>* instance) {};
    void registerCommand(Wrapper<T, F, Pairs...>* instance, const std::string& name)
    {
        commands[name] = [instance](const ArgumentsList& arguments)
        {
            return instance->execute(arguments);
        };
    }

    auto execute(const std::string& name, const ArgumentsList& arguments)
    {
        auto it = commands.find(name);
        if (it != commands.end())
            return (it->second)(arguments);
        std::cerr << "Undefined command name" << std::endl;
        return F();
    }
};