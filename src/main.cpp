#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include <iomanip>
#include <sstream>
#include "Stack.cpp"
#include "Utils.cpp"

using namespace std;

const double PI = 3.14159;
const double EN = 2.71828;

double arr[52]; // a-z: 26 and A-Z: 26

int getArrayIndex(char v)
{
    if (v >= 'a' && v <= 'z')
    {
        return v - 'a';
    }
    if (v >= 'A' && v <= 'Z')
    {
        return v - 'A' + 26;
    }
    throw invalid_argument("invalid variable name");
}
int main()
{
    int n;
    cin >> n;
    fill(arr, arr + 52, 0.0); // initialize variable with 0.0 by defult.

    while (n > 0)
    {
        string input;
        cin.ignore();
        getline(cin, input);
        size_t equalPosition = input.find('=');
        string variable = input.substr(0, equalPosition);
        string expression = input.substr(equalPosition + 1);

        try
        {
            double value = evaluatePostfix(expression);
            int index = getArrayIndex(variable[0]);
            arr[index] = value;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (arr[i] != 0)
        {
            cout << char('a' + i) << "=" << fixed << setprecision(4) << arr[i] << endl;
        }
    }
    return 0;
}