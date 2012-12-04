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


	queue.Remove();
	queue.Remove();

	//queue.printAll();
	queue.Add(7);
	queue.Add(8);
	queue.Add(9);

//	queue.printAll();
//	cout<<"queue: "<<queue.toString()<<endl;
    
}
