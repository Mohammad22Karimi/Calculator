#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include <iomanip>
#include <sstream>
#include "Stack.cpp"
#include "Utils.cpp"
#include <cmath>
#include <algorithm>

using namespace std;

double arr[26]; // a-z: 26 and A-Z: 26
string removeTrailingZeros(double number)
{
    ostringstream oss;
    oss << fixed << setprecision(4) << number;
    string str = oss.str();

    // find the position of the decimal point
    size_t decimalPointPos = str.find('.');
    if (decimalPointPos != string::npos)
    { // Find the position of the last non-zero character after the decimal point
        size_t lastNonZeroPos = str.find_last_not_of('0');
        if (lastNonZeroPos != string::npos && lastNonZeroPos > decimalPointPos)
        {
            str.erase(lastNonZeroPos + 1);
        }
        else
        {
            // If all characters after the decimal point are zeros, remove the decimal point as well
            str.erase(decimalPointPos);
        }
    }
    return str;
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
        if (equalPosition == string::npos)
        {
            double result = evaluateExpression(input);
            cout << result << endl;
            n--;
            continue;
        }
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
            double number = arr[i];
            string result = removeTrailingZeros(number); //
            cout << fixed << result << endl;
        }
    }

    return 0;
}