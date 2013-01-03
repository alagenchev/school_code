
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

        System.out.println("unsorted:");
        for(int i = 0; i< elements.length;i++)
        {
            System.out.printf("%d: %d\n", i, elements[i]);
        }


        RadixSort sort = new RadixSort();

        sort.Sort(elements);

        System.out.println("sorted:");
        for(int i = 0; i< elements.length;i++)
        {
            System.out.printf("%d: %d\n", i, elements[i]);
        }
    }


}
