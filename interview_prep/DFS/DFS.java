import java.util.*;

class DFS
{
    private HashMap<Integer, Boolean> visitedNodes;
    private Stack<Integer> stack;

    public void Run(int []arr, int startIndex)
    {
        visitedNodes = new HashMap<Integer,Boolean>();
        stack = new Stack<Integer>();

        for(int i = 0; i <  arr.length; i++)
        {
            visitedNodes.put(i, false);
        }

        int currentNode = startIndex;


        do
        {
            if(!isVisited(currentNode))
            {
                System.out.println("visiting: " + arr[currentNode]);
                visitedNodes.put(currentNode, true);
                stack.push(currentNode);
            }
            int adjacent = getAdjacent(currentNode,arr);
            
            if(adjacent > 0)
            {
                currentNode = adjacent;
            }
            else 
            {
                currentNode = stack.pop();
            }

        }while(!stack.isEmpty() || getAdjacent(currentNode, arr) > -1 || 
                !isVisited(currentNode));
    }

    private int getAdjacent(int index, int []arr)
    {
        int left = getLeftChild (index);

        if(left < arr.length && arr[left]!= -666 && !isVisited(left))
        {
            return left;
        }

        int right = getRightChild(index);

        if(right < arr.length && arr[right]!= -666 && !isVisited(right))
        {
            return right;
        }

        return -1;
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
