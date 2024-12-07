#ifndef QUEUE_H
#define QUEUE_H

#pragma once

class Queue
{
public:
    Queue(int capacity);
    ~Queue();
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    int dequeue();
    int frontElement();

private:
    int *data;
    int capacity;
    int front;
    int rear;
    int size;
};

#endif