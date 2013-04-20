package ball_larus;

public class Edge
{
	private BasicBlock _start;
	private BasicBlock _end;
	private int _value;
	
	public Edge()
	{
		
	}
	
	public Edge(BasicBlock start, BasicBlock end)
	{
		_start = start;
		_end = end;
	}
	public BasicBlock getStart()
	{
		return _start;
	}
	public void setStart(BasicBlock start)
	{
		_start = start;
	}
	
	public BasicBlock getEnd()
	{
		return _end;
	}
	public void setEnd(BasicBlock end)
	{
		_end = end;
	}
	public int getValue()
	{
		return _value;
	}
	public void setValue(int value)
	{
		_value = value;
	}
	
}
