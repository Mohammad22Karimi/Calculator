#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <string>
using std::string;

int precedence(char op);
int factorial(int number);
string infixToPostfix(const string &infix);
int evaluatePostfix(const string &postfix);
#endif