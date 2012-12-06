public class Main
{
	public static void main(String []args) throws Exception
	{
		String pattern = "cad";
		KMPMatch kmp = new KMPMatch(pattern);
		kmp.computeFailure();
		int match = kmp.match("abracadabra");
		
		System.out.println("matched at index: " + match);

	}
}

