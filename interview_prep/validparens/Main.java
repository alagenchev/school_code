public class Main
{
	public static void main(String[] args)
	{
		Solution sol = new Solution();
		boolean isValid = sol.isValid("[");
		System.out.println("isValid: "+isValid);

		isValid = sol.isValid("]");
		System.out.println("isValid: "+isValid);
	}
}
