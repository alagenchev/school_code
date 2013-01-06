class Main
{
    public static void main(String []args) throws Exception
    {
        Queue queue = new Queue();

        queue.Add(1);
        queue.Add(2);
        queue.Add(3);
        queue.Add(4);
        queue.Add(5);

        queue.Add(5);
        queue.Print();
    }
}
