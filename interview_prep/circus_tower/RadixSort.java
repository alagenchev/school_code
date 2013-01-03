import java.util.*;
class RadixSort
{
    private ArrayList<ArrayDeque<Person>> buckets;
    private int bucketSize;

    public RadixSort()
    {
        buckets  = new ArrayList<ArrayDeque<Person>>();
        //we are going to use base 10 for simplicity
        //base 2 is faster for computers because we
        //can use shifts
        bucketSize = 10; 

        for(int i = 0; i < bucketSize; i++)
        {
            //add as many buckets as our base numbering system
            buckets.add(new ArrayDeque<Person>());
        }
    }
    public Person[] SortWeight(Person []people)
    {
        int [] weights = new int[people.length];
        for(int i = 0; i < people.length;i++)
        {
            weights[i] = people[i].Weight;
        }

        int maxDigitLength = getMaxNumberOfDigits(weights);


        for(int digitLocation = 0; digitLocation < maxDigitLength; digitLocation++)
        {
            //you can also use counting sort with complete
            //items here to use counting sort as a subroutine
            //of radix sort. I'm using buckets here similar
            //to wikipedia's page, since I haven't yet implemented
            //counting sort on full items

            for(Person person : people)
            {
                //separate numbers in queues based on the
                //particular digits we are sorting/separating them on
                int digitToSortOn = getDigit(person.Weight,digitLocation);
                buckets.get(digitToSortOn).add(person);
            }


            int i = 0;
            for(int j = 0; j< bucketSize; j++)
            {
                //take out all numbers from the queues and
                //put them back in the array in sorted order
                ArrayDeque<Person> currentBucket = buckets.get(j);
                while(!currentBucket.isEmpty())
                {
                    people[i] = currentBucket.remove();
                    i++;
                }

            }
        }
        return people;
    }
    public Person[] SortHeight(Person []people)
    {
        int [] heights = new int[people.length];
        for(int i = 0; i < people.length;i++)
        {
            heights[i] = people[i].Height;
        }

        int maxDigitLength = getMaxNumberOfDigits(heights);


        for(int digitLocation = 0; digitLocation < maxDigitLength; digitLocation++)
        {
            //you can also use counting sort with complete
            //items here to use counting sort as a subroutine
            //of radix sort. I'm using buckets here similar
            //to wikipedia's page, since I haven't yet implemented
            //counting sort on full items

            for(Person person : people)
            {
                //separate numbers in queues based on the
                //particular digits we are sorting/separating them on
                int digitToSortOn = getDigit(person.Height,digitLocation);
                buckets.get(digitToSortOn).add(person);
            }


            int i = 0;
            for(int j = 0; j< bucketSize; j++)
            {
                //take out all numbers from the queues and
                //put them back in the array in sorted order
                ArrayDeque<Person> currentBucket = buckets.get(j);
                while(!currentBucket.isEmpty())
                {
                    people[i] = currentBucket.remove();
                    i++;
                }

            }
        }

        return people;
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
