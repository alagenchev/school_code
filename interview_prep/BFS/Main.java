
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
        BFS dfs = new BFS();
        dfs.Run(elements, 0);

    }


}
