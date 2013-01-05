
class Main
{
    public static void main(String []args)
    {
       String parens = args[0];

       Boolean valid = isValid(parens, 0, parens.length() - 1);

       System.out.println("valid: " + valid);

    }

    public static Boolean isValid(String parens, int start, int end)
    {
        System.out.println("start: " + start + " end: " + end);

        if(start > end)
        {
            return true;
        }

        if(start + 1 == end)
        {
            if(parens.charAt(start) != '(' || parens.charAt(end) != ')')
            {
                return false;
            }
            else
            {
                return true;
            }

        }

        int current = start;
        int count = 0;
        int index = -1;

        while(current == start || (current <= end && index == -1))
        {
            if(parens.charAt(current) == '(')
            {
                count++;
            }
            else
            {
                count--;
            }
            System.out.printf("at %d, count: %d\n", current, count);
            if(count < 0)
            {
                return false;
            }
            else if(count == 0)
            {
                index = current;
            }
            else
            {
                current++;
            }
        }

        if(count != 0)
        {
            return false;
        }

        System.out.println("index: " + index);

        if(parens.charAt(start) != '(' || parens.charAt(index) != ')')
        {
            return false;
        }
        else if (index == end)
        {
            return isValid(parens, start + 1, end - 1);
        }
        else
        {
            Boolean valid = false;
            valid = isValid(parens, start + 1, index - 1);
            if(valid)
            {
                return isValid(parens, index + 1, end);
            }
        }

        return false;
    }


}
