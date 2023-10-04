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
	if ((acc == true && bin == 2) || (acc == false && bin == 1) )
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

bool Parser::shuntingYard(const std::string& input, std::string& output)
{
    bool interruption = false;
    std::stack<std::string> op_stack;
    int length = input.length();
    output = "";
    for (int i = 0; i < length; ++i) 
    {
        if (interruption == true)
        {
            std::cerr << " Process was interrupted" << std::endl;
            std::cerr << " Please, rewrite expression" << std::endl;
            return false;
        }
        char c = input[i];
        std::string c_str = { c };
        if (c_str != " ") 
        {
            if (c == '(')
            {
                op_stack.push(c_str);
            }
            else if (c == ')')
            {
                bool pe = false;
                while (!op_stack.empty())
                {
                    std::string sc = op_stack.top();
                    op_stack.pop();
                    if (sc == "(")
                    {
                        pe = true;
                        break;
                    }
                    else
                        output += sc + "|";
                }
                if (!pe)
                {
                    std::cout << "Error: parentheses mismatched" << std::endl;
                    interruption = true;
                    return false;
                }
                if (!op_stack.empty())
                {
                    std::string sc = op_stack.top();
                    if (isFunction(sc))
                    {
                        output += sc + "|";
                        op_stack.pop();
                    }
                }
            }
            else if (isIdent(c))
            {
                int j = 0;
                int dot_flag = 0;
                while (j < length)
                {
                    j = i + 1;
                    char c_current = input[j];
                    if (c_current == '.')
                    {
                        dot_flag++;
                        if (dot_flag < 2)
                            c_str += c_current;
                        else
                        {
                            std::cerr << " More than one dot in number :" << c_str << std::endl;
                            interruption = true;
                            break;
                        }
                    }
                    else if (isIdent(c_current))
                        c_str += c_current;
                    else
                        break;
                    i++;
                }
                output += c_str + "|";
            }
            else if (isLetter(c_str))
            {
                int j = i + 1;
                char c_current = input[j];
                while (j<length)
                {
                    j = i + 1;
                    char c_current = input[j];
                    if (isLetter(c_current))
                        c_str += c_current;
                    else
                        break;
                    i++;
                }
                if (isFunction(c_str))
                    op_stack.push(c_str);
            }
            else if (isOperator(c_str)) 
            {
                while (!op_stack.empty()) 
                {
                    std::string sc = op_stack.top();
                    std::string sc_str = { sc };
                    if (isOperator(sc_str) && ((opAssociativity(c_str) && (opPriority(c_str) <= opPriority(sc_str))) ||
                        (!opAssociativity(c_str) && (opPriority(c_str) < opPriority(sc_str))))) 
                    {
                        output += sc_str +"|";
                        op_stack.pop();
                    }
                    else
                        break;
                }
                op_stack.push(c_str);
            }            
            else 
            {
                std::cout << "Unknown token in" << c_str << std::endl;
                interruption = true;
                return false;
            }
        }
    }
    while (!op_stack.empty()) {
        std::string sc = op_stack.top();
        op_stack.pop();
        if (sc == "(" || sc == ")") 
        {
            std::cout << "Error: parentheses mismatched" << std::endl;
            interruption = true;
            return false;
        }
        output += sc + "|";
    }
    return true;
}

bool Parser::executionOrder(const std::string& input) 
{
    int const length = input.length();
    std::vector<std::string> stack(length);
    std::vector < double > stack2(length);
    int sl = 0;
    int rn = 0;
    for (int i = 0; i < length; ++i) 
    {
        char c = input[i];
        std::string c_str = { c };
        if (isIdent(c_str)) 
        {
            double val;
            char c_current = input[i+1];
            while (c_current != '|')
            {

                c_str += c_current;
                i++;
                c_current = input[i+1];
            }
            i++;
            std::istringstream(c_str) >> val;
            stack[sl] = c_str;
            stack2[sl] = val;
            ++sl;
        }
        else 
        {
            if (isLetter(c_str))
            {
                char c_current = input[i + 1];
                while (c_current != '|')
                {
                    c_str += c_current;
                    i++;
                    c_current = input[i + 1];
                }
                stack[sl] = c_str;
            }
            i++;
            if (isOperator(c_str) || isFunction(c_str)) 
            {
                int nargs = opBinary(c_str);
                int Tnargs = nargs;
                double val = 0;
                std::string res = "(" +  std::to_string(rn++) + ")";
                std::cout << res << " = ";

                if (sl < nargs) 
                {
                    std::cout << "Error: insufficient arguments in expression" << std::endl;
                    return false;
                }

                if (nargs == 1)
                {
                    std::string sc = stack[sl - 1];
                    double sc2 = stack2[sl - 1];
                    sl--;
                    val = calculation(c_str, sc2, 0);
                    if(opAssociativity(c_str))
                        std::cout << c_str << " " << sc << " = " << val << std::endl;
                    else
                        std::cout  << sc << " " << c_str  << " = " << val << std::endl;
                }
                else
                {
                    std::string sc1 = stack[sl - 2];
                    double sc21 = stack2[sl - 2];
                    std::cout << sc1 << " " << c << " ";
                    std::string sc2 = stack[sl - 1];
                    double sc22 = stack2[sl - 1];
                    val = calculation(c_str, sc21, sc22);
                    std::cout << sc2 << " = " << val << std::endl;
                    sl -= 2;
                }
                stack[sl] = res;
                stack2[sl] = val;
                ++sl;
            }
        }
    }
    if (sl == 1) {
        std::string sc = stack[sl - 1];
        double sc1 = stack2[sl - 1];
        sl--;
        std::cout << "Result : " << sc << " = " << sc1 << std::endl;
        return true;
    }
    std::cout << "Error: too many values entered by the user" << std::endl;
    return false;
}


