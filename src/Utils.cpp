#include "Utils.h"

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