#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include <iomanip>
#include <sstream>
#include "Stack.cpp"
#include "Utils.cpp"
#include "Queue.cpp"
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

bool isAssigned[26] = {false};
double arr[26]; // a-z: 26 and A-Z: 26
const int MAX_VARIABLE = 26;
int inDegree[MAX_VARIABLE];             // تعداد ورودی برای هر متغیر
vector<int> dependencies[MAX_VARIABLE]; // وابستگی ها

struct Equation
{
    int variable;      // variable left side
    string expression; // expression right side
};

void build_dependencies(vector<Equation> &equations)
{
    fill(inDegree, inDegree + MAX_VARIABLE, 0);
    for (int i = 0; i < MAX_VARIABLE; ++i)
    {
        dependencies[i].clear();
    }
    for (auto &eq : equations)
    {
        int ch = eq.variable;
        for (char c : eq.expression)
        {
            if (isalpha(c))
            {
                int ch2 = tolower(c) - 'a';
                dependencies[ch2].push_back(ch);
                inDegree[ch]++;
            }
        }
    }
}
vector<int> topologicalSort()
{
    Queue q(MAX_VARIABLE);
    vector<int> sortedOrder;
    vector<bool> visited(MAX_VARIABLE, false);
    // Add variables with zero entry level to the queue
    for (int i = 0; i < MAX_VARIABLE; i++)
    {
        if (inDegree[i] == 0)
        {
            q.enqueue(i);
        }
    }
    while (!q.isEmpty())
    {
        int current = q.dequeue();
        sortedOrder.push_back(current);
        visited[current] = true;
        // Reduce the input degree of dependent variables
        for (int neighbor : dependencies[current])
        {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
            {
                q.enqueue(neighbor);
            }
        }
    }
    for (int i = 0; i < MAX_VARIABLE; i++)
    {
        if (!visited[i] && inDegree[i] > 0)
        {
            cerr << "Circular Dependency" << endl;
            exit(1);
        }
    }
    return sortedOrder;
}
void evaluateSortedEquations(vector<Equation> &equations, vector<int> &sortedOrder)
{ // Solve the variable of each equation
    for (int variableIndex : sortedOrder)
    {
        char variableName = variableIndex + 'a';
        string expression;
        bool found = false;
        // Find the expression related to the variable
        for (auto &eq : equations)
        {
            if (eq.variable == variableIndex)
            {
                expression = eq.expression;
                found = true;
                break;
            }
        }
        try
        {
            if (found)
            {
                double value = evaluateExpression(expression);
                arr[variableIndex] = value;
                isAssigned[variableIndex] = true;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(1);
        }
    }
    // Calculate the value of the expression
}
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
void checkError(const string &input)
{
    // checking =
    size_t equalPos = input.find('=');
    if (equalPos == string::npos)
    {
        cerr << "Invalid Format" << endl;
        exit(1);
    }
    string v = input.substr(0, equalPos);
    string e = input.substr(equalPos + 1);
    if (v.length() != 1 || !isalpha(v[0]))
    {
        cerr << "Invalid Format" << endl;
        exit(1);
    }
    int open = 0, close = 0;
    for (char c : e)
    {
        if (c == '(')
            open++;

        if (c == ')')
            close++;

        if (close > open)
        {
            cerr << "Invalid Format" << endl;
            exit(1);
        }
    }
    if (open != close)
    {
        cerr << "Invalid Format" << endl;
        exit(1);
    }
}
void readEquation(vector<Equation> &equations, int n)
{
    while (n > 0)
    {
        string input;
        cin >> input;
        if (input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/^!=().") != string::npos)
        {
            cerr << "Invalid Input" << endl;
            exit(1);
        }
        checkError(input);
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
        int varIndex = variable[0] - 'a';
        if (isAssigned[varIndex])
        {
            for (auto &eq : equations)
            {
                if (eq.variable = varIndex)
                {
                    cerr << "Inconsistency" << endl;
                    exit(1);
                }
            }
        }
        isAssigned[varIndex] = true;

        Equation E;
        E.variable = varIndex;
        E.expression = expression;
        equations.push_back(E);
        n--;
    }
}
int main()
{
    // cin.ignore(); // consume newline character
    int n;
    cin >> n;

    fill(arr, arr + 26, 0.0); // initialize variable with 0.0 by default.
    vector<Equation> equation;
    readEquation(equation, n);
    build_dependencies(equation);
    vector<int> sortedOrder = topologicalSort();
    evaluateSortedEquations(equation, sortedOrder);
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
