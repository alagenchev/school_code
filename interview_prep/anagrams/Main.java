import java.util.*;
class Main
{
    public static void main(String []args)
    {
        String []elements = args[0].split(",");

        
        QuickSort sort = new QuickSort();

        sort.Sort(0, elements.length - 1, elements);
        //Arrays.sort(elements, new AnagramComparator());
        
        for(String i : elements)
        {
            System.out.println(i);
        }
    }

}
