#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include <iomanip>
#include <sstream>
#include "Stack.cpp"
#include "Utils.cpp"

using namespace std;

double arr[26]; // a-z: 26 and A-Z: 26

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
        variable[0] = tolower(variable[0]);
        try
        {
            double value = evaluateExpression(expression);
            int index = getArrayIndex(variable[0]);
            arr[index] = value;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            n--;
            continue;
        }
        n--;
    }

    for (int i = 0; i < 26; i++)
    {
        if (arr[i] != 0)
        {
            char letter = 'A' + i; // convert to capital letter
            cout << letter << "=";

            if (arr[i] == floor(arr[i]))
            {
                cout << fixed << setprecision(0) << arr[i] << endl;
            }
            else
            {
                cout << fixed << setprecision(4) << arr[i] << endl;
            }
        }
    }

    return 0;
}