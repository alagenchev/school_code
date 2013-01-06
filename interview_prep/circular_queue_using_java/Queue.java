class Queue
{
    int _head;
    int _tail;
    int _size;
    int []arr;
    public Queue()
    {
        _size = 0;
        arr = new int[5];
        _head = 0;
        _tail = 0;
    }

    public void Add(int element) throws Exception
    {
        if(_size >= arr.length)
        {
            int [] newArr = new int[arr.length + 5];
            int i = 0;

            while(i < _size)
            {
                newArr[i++] = arr[_head++];
                _head = _head % _size;
            }

            _tail = i;
            _head = 0;
            arr = newArr;
        }

        arr[_tail] = element;
        _tail++;
        _tail = _tail % arr.length;
        _size++;

    }

    public int Remove() throws Exception
    {
        if(_size > 0)
        {
            _size--;
            int temp = arr[_head];
            _head++;
            _head = _head % arr.length;
            return temp;
        }
        throw new Exception("stack is empty. Can't remove");
    }

    public void Print()
    {
        String temp;

        System.out.println("Head: " + _head + ", Tail: " + _tail);
        for(int i = 0; i < arr.length; i++)
        {
            System.out.print(arr[i] + ", ");
        }
        System.out.println();
    }
}
