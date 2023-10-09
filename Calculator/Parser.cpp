#include "Parser.h"

int Parser::opPriority(const std::string& symbol)
{
    return this->operations->getPriority(symbol);
}

bool Parser::opAssociativity(const std::string& symbol)
{
    return this->operations->getAssociativity(symbol);
}

int Parser::opBinary(const std::string& symbol)
{
    return this->operations->getBinary(symbol);
}

bool Parser::isOperator(const std::string& symbol)
{
    if (symbol == "(" || symbol == ")")
        return false;
    bool acc = this->opAssociativity(symbol);
    int bin = this->opBinary(symbol);
    if ((acc == true && bin == 2) || (acc == false && bin == 1))
        return true;
    return false;
}

bool Parser::isFunction(const std::string& symbol)
{
    if (symbol == "(" || symbol == ")")
        return false;
    if (this->opAssociativity(symbol) == true && this->opBinary(symbol) == 1)
        return true;
    return false;
}

bool Parser::isIdent(const std::string& symbol)
{
    return (symbol >= "0" && symbol <= "9");
}

bool Parser::isIdent(char symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

bool Parser::isLetter(char symbol)
{
    return (symbol >= 'a' && symbol <= 'z');
}

bool Parser::isLetter(const std::string& symbol)
{
    return (symbol >= "a" && symbol <= "z");
}

double Parser::calculation(const std::string& symbol, double a, double b)
{
    return this->operations->calculation(symbol, a, b);
}

bool Parser::parenthesesBalance(std::stack<std::string>& operations_, std::string& output)
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
    {
        std::cerr << "Error: parentheses mismatched" << std::endl;
        return false;
    }
    if (!operations_.empty())
    {
        symbols = operations_.top();
        if (isFunction(symbols))
        {
            output += symbols + "|";
            operations_.pop();
        }
    }
    return true;
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

bool Parser::parse(const std::string& input, std::string& output)
{
    std::stack<std::string> operations_;
    int length = input.length();
    output = "";
    for (int i = 0; i < length; ++i)
    {
        char current_symbol = input[i];
        std::string current_substring = { current_symbol };
        if (current_substring != " ")
        {
            if (current_symbol == '(')
                operations_.push(current_substring);
            else if (current_symbol == ')')
            {
                if (!parenthesesBalance(operations_, output))
                    return false;
            }
            else if (isIdent(current_symbol))
            {
                int j = 0;
                while (j < length)
                {
                    j = i + 1;
                    char c_current = input[j];
                    if (isIdent(c_current) || c_current == '.')
                        current_substring += c_current;
                    else
                        break;
                    i++;
                }
                output += std::to_string(stod(current_substring)) + "|";
            }
            else if (isLetter(current_substring))
            {
                int j = i + 1;
                char c_current = input[j];
                while (j < length)
                {
                    j = i + 1;
                    char c_current = input[j];
                    if (isLetter(c_current))
                        current_substring += c_current;
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
            {
                std::cerr << "Unknown token in" << current_substring << std::endl;
                return false;
            }
        }
    }
    while (!operations_.empty())
    {
        std::string sc = operations_.top();
        operations_.pop();
        if (sc == "(" || sc == ")")
        {
            std::cerr << "Error: parentheses mismatched" << std::endl;
            return false;
        }
        output += sc + "|";
    }
    return true;
}

bool Parser::evaluate(const std::string& input)
{
    int length = input.length();
    std::vector<std::string> operations_(length);
    std::vector < double > values(length);
    int last_index = 0;
    int iteration_of_calculation = 0;
    for (int i = 0; i < length; ++i)
    {
        char current_symbol = input[i];
        std::string current_substring = { current_symbol };
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
                double value = 0;
                std::string res = "(" + std::to_string(iteration_of_calculation++) + ")";
                std::cout << res << " = ";
                if (last_index < arguments)
                {
                    std::cerr << "Error: insufficient arguments in expression" << std::endl;
                    return false;
                }
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
                    std::cout << prev_substring1 << " " << current_symbol << " ";
                    value = calculation(current_substring, prev_value1, prev_value);
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
        std::cerr << "Result : " << final_operation << " = " << final_value << std::endl;
        return true;
    }
    std::cerr << "Error: too many values entered by the user" << std::endl;
    return false;
}


