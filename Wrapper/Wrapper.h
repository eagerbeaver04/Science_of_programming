#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <vector>
#include <type_traits>

template <typename T, typename... Ts>
struct unique 
{
    using type = T;
};

template <typename... Ts, typename U, typename... Us>
struct unique<std::variant<Ts...>, U, Us...>
    : std::conditional_t<(std::is_same_v<U, Ts> || ...),
    unique<std::variant<Ts...>, Us...>,
    unique<std::variant<Ts..., U>, Us...>> {};

template <typename... Ts>
using variant_t = typename unique<std::variant<>, Ts...>::type;

template <typename T, typename F, typename... Pairs>
class Wrapper
{
private:
    using Fptr = F(T::*)(Pairs...);
    using ArgumentUniqueType = variant_t<Pairs...>;
    using ArgumentsList = std::unordered_map<std::string, ArgumentUniqueType>;
    T* instancePointer;
    Fptr methodPointer;
    ArgumentsList arguments;

    std::vector<ArgumentUniqueType> values;

public:
    Wrapper(T* instancePointer_, Fptr methodPointer_, const ArgumentsList& arguments_)
        : instancePointer(instancePointer_), methodPointer(methodPointer_), arguments(arguments_)
    {
        for (auto&& pair : arguments_)
        {
            arguments[pair.first] = pair.second;
            values.push_back(pair.second);
        }
    }

    template <std::size_t... Is>
    auto calculate(std::index_sequence<Is...>)
    {
        return (instancePointer->*methodPointer)(std::get<Pairs>(values[Is])...);
    }

    auto execute(const ArgumentsList& arguments_)
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
                return F();
            }
            values[std::distance(itStoreBegin, itStore)] = itInput->second;
            itInput++;
        }
        return calculate(std::make_index_sequence<sizeof...(Pairs)>{});
    }
};