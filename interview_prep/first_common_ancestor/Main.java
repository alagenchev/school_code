import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        String[] stringNodes = args[0].split(",");
        int [] tree = new int[stringNodes.length];

        int startNode = Integer.parseInt(args[1]);
        int endNode = Integer.parseInt(args[2]);

        System.out.println("startNode: "+startNode + ", endNode: "+ endNode);

        for(int i = 0; i< stringNodes.length;i++)
        {
            tree[i] = Integer.valueOf(stringNodes[i]);
        }

        ArrayList<Integer> inorderSet = new ArrayList<Integer>();
        System.out.print("in order: ");
        inorder(tree, 0, inorderSet);
        System.out.println();

        System.out.print("post order: ");
        ArrayList<Integer> postOrderList = new ArrayList<Integer>();
        postorder(tree, 0, postOrderList);
        System.out.println();

        HashSet<Integer> hashSet = new HashSet<Integer>();

        boolean add = false;
        for(int i : inorderSet)
        {
            if(add)
            {
                hashSet.add(i);
            }
            if(i == startNode)
            {
                add = true;
            }
            if(i == endNode)
            {
                break;
            }
        }

        boolean started = false;
        for(int i = 0; i < postOrderList.size();i++)
        {
            int current = postOrderList.get(i);

            if(hashSet.contains(current))
            {
                started = true;
            }

            if(started && !hashSet.contains(current))
            {
                System.out.println("lowest common parent: " + postOrderList.get(i-1));
                break;
            }
        }


    }


    public static void inorder(int[] tree, int currentIndex, ArrayList<Integer> inorderList)
    {
        if(currentIndex >= tree.length)
        {
            return;
        }

        inorder(tree, 2 * currentIndex + 1, inorderList);

        if(tree[currentIndex] != -666)
        {
            inorderList.add(tree[currentIndex]);
            System.out.print(tree[currentIndex]+", ");
        }

        inorder(tree, 2 * currentIndex + 2, inorderList);
    }


    public static void postorder(int[] tree, int currentIndex, ArrayList<Integer> list)
    {
        if(currentIndex >= tree.length)
        {
            return;
        }

        postorder(tree, 2 * currentIndex + 1, list);

        postorder(tree, 2 * currentIndex + 2, list);

        if(tree[currentIndex] != -666)
        {
            list.add(tree[currentIndex]);
            System.out.print(", "+ tree[currentIndex]);
        }

    }
}

