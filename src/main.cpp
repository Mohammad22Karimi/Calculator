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
    oss << fixed << setprecision(10) << number;
    string str = oss.str();

    // find the position of the decimal point
    size_t decimalPointPos = str.find('.');
    if (decimalPointPos != string::npos)
    {
        // Find the position of the last non-zero character after the decimal point
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
    fill(arr, arr + 26, 0.0); // initialize variable with 0.0 by default.

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
            int index = variable[0] - 'a'; // Convert variable to array index
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
            char letter = 'A' + i; // Convert to uppercase letter
            cout << letter << "=";
            ostringstream oss;
            oss << fixed << setprecision(12) << arr[i];
            string ns = oss.str();
            size_t dp = ns.find('.');
            if (dp != string::npos && dp + 5 <= ns.length())
            {
                bool b = false;
                for (int i = dp + 6; i < ns.length() - 2; i++)
                {
                    if (ns[i] != '0')
                    {
                        b = true;
                        break;
                    }
                }
                if (b == true)
                {
                    string truncatedStr = ns.substr(0, dp + 6);
                    string truncateStr2 = removeTrailingZeros(stod(truncatedStr));
                    truncateStr2 = truncateStr2.substr(0, dp + 5);
                    cout << truncateStr2 << endl;
                }
                else
                {
                    string truncatedStr = ns.substr(0, dp + 5);
                    cout << removeTrailingZeros(stod(truncatedStr)) << endl;
                }
            }
            else
            {
                cout << removeTrailingZeros(arr[i]) << endl;
            }
        }
    }

    return 0;
}
