
class Main
{
    public static void main(String []args)
    {
        String []temp_elements = args[0].split(",");
        int []elements = new int[temp_elements.length];

        for(int i = 0; i< elements.length;i++)
        {
            elements[i] = Integer.parseInt(temp_elements[i]);
        }

        

        QuickSort sort = new QuickSort();

        sort.Sort(0, elements.length - 1, elements);
        
        for(int i : elements)
        {
            System.out.println(i);
        }
    }

}
