public class Main
{
	public static void main(String []args)
	{
		String pattern = "ababababca";
		KMPMatch kmp = new KMPMatch();
		int[] failure = kmp.computeFailure(pattern);

		for(int i = 0; i < failure.length; i++)
		{
			System.out.println(i + ": "+ failure[i] + "|");
		}

	}
}
