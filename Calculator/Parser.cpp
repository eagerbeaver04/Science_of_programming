#include "Parser.h"

int Parser::opPriority(const std::string& symbols)
{
    return operations->getPriority(symbols);
}

bool Parser::opAssociativity(const std::string& symbols)
{
    return operations->getAssociativity(symbols);
}

int Parser::opBinary(const std::string& symbols)
{
    return operations->getBinary(symbols);
}

bool Parser::isOperator(const std::string& symbols)
{
    if (symbols == "(" || symbols == ")")
        return false;
    bool associativity = opAssociativity(symbols);
    int binary = opBinary(symbols);
    if ((associativity == true && binary == 2) || (associativity == false && binary == 1))
        return true;
    return false;
}

bool Parser::isFunction(const std::string& symbols)
{
    if (symbols == "(" || symbols == ")")
        return false;
    if (opAssociativity(symbols) == true && opBinary(symbols) == 1)
        return true;
    return false;
}

bool Parser::isIdent(const std::string& symbols)
{
    return (symbols >= "0" && symbols <= "9");
}

bool Parser::isIdent(char symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

bool Parser::isLetter(char symbol)
{
    return (symbol >= 'a' && symbol <= 'z');
}

bool Parser::isLetter(const std::string& symbols)
{
    return (symbols >= "a" && symbols <= "z");
}

double Parser::calculation(const std::string& symbol, double a, double b)
{
    return operations->calculation(symbol, a, b);
}

void Parser::parenthesesBalance(std::stack<std::string>& operations_, std::string& output)
{
    std::string symbols;
    while (!operations_.empty())
    {
        symbols = operations_.top();
        operations_.pop();
        if (symbols == "(")
            break;
        else
            output += symbols + "|";
    }
    if (operations_.empty() && symbols != "(")
        throw std::runtime_error("Error: parentheses mismatched");
    if (!operations_.empty())
    {
        symbols = operations_.top();
        if (isFunction(symbols))
        {
            output += symbols + "|";
            operations_.pop();
        }
    }
}

void Parser::operationPriorityArrangment(std::stack<std::string>& operations_, std::string& current_operator, std::string& output)
{
    while (!operations_.empty())
    {
        std::string last_operator = operations_.top();
        if (isOperator(last_operator) && ((opAssociativity(current_operator) && (opPriority(current_operator) <= opPriority(last_operator))) ||
            (!opAssociativity(current_operator) && (opPriority(current_operator) < opPriority(last_operator)))))
        {
            output += last_operator + "|";
            operations_.pop();
        }
        else
            break;
    }
    operations_.push(current_operator);
}

void Parser::parse(const std::string& input, std::string& output)
{
    std::stack<std::string> operations_;
    int length = input.length();
    output = "";
    for (int i = 0; i < length; ++i)
    {
        std::string current_substring = { input[i] };
        if (current_substring != " ")
        {
            if (current_substring == "(")
                operations_.push(current_substring);
            else if (current_substring == ")")
                parenthesesBalance(operations_, output);
            else if (isIdent(current_substring))
            {
                int j = 0;
                while (j < length)
                {
                    j = i + 1;
                    char current_symbol = input[j];
                    if (isIdent(current_symbol) || current_symbol == '.')
                        current_substring += current_symbol;
                    else
                        break;
                    i++;
                }
                double val1 = stod(current_substring);
                int val2 = (int)val1;
                if (val1 == val2)
                    output += std::to_string(val2) + "|";
                else
                    output += std::to_string(val1) + "|";
            }
            else if (isLetter(current_substring))
            {
                int j = i + 1;
                while (j < length)
                {
                    j = i + 1;
                    char current_symbol = input[j];
                    if (isLetter(current_symbol))
                        current_substring += current_symbol;
                    else
                        break;
                    i++;
                }
                if (isFunction(current_substring))
                    operations_.push(current_substring);
            }
            else if (isOperator(current_substring))
                operationPriorityArrangment(operations_, current_substring, output);
            else
                throw std::runtime_error("Unknown operation in " + current_substring);
        }
    }
    while (!operations_.empty())
    {
        std::string current_substring = operations_.top();
        operations_.pop();
        if (current_substring == "(" || current_substring == ")")
            throw std::runtime_error("Error: parentheses mismatched");
        output += current_substring + "|";
    }
}

void Parser::evaluate(const std::string& input)
{
    int length = input.length();
    std::vector<std::string> operations_(length);
    std::vector < double > values(length);
    int last_index = 0;
    int iteration_of_calculation = 0;
    for (int i = 0; i < length; ++i)
    {
        std::string current_substring = { input[i] };
        if (isIdent(current_substring))
        {
            double value;
            char c_current = input[i + 1];
            while (c_current != '|')
            {
                current_substring += c_current;
                i++;
                c_current = input[i + 1];
            }
            i++;
            std::istringstream(current_substring) >> value;
            operations_[last_index] = current_substring;
            values[last_index] = value;
            ++last_index;
        }
        else
        {
            if (isLetter(current_substring))
            {
                char c_current = input[i + 1];
                while (c_current != '|')
                {
                    current_substring += c_current;
                    i++;
                    c_current = input[i + 1];
                }
                operations_[last_index] = current_substring;
            }
            i++;
            if (isOperator(current_substring) || isFunction(current_substring))
            {
                int arguments = opBinary(current_substring);
                double value;
                std::string res = "(" + std::to_string(iteration_of_calculation++) + ")";
                std::cout << res << " = ";
                if (last_index < arguments)
                    throw std::runtime_error("Error: insufficient arguments in expression");
                std::string prev_substring = operations_[last_index - 1];
                double prev_value = values[last_index - 1];
                if (arguments == 1)
                {
                    last_index--;
                    value = calculation(current_substring, prev_value, 0);
                    if (opAssociativity(current_substring))
                        std::cout << current_substring << " " << prev_substring << " = " << value << std::endl;
                    else
                        std::cout << prev_substring << " " << current_substring << " = " << value << std::endl;
                }
                else
                {
                    std::string prev_substring1 = operations_[last_index - 2];
                    double prev_value1 = values[last_index - 2];
                    value = calculation(current_substring, prev_value1, prev_value);
                    std::cout << prev_substring1 << " " << current_substring << " ";
                    std::cout << prev_substring << " = " << value << std::endl;
                    last_index -= 2;
                }
                operations_[last_index] = res;
                values[last_index] = value;
                ++last_index;
            }
        }
    }
    if (last_index == 1)
    {
        std::string final_operation = operations_[last_index - 1];
        double final_value = values[last_index - 1];
        last_index--;
        std::cout << "Result : " << final_operation << " = " << final_value << std::endl;
    }
    else
        throw std::runtime_error("Error: too many values entered by the user");
}







