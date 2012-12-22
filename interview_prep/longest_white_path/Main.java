public class Main
{
    public static void main(String []args)
    {
        TreeNode l1 = new TreeNode();
        l1.Color = 0;
        l1.Name = "l1";

        TreeNode l2 = new TreeNode();
        l2.Color = 0;
        l2.Name = "l2";

        TreeNode l3 = new TreeNode();
        l3.Color = 1;
        l3.Name = "l3";

        TreeNode l4 = new TreeNode();
        l4.Color = 0;
        l4.Name = "l4";

        TreeNode root = new TreeNode();
        root.Color = 0;
        root.Name = "root";

        TreeNode r1 = new TreeNode();
        r1.Color = 0;
        r1.Name = "r1";

        TreeNode r2 = new TreeNode();
        r2.Color = 1;
        r2.Name = "r2";
        
        TreeNode r3 = new TreeNode();;
        r3.Color = 0;
        r3.Name = "r3";

        TreeNode r4 = new TreeNode();;
        r4.Color = 1;
        r4.Name = "r4";

        TreeNode r5 = new TreeNode();;
        r5.Color = 0;
        r5.Name = "r5";

        TreeNode r6 = new TreeNode();;
        r6.Color = 0;
        r6.Name = "r6";

        TreeNode r7 = new TreeNode();;
        r7.Color = 1;
        r7.Name = "r7";

        root.Left = l4;
        root.Right = r7;

        l4.Left = l3;
        l3.Right = l2;
        l2.Right = l1;

        r7.Left = r6;
        r7.Right = r5;

        r5.Right = r4;
        r4.Right = r3;

        r3.Left = r1;
        r3.Right = r2;

        CurrentVal val = new CurrentVal();
        val.Length = 0;
        val.Max = 0;
        val.LengthString = "";
        val.MaxString = "";

        CurrentVal result = GetWhiteLength(root, val);

        System.out.println("max is "+ result.Max + " for nodes: " + result.MaxString);

    }

    public static CurrentVal GetWhiteLength(TreeNode current, CurrentVal val)
    {
        if(current == null)
        {
            return val;
        }

        CurrentVal newVal = new CurrentVal();
        newVal.Length = val.Length;
        newVal.Max = val.Max;
        newVal.MaxString = val.MaxString;
        newVal.LengthString = val.LengthString;



        if(current.Color == 0)
        {
            newVal.Length++;
            newVal.LengthString += ", "+current.Name;

        }
        else
        {
            newVal.Length = 0;
            newVal.LengthString = "";
        }

        if(newVal.Length > newVal.Max)
        {
            newVal.Max = newVal.Length;
            newVal.MaxString = newVal.LengthString;
        }
        CurrentVal leftVal = null;

        if(current.Left != null)
        {
            leftVal = GetWhiteLength(current.Left, newVal);
        }

        if(leftVal != null && leftVal.Max > newVal.Max)
        {
            newVal.MaxString = leftVal.MaxString;
            newVal.Max = leftVal.Max;
        }


        CurrentVal rightVal = null;

        if(current.Right != null)
        {
            rightVal = GetWhiteLength(current.Right, newVal);
        }

        if(rightVal!=null && rightVal.Max > newVal.Max)
        {
            newVal.MaxString = rightVal.MaxString;
            newVal.Max = rightVal.Max;
        }

        return newVal;

    }
}
