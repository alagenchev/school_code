#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include <string>

using namespace std;

namespace MyQueue
{
    class CircularQueue
    {
        private:
            int *_queue;
            int _size;
            int _tail;
            int _head;
			int _count;
        public:
            int getSize();
            CircularQueue();
            void Add(int newElement);
            int Remove();
            int Peek();
		   	string toString();
			void printAll();
            ~CircularQueue();
    };
};

#endif
