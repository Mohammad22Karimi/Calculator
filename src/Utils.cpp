#include "Utils.h"
#include "Stack.h"
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>

const double PI = 3.14159;
const double EN = 2.71828;

extern double arr[26]; // a-z: 26 and A-Z: 26

int precedence(char op)
{
    if (op == '!')
        return 4;
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

double factorial(double n)
{
    if (n < 0)
        throw std::invalid_argument("negative number for factorail\n");

    if (n == 0 || n == 1)
        return 1;
    double result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}
string infixToPostfix(const string &infix)
{
    Stack stack(infix.length()); // stack for holding operators
    string postfix = "";
    string number = "";
    for (size_t i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if (isalpha(c))
        {
            number += c;

            if (i + 1 == infix.length() || !isalpha(infix[i + 1]))
            {
                if (number == "PI" || number == "EN")
                {
                    postfix += number + " ";
                }
                else
                {
                    postfix += number + " ";
                }
                number = "";
            }
        }
        else if (isdigit(c) || c == '.') // number of decimal
        {
            number += c;
        }
        else
        {
            if (!number.empty())
            {
                postfix += number + " ";
                number = "";
            }
            if (c == '(')
            {
                stack.push(c);
            }
            else if (c == ')')
            {
                while (!stack.isEmpty() && stack.peek() != '(')
                {
                    postfix += stack.pop();
                    postfix += " ";
                }
                stack.pop(); // delete the (
            }
            else // if it was operator
            {
                while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
                {
                    postfix += stack.pop();
                    postfix += " ";
                }
                stack.push(c);
            }
        }
    }

    if (!number.empty())
    {
        postfix += number + " ";
    }
    // add remaining operators on the stack to the postfix
    while (!stack.isEmpty())
    {
        postfix += stack.pop();
        postfix += " ";
    }
    return postfix;
}

int getArrayIndex(char v)
{
    if (v >= 'A' && v <= 'Z')
    {
        v = tolower(v); // convert to small letter
    }
    if (v >= 'a' && v <= 'z')
    {
        return v - 'a';
    }
    throw std::invalid_argument(std::string("invalid variable name: ") + v);
}

double evaluatePostfix(const string &postfix)
{
    Stack stack(postfix.length());

    string number;
    std::stringstream numberStream(postfix);

    while (numberStream >> number)
    {
        if (isdigit(number[0]) || (number[0] == '-' && number.size() > 1))
        { // if it was a number
            stack.push(std::stod(number));
        }
        else if (number == "PI")
        {
            stack.push(PI);
        }
        else if (number == "EN")
        {
            stack.push(EN);
        }
        else if (isalpha(number[0]))
        {
            int index = getArrayIndex(number[0]);
            stack.push(arr[index]);
        }
        else
        { // operator
            if (number == "!")
            {
                double num = stack.pop();
                stack.push(factorial(num));
            }
            else
            {
                double num1 = stack.pop();
                double num2 = stack.pop();
                if (number == "+")
                {
                    stack.push(num1 + num2);
                }
                else if (number == "-")
                {
                    stack.push(num2 - num1);
                }
                else if (number == "*")
                {
                    stack.push(num1 * num2);
                }
                else if (number == "/")
                {
                    if (num1 == 0)
                    {
                        throw std::runtime_error("division by 0\n");
                    }
                    stack.push(num2 / num1);
                }
                else if (number == "^")
                {
                    stack.push(std::pow(num2, num1));
                }
            }
        }
    }
    if (stack.isEmpty())
    {
        throw std::runtime_error("invalid expression\n");
    }
    return stack.pop();
}

double evaluateExpression(const string &expression)
{
    string postfix = infixToPostfix(expression); // convert to postfix
    return evaluatePostfix(postfix);
}
