public class Main
{
	public static void main(String[] args)
	{
		Solution sol = new Solution();
		boolean isMatch = sol.isMatch(args[0], args[1]);

		System.out.println("isMatch: " + isMatch);
	}
}
