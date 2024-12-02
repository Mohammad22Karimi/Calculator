#include "Utils.h"
#include <stdexcept>

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

int factorial(int number)
{
    if (n < 0)
        throw std::invalid_argument("negative number for factorail\n");

    if (n == 0 || n == 1)
        return 1;
    return number * factorial(number - 1);
}
