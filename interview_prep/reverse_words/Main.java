import java.util.Stack;

public class Main
{
	public static void main(String[] args)
	{
        String toReverse = "This is  a string that Ivan wants to reverse";
        String reversed = "";
    
        String temp = Reverse(toReverse);

        String[] split = temp.split(" ");

        for(String str : split)
        {
            reversed += Reverse(str);
            reversed +=" ";
        }

        System.out.println("Reversed: " + reversed);

	}

    public static String Reverse(String stringToReverse)
    { 
        String reversed = "";

        Stack<Character> stack = new Stack<Character>();

        for(char c: stringToReverse.toCharArray())
        {
            stack.push(c);
        }
       
        while(!stack.empty())
        {
            reversed += stack.pop();
        }


        return reversed;

    }
}
