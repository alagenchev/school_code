#include <iostream>
#include "CircularQueue.h"
#include <exception>
#include "MyException.h"
#include <sstream>
#include <stdlib.h>

using namespace std;



MyQueue::CircularQueue::CircularQueue()
{
	_queue = new int[5];
	_size = 5;
	_tail = 0;
	_head = 0;
	_count = 0;

	for(int i = 0; i < 5; i++)
	{
		_queue[i] = -666;
	}
}

MyQueue::CircularQueue::~CircularQueue()
{
	delete _queue;
}

int MyQueue::CircularQueue::getSize()
{
	return _size;
}

void MyQueue::CircularQueue::Add(int newElement)
{
	cout<<"adding: "<<newElement<<" size is: " <<_size<<" count is: " << _count<<endl;
	if(_count == _size && _tail > _head)
	{
		cout<<"REALLOCATING W REALLOC"<<endl;
		_size++;
		_queue = (int *) realloc(_queue, _size * sizeof(int)); 
		_queue[_tail] = newElement;
	}
	else if(_count == _size && _tail == _head)
	{
		cout<<"Second type of Reallocation"<<endl;
		_size++;
		int *newPtr = (int *) calloc(_size, sizeof(int));

		for(int i = _head; i < _size; i++)
		{
			newPtr[i - _head] = _queue[i];

			cout<<"newPtr["<<i - _head<<"] = "<<newPtr[i - _head]<<endl;
		}

	}
	else if(_tail==_size && _head != 0)
	{
		_tail = 0;
		_queue[0] = newElement;
	}
	else
	{
		_queue[_tail] = newElement;
	}
	_count++;
	_tail++;

}

int MyQueue::CircularQueue::Remove()
{
	if(_head == _tail)
	{
		throw MyException("queue is empty, can't remove");
	}
	int temp = _queue[_head];

	_queue[_head] = -666;
	_count--;
	_head++;
	return temp;
}

int MyQueue::CircularQueue::Peek()
{
}

string MyQueue::CircularQueue::toString()
{
	string temp = "FRONT: ";
	if(_tail > _head)
	{
		for(int i = _head; i < _tail && i < _size; i++)
		{
			std::stringstream ss;
			ss<<_queue[i];
			temp+= ss.str();
			if(i < _tail - 1 && i < _size - 1)
			{
				temp+=", ";
			}
		}
	}
	else
	{
		for(int i = _head; i < _size; i ++)
		{
			std::stringstream ss;
			ss<<_queue[i];
			temp+= ss.str();
			if(i < _tail - 1 || i < _size - 1)
			{
				temp+=", ";
			}
		}

		for(int i = 0; i < _tail; i ++)
		{
			if(i == 0)
			{
				temp+=", ";
			}
			std::stringstream ss;
			ss<<_queue[i];
			temp+= ss.str();
			if(i < _tail - 1)
			{
				temp+=", ";
			}
		}

	}

	temp+=" :TAIL| Count:";
	std::stringstream s;
	s<<_count;
	temp+=s.str();

	return temp;
}

void MyQueue::CircularQueue::printAll()
{
	cout<<"ALL: FRONT: ";
	for(int i = 0; i < _size;i++)
	{
		cout<<_queue[i];
		if(i < _size - 1)
		{
			cout<<", ";
		}
	}

	cout<<" :END"<<" count:"<<_count<<endl;

}

