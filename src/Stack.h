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
    void push(char value);
    char pop();
    char peek();

private:
    int top;
    int capacity;
    char *arr;
};

#endif