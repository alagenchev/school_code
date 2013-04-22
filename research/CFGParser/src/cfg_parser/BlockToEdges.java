package cfg_parser;

import java.util.ArrayList;

public class BlockToEdges
{
	private int _blockId;
	private ArrayList<Integer> _edgeIds;
	
	public BlockToEdges(int blockId)
	{
		_edgeIds = new ArrayList<Integer>();
		_blockId = blockId;
	}
	public int getBlockId()
	{
		return _blockId;
	}
	public void setBlockId(int blockId)
	{
		_blockId = blockId;
	}
	public ArrayList<Integer> getEdgeIds()
	{
		return _edgeIds;
	}
	public void setEdgeIds(ArrayList<Integer> edgeIds)
	{
		_edgeIds = edgeIds;
	}
	
	public void AddEdge(int edge)
	{
		_edgeIds.add(edge);
	}
	
	@Override
	public String toString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("Block: ");
		builder.append(_blockId);
		builder.append(", edges: ");
		for(Integer edge: _edgeIds)
		{
			builder.append(edge);
			builder.append(",");
		}
		
		return builder.toString();
	}
}
