
class Main
{
    public static void main(String []args)
    {
        int toFind = Integer.parseInt(args[1]);
        System.out.println("will be finding: " + toFind);
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

        int index = findBreakIndex(elements);

        System.out.printf("found break index at: %d\n", index);

        int foundIndex = -1;

        if(index > 0)
        {
            int start = elements[0];
            int end = elements[elements.length - 1];
            int middle = elements[index];

            if(toFind <= middle && toFind >=start)
            {
                //search first part
                foundIndex = binarySearch(elements, toFind, 0, index);
            }
            else if(toFind >= middle && toFind <= end)
            {
                //search second part
                foundIndex = binarySearch(elements, toFind, index, elements.length - 1);
            }
        }
        else
        {
            //search normally
            foundIndex = binarySearch(elements, toFind, 0, elements.length - 1);
        }

        System.out.println("found index: " + foundIndex);

    }

    public static int binarySearch(int []arr, int value, int start, int end)
    {
        if(start > end)
        {
            return -1;
        }
        int middle = (start + end)/2;
        if(arr[middle] == value)
        {
            return middle;
        }

        if(arr[middle] > value)
        {
            //search lower part
            return binarySearch(arr, value, start, middle - 1);
        }
        else
        {
            //search upper part
            return binarySearch(arr, value, middle +1, end);
        }
    }
    public static int findBreakIndex(int [] arr)
    {
        for(int i = 1; i < arr.length; i++)
        {
            if(arr[i - 1] > arr[i])
            {
                return i;
            }
        }

        return -1;
    }

}
