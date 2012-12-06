import java.util.Stack;


public class Solution
{
	private Stack<Character> _stack;
	public Solution()
	{
		_stack = new Stack<Character>();
	}

	public boolean isClosing(char c)
	{
		switch (c)
		{
			case '}':
				return true;
			case ']':
				return true;
			case ')':
				return true;
			default: 
				return false;
		}
	}

	public boolean isValid(String s)
	{
		for(int i = 0; i < s.length();i++)
		{

			char right = s.charAt(i);

			if(_stack.size() == 0)
			{
				if(isClosing(right))
				{
					_stack.removeAllElements();
					return false;
				}
				else
				{
					_stack.push(right);
				}
				continue;
			}

			char top = _stack.peek();

			boolean isMatch = doMatch(top, right);

			if(isMatch)
			{
				_stack.pop();
			}
			else
			{
				_stack.push(right);
			}
		}


		if(_stack.size() > 0)
		{
			_stack.removeAllElements();
			return false;
		}

		return true;

	}

	private boolean doMatch(char left, char right)
	{
		if(left == '{' && right == '}')
		{
			return true;
		}
		else if(left == '[' && right == ']')
		{
			return true;
		}
		else if(left == '(' && right == ')')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
