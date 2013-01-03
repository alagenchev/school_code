class CountingSort
{
    public int[] Sort(int []arr, int maxPossibleValue)
    {
        //java sets the default values of counts and output to all 0s
        int [] output = new int[arr.length];

        // +1 to allow for both the max val and for 0
        int [] counts = new int[maxPossibleValue + 1];  

        for(int i : arr)
        {
            //count each element in array
            counts[i]++;
        }

        //start at first index of output array
        int i = 0;

        //go through all counts that we counted 
        //(even for those that weren't represented)
        for(int k = 0; k < counts.length; k++)
        {
            //for each counts that had counts
            //output the element with counts that many times
            for(int j = 0; j < counts[k]; j++)
            {
                //k is the index in the counts array
                //and also the element value in the input 
                //array
                output[i] = k;

                //shift the index in the output array, since we have a new element in
                i++;
            }
        }
        return output;
    }
}
