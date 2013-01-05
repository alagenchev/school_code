import java.util.*;

class Main
{
    public static void main(String []args)
    {
        char[] characters = args[0].toCharArray();

        for(char c: characters)
        {
            System.out.println(c);
        }

        ArrayList<Character> notUsed = new ArrayList<Character>();
        for(char c: characters)
        {
            notUsed.add(c);
        }

        String [] permutations = getPermutations(notUsed, -1);

        System.out.println("permutations:");
        for(String p : permutations)
        {
            System.out.println(p);
        }
    }

    public static String [] getPermutations(ArrayList<Character> unused, int remove)
    {
        ArrayList<String> result = new ArrayList<String>();
        ArrayList<Character> myUnused = new ArrayList<Character>();

        for(int i = 0; i < unused.size();i++)
        {
            if(i != remove)
            {
                myUnused.add(unused.get(i));
            }
        }

        for(int i = 0; i < myUnused.size();i++)
        {
        	
            String[] permutations = getPermutations(myUnused,i);
            for(String p: permutations)
            {
                result.add(myUnused.get(i) + p);
            }
            if(permutations.length == 0)
            {
            	result.add(myUnused.get(i).toString());
            }
        }

        return result.toArray( new String[result.size()]);

    }

}


