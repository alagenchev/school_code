public class Main
{
	public static void main(String[] args)
	{
		String[] stringNodes = args[0].split(",");
		int [] tree = new int[stringNodes.length];

		for(int i = 0; i< stringNodes.length;i++)
		{
			tree[i] = Integer.valueOf(stringNodes[i]);
		}

		System.out.println("in order:");

		for(int i = 0; i < tree.length; i++)
		{
			if(2*i +1 < tree.length)
			{
				System.out.print("l: "+ tree[2*i + 1]);
			}
			else
			{
				System.out.print("l: -1");
			}
			System.out.print(", p: "+ tree[i]);
			if(2*i+2 < tree.length)
			{
				System.out.println(", r: "+tree[2*i+2]);
			}
			else
			{
				System.out.println(", r: -1");
			}
		}
	}


	public void inorder(int[] tree, int currentIndex)
	{
		inorder(tree, 2 * currentIndex + 1);
		System.out.println(
	}
}

