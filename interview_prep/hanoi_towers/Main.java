import java.util.*;

class Main
{
    public static void main(String []args)
    {
        String []temp_elements = args[0].split(",");
        int []elements = new int[temp_elements.length];

        for(int i = 0; i< elements.length;i++)
        {
            elements[i] = Integer.parseInt(temp_elements[i]);
        }

        for(int i = 0; i < elements.length ; i++)
        {
            System.out.println(i+":"+elements[i]);
        }

        ArrayList<Stack<Integer>> towers = new ArrayList<Stack<Integer>>();

        for(int i = 0; i < 3; i++)
        {
            towers.add(new Stack<Integer>());
        }

        for(int i : elements)
        {
            towers.get(0).push(i);
        }

        moveTowers(towers, 0, 2, elements.length);

        System.out.println(towers.get(2));

    }

    private static void moveTowers(ArrayList<Stack<Integer>> towers, int from, int to, int count)
    {
        if(count == 0 || from == to)
        {
            return;
        }
        if(towers.get(from).isEmpty())
        {
            return;
        }
        
        int other = 0;

        if( from + to == 1)
        {
            other = 2;
        }
        else if (from + to == 2)
        {
            other = 1;
        }

        moveTowers(towers, from, other, count - 1);
        int temp = towers.get(from).pop();
        towers.get(to).push(temp);
        moveTowers(towers, other, to, count - 1);


    }

}
