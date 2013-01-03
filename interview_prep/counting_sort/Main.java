
class Main
{
    public static void main(String []args)
    {
        int maxValue = Integer.parseInt(args[1]);
        String []temp_elements = args[0].split(",");
        int []elements = new int[temp_elements.length];

        for(int i = 0; i< elements.length;i++)
        {
            elements[i] = Integer.parseInt(temp_elements[i]);
        }

        for(int i = 0; i< elements.length;i++)
        {
            System.out.printf("%d: %d\n", i, elements[i]);
        }


        CountingSort sort = new CountingSort();

        int [] result = sort.Sort(elements, maxValue);

        for(int i = 0; i< result.length;i++)
        {
            System.out.printf("%d: %d\n", i, result[i]);
        }
    }


}
