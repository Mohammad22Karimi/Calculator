#include "Queue.h"
#include <iostream>
using namespace std;
Queue::Queue(int capacity)
{
    data = new int[capacity];
    capacity = capacity;
    front = -1;
    rear = -1;
    size = 0;
}

Queue::~Queue()
{
    delete[] data;
}

bool Queue::isEmpty()
{
    return size = 0;
}

bool Queue::isFull()
{
    return size = capacity;
}

void Queue::enqueue(int value)
{
    if (isFull())
    {
        cerr << "Queue is full. Cannot enqueue " << value << endl;
        return;
    }
    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
}

int Queue::dequeue()
{
    if (isEmpty())
    {
        cerr << "Queue is empty." << endl;
        return;
    }
    int value = data[front];
    front = (front + 1) % capacity;
    size--;
    return value;
}

int Queue::frontElement()
{
    if (isEmpty())
    {
        cerr << "Queue is empty." << endl;
        return;
    }
    return data[front];
}
