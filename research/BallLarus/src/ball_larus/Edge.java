package ball_larus;

public class Edge
{
	private BasicBlock _start;
	private BasicBlock _end;
	private int _value;
	private String _description;
	
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
	
	@Override
	public String toString()
	{
		return _start.getId() + " -> " + _end.getId();
	}

	public String getDescription()
	{
		return _description;
	}

	public void setDescription(String description)
	{
		_description = description;
	}
	
}
