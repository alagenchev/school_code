import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        int [] arr1 = {5,4,3,8,10,20,12,1};
        int [] arr2 = {5,4,3,8,13,7,6,9,10,111,1123,112};

        HashSet<Integer> hashSet = new HashSet<Integer>();

        for(int i : arr1)
        {
            hashSet.add(i);
        }

        System.out.print("Common: ");
        for(int i : arr2)
        {
            if(hashSet.contains(i))
            {
                System.out.print(i+", ");
            }
        }
        System.out.println();

    }
}
