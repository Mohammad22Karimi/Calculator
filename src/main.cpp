#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include "Stack.cpp"
#include "Utils.cpp"

using namespace std;

int main()
{
    string in;
    cin >> in;
    try
    {
        string po = infixToPostfix(in);
        cout << "postfix: " << po << endl;

        int result = evaluatePostfix(po);
        cout << "resutl: " << result << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}