#include "Utils.h"
#include "Stack.h"
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <string>

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

int factorial(int n)
{
    if (n < 0)
        throw std::invalid_argument("negative number for factorail\n");

    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}
string infixToPostfix(const string &infix)
{
    Stack stack(infix.length()); // stack for holding operators
    string postfix = "";
    for (char c : infix)
    {
        if (isalnum(c)) // if the character is a number or variable
        {
            postfix += c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop();
            }
            stack.pop(); // delete the (
        }
        else // if it was operator
        {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
            {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }

    // add remaining operators on the stack to the postfix
    while (!stack.isEmpty())
    {
        postfix += stack.pop();
    }
    return postfix;
}

int evaluatePostfix(const string &postfix)
{
    Stack stack(postfix.length());

    for (char c : postfix)
    {
        if (isdigit(c)) // if it's a number
        {
            stack.push(c - '0');
        }
        else if (c == '!')
        {
            int num = stack.pop();
            stack.push(factorial(num));
        }
        else
        {
            float num1 = stack.pop();
            float num2 = stack.pop();
            switch (c)
            {
            case '+':
                stack.push(num1 + num2);
                break;
            case '-':
                stack.push(num2 - num1);
                break;
            case '*':
                stack.push(num1 * num2);
                break;
            case '/':
                if (num1 == 0)
                {
                    throw std::runtime_error("division by 0\n");
                }
                stack.push(num2 / num1);
                break;
            case '^':
                stack.push(pow(num2, num1));
                break;

            default:
                throw std::invalid_argument("unknown argument\n");
            }
        }
    }
    return stack.peek();
}
