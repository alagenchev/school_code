#include<iostream>
#include "CircularQueue.h"

using namespace std;
using namespace MyQueue;

int main()
{

    CircularQueue queue = CircularQueue();
	queue.Add(1);
	queue.Add(2);
	queue.Add(3);
	queue.Add(4);
	queue.Add(5);

	int i = queue.Remove();

	queue.printAll();

	queue.Remove();
	queue.Remove();

	queue.printAll();
	cout<<"queue: "<<queue.toString()<<endl;
	queue.Add(6);
	queue.Add(6);

	queue.printAll();
	cout<<"queue: "<<queue.toString()<<endl;
    
}
