#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include "Stack.cpp"
#include "Utils.cpp"
using namespace std;

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

int main()
{
    string in;
    cin >> in;

    try
    {
        string postfix = infixToPostfix(in);
        cout << "postfix: " << postfix << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}