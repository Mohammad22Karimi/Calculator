#include <iostream>
#include "Stack.cpp"
using namespace std;

int main()
{
    // testing Stack:
    Stack stack(5);
    try
    {
        stack.push('a');
        stack.push('b');
        stack.push('c');

        cout << "top element: " << stack.peek() << endl;
        stack.pop();
        cout << "top element after pop: " << stack.peek() << endl;
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}