import java.util.*;

class BFS
{
    private HashMap<Integer, Boolean> visitedNodes;
    private ArrayDeque<Integer> queue;

    public void Run(int []arr, int startIndex)
    {
        visitedNodes = new HashMap<Integer,Boolean>();
        queue = new ArrayDeque<Integer>();

        for(int i = 0; i <  arr.length; i++)
        {
            visitedNodes.put(i, false);
        }

        int currentNode = startIndex;
        queue.add(currentNode);

        while(!queue.isEmpty())
        {

            currentNode = queue.remove();
            if(!isVisited(currentNode))
            {
                System.out.println("visiting: " + arr[currentNode]);
                visitedNodes.put(currentNode, true);

                int left = getLeftChild(currentNode);
                int right = getRightChild(currentNode);

                if(left < arr.length)
                {
                    queue.add(left);
                }

                if(right < arr.length)
                {
                    queue.add(right);
                }
            }

        }
    }

    private Boolean isVisited(int index)
    {
        return visitedNodes.get(index);
    }

    private int getLeftChild( int current)
    {
        return 2 * current + 1;
    }

    private int getRightChild( int current)
    {
        return 2 * current + 2;
    }
}
