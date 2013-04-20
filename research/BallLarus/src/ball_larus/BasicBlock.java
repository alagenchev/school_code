package ball_larus;

import java.util.ArrayList;

public class BasicBlock
{
	private boolean _isExit;
	private ArrayList<Edge> _outgoingEdges;
	private int _id;
	private String _description;
	
	public BasicBlock(String description)
	{
		this();
		_description = description;
	}
	public BasicBlock()
	{
		setOutgoingEdges(new ArrayList<Edge>());
	}

	public ArrayList<Edge> getOutgoingEdges()
	{
		return _outgoingEdges;
	}

	public void setOutgoingEdges(ArrayList<Edge> outgoingEdges)
	{
		_outgoingEdges = outgoingEdges;
	}
	
	public boolean getIsExit()
	{
		return _isExit;
	}

	public void setIsExit(boolean isExit)
	{
		_isExit = isExit;
	}

	public int getId()
	{
		return _id;
	}

	public void setId(int id)
	{
		_id = id;
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
