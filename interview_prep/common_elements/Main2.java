import java.util.*;

public class Main2
{
    public static void main(String[] args)
    {
        int [] arr1 = {5,4,3,8,10,20,12,1};
        int [] arr2 = {5,4,3,8,13,7,6,9,10,111,1123,112, 20};

        HashSet<Integer> hashSet = new HashSet<Integer>();

        for(int i : arr1)
        {
            hashSet.add(i);
        }

        System.out.print("Common: ");
        
        Arrays.sort(arr2);

        for(int i : arr1)
        {
            if(isPresent(i, arr2, 0, arr2.length-1))
            {
                System.out.print(i + ", ");
            }

        }
        System.out.println();

    }

    public static boolean isPresent(int element, int [] arr, int startIndex, int endIndex)
    {
        //System.out.println("start: " + startIndex + " end: "+ endIndex);
        if(startIndex == endIndex && arr[startIndex] != element)
        {
            return false;
        }
        else if(startIndex == endIndex && arr[startIndex] == element)
        {
            return true;
        }

        if(arr[(startIndex + endIndex)/2] == element)
        {
            return true;
        }
        else if(arr[(startIndex + endIndex)/2] > element)
        {
            return isPresent(element, arr, startIndex, (startIndex + endIndex)/2);
        }
        else
        {
            return isPresent(element, arr, (startIndex + endIndex)/2 + 1, endIndex);
        }

    }
}
