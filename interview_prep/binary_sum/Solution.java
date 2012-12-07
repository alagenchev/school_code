import java.lang.Integer;

public class Solution 
{
    public String addBinary(String a, String b) 
    {
        String first = a;
        String second = b;
        String ret = "";

        if(a.length() < b.length())
        {
            first = b;
            second = a;
        }
        
        int carry = 0;
        int j = first.length() - 1;
        for(int i = second.length() - 1; i >= 0; i--)
        {
            int temp = Character.getNumericValue(second.charAt(i));
            int temp1 = Character.getNumericValue(first.charAt(j));
            j--;

            int result = temp ^ temp1;
            result = result ^ carry;
            carry = (temp & temp1)|(temp & carry) | (temp1 & carry);

            //System.out.println("r1:"+ result + ", c1:" + carry);

            ret += String.valueOf(result);

        }

        for(int i = j;i>= 0;i--)
        {
            int temp = Character.getNumericValue(first.charAt(i));
            int result = temp^ carry;
            ret+=String.valueOf(result);
            carry = temp & carry;
        }

        if(carry>0)
        {
            //System.out.println("c:"+carry);
            ret+=String.valueOf(carry);
        }

        String temp = "";

        for(int i = ret.length() - 1; i>=0;i--)
        {
            temp+= ret.charAt(i);
        }

        return temp;
    }
}
