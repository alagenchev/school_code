import java.util.*;

class QuickSort
{
    public void Sort(int start, int end, int[] arr)
    {
        if(start >= end)
        {
            return;
        }
        int pivotIndex = partition(start, end, arr);

        Sort(start, pivotIndex - 1, arr);
        Sort(pivotIndex + 1, end, arr);

    }

    private int partition(int start, int end, int[] arr)
    {

        //random pivot selection gives better performance
        long seed = (long)Calendar.MILLISECOND;
        Random ran = new Random(seed);

        int pivotIndex = ran.nextInt( end - start);
        pivotIndex = start + pivotIndex;

        //put pivot away at the end
        int temp = arr[end];
        arr[end] = arr[pivotIndex];
        arr[pivotIndex] = temp;

        int pivotValue = arr[end];

        //this is a pointer to the last element that is 
        //smaller than pivot
        int indexOfSmallerThanPivot = start - 1;

        for(int index = start; index < end ; index++)
        {
            if(arr[index] <= pivotValue)
            {
                //move index up to make room for new
                //element smaller than pivot
                indexOfSmallerThanPivot++;

                //swap the element that was bigger than pivot
                //with element that is smaller than pivot
                temp = arr[indexOfSmallerThanPivot];
                arr[indexOfSmallerThanPivot] = arr[index];
                arr[index] = temp;
            }
        }

        //we'll put the pivot at the first element after 
        //the numbers smaller than pivot
        pivotIndex = indexOfSmallerThanPivot + 1;

        //swap that element with the pivot that was stowed away
        //at the end
        temp = arr[pivotIndex];
        arr[pivotIndex] = arr[end];
        arr[end] = temp;

        return pivotIndex;
    }
    
}
