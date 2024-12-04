#include "Stack.h"
#include <stdexcept> // for management of exceptions

Stack::Stack(int size)
{
    top = -1;
    capacity = size;
    arr = new double[capacity];
}

Stack::~Stack()
{
    delete[] arr;
}

bool Stack::isEmpty()
{
    return top == -1;
}
bool Stack::isFull()
{
    return top == capacity - 1;
}

void Stack::push(double value)
{
    if (isFull())
    {
        throw std::overflow_error("Stack is full");
    }
    arr[++top] = value;
}

double Stack::pop()
{
    if (isEmpty())
    {
        throw std::underflow_error("Stack is empty");
    }
    return arr[top--];
}
double Stack::peek()
{
    if (isEmpty())
    {
        throw std::underflow_error("Stack is empty");
    }
    return arr[top];
}