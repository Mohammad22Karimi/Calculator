#ifndef STACK_H
#define STACK_H

#pragma once

class Stack
{
public:
    Stack(int size); // constructor
    ~Stack();        // destructor

    bool isEmpty();
    bool isFull();
    void push(double value);
    double pop();
    double peek();

private:
    int top;
    int capacity;
    double *arr;
};

#endif