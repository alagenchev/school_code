#include <iostream>
#include "CircularQueue.h"
#include <exception>
#include "MyException.h"

using namespace std;



MyQueue::CircularQueue::CircularQueue()
{
    _queue = new int[5];
    _size = 5;
    _tail = 0;
    _head = 0;
}

MyQueue::CircularQueue::~CircularQueue()
{
    delete [] _queue;
}

int MyQueue::CircularQueue::getSize()
{
    return _size;
}

void MyQueue::CircularQueue::Add(int newElement)
{
    if(_head == _size )
    {
        throw MyException("queue is full, can't add!");
    }
    else
    {
        _queue[_tail] = newElement;
    }
    _head++;

}

int MyQueue::CircularQueue::Remove()
{
    if(_head == tail)
    {
        throw MyException("queue is empty, can't remove");
    }

    _head--;
}

int MyQueue::CircularQueue::Peek()
{
}

string MyQueue::CircularQueue::toString()
{
    string temp = "";
    for(int i = _tail; i < _head; i++)
    {
        temp+=_queue[i];
        if(i < _size - 1)
        {
            temp+=", ";
        }
    }
    return temp;
}
