public class Solution 
{
	public boolean isMatch(String s, String p) {
		
		int indexInP = 0;

		if(p.length() == 1 && p.charAt(0) == '*')
		{
			return true;
		}

		for(int i = 0; i < s.length(); i++)
		{
		
			if(indexInP >= p.length() || p.charAt(indexInP) != '*' && p.charAt(indexInP) != '?' && p.charAt(indexInP)!= s.charAt(i))
			{
				return false;
			}
			else if(p.charAt(indexInP) == '*')
			{
				if(indexInP < p.length() - 1)
				{
					i = eatWildcardUntil(s, i, p.charAt(indexInP + 1));//make sure there is indexInP + 1
				}
				else
				{
					return true;
				}
			}
			else if(p.charAt(indexInP) != '?' && p.charAt(indexInP) != s.charAt(i))
			{
				return false;
			}
				indexInP++;
		}

		for(int i = indexInP; i < p.length(); i++)
		{
			if(p.charAt(i) != '*')
			{
				return false;
			}
		}
		return true;
	}
	
	private int eatWildcardUntil(String stringToEat,int startIndex, char eatUntil)
	{
		int i = startIndex;

		while(i < stringToEat.length() && stringToEat.charAt(i) != eatUntil)
		{
			i++;
		}

		if(i == stringToEat.length())
		{
			return -1;
		}
		
		return i - 1;
	}
}
