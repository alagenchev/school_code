import java.util.*;

class DFS
{
    private HashMap<Integer, Boolean> visitedNodes;
    private Stack<Integer> stack;

    public void Run(int []arr, int startIndex)
    {
        if(startIndex >= arr.length)
        {
            return;
        }
        if(arr == null || arr.length == 0)
        {
            return;
        }
        System.out.println("visiting: " + arr[startIndex]);
        Run(arr, 2 * startIndex + 1);
        Run(arr, 2 * startIndex + 2);
    }
}
