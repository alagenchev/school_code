class Person
{
    public int Height;
    public int Weight;

    public Person(int height, int weight)
    {
        Height = height;
        Weight = weight;
    }

    @Override
    public String toString()
    {
        return String.format("(%d, %d)", Height, Weight);
    }
}
