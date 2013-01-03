import java.util.*;
class RadixSort
{
    private ArrayList<ArrayDeque<Integer>> buckets;
    private int bucketSize;

    public RadixSort()
    {
        buckets  = new ArrayList<ArrayDeque<Integer>>();
        //we are going to use base 10 for simplicity
        //base 2 is faster for computers because we
        //can use shifts
        bucketSize = 10; 

        for(int i = 0; i < bucketSize; i++)
        {
            //add as many buckets as our base numbering system
            buckets.add(new ArrayDeque<Integer>());
        }
    }

    public void Sort(int []unsortedArray)
    {
        int maxDigitLength = getMaxNumberOfDigits(unsortedArray);


        for(int digitLocation = 0; digitLocation < maxDigitLength; digitLocation++)
        {

            //you can also use counting sort with complete
            //items here to use counting sort as a subroutine
            //of radix sort. I'm using buckets here similar
            //to wikipedia's page, since I haven't yet implemented
            //counting sort on full items

            for(int unsortedNumber : unsortedArray)
            {
                //separate numbers in queues based on the
                //particular digits we are sorting/separating them on
                int digitToSortOn = getDigit(unsortedNumber,digitLocation);

                buckets.get(digitToSortOn).add(unsortedNumber);
            }

            int i = 0;

            for(int j = 0; j< bucketSize; j++)
            {
                //take out all numbers from the queues and
                //put them back in the array in sorted order
                ArrayDeque<Integer> currentBucket = buckets.get(j);
                while(!currentBucket.isEmpty())
                {
                    unsortedArray[i] = currentBucket.remove();
                    i++;
                }
            }
        }
    }

    //gets the length of the number in the array that 
    //has the most digits
    private int getMaxNumberOfDigits(int []unsorted) 
    {
        int max = Integer.MIN_VALUE;
        int temp = 0;

        for (int i : unsorted) 
        {
            //log base 10 of 0-9 is 0
            //log base 10 of 10-19 is 1 and so on
            temp = (int)Math.log10(i)+1;
            if (temp > max) 
            {
                max=temp;
            }
        }
        return max;
    }

    //gets a digit in a particular location
    private int getDigit(int number, int digitLocation)
    {
        int temp = (number / (int)Math.pow(10,digitLocation)) % 10;
        return temp;
    }

}
