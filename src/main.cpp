#include <iostream>
#include <string>
#include <cctype> // for checking numbers and variables
#include "Stack.cpp"
#include "Utils.cpp"

using namespace std;

const double PI = 3.14159;
const double EN = 2.71828;

double array[52]; // a-z: 26 and A-Z: 26

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

    return 0;
}