package ball_larus;

import java.util.ArrayList;
import java.util.Hashtable;

public class BallLarus
{
	public void CalculateValues(ArrayList<BasicBlock> blocks)
	{
		Hashtable<Integer, Integer> numPaths = new Hashtable<Integer, Integer>();
		
		for(int i = blocks.size() - 1; i >= 0; i--)
		{
			BasicBlock v = blocks.get(i);
			if(v.getIsExit())
			{
				numPaths.put(i, 1);
			}
			else
			{
				numPaths.put(i, 0);
				
				for(Edge outgoing: v.getOutgoingEdges())
				{
					if(v.getId() > outgoing.getEnd().getId() && outgoing.getEnd().getId() != -666)
					{
						continue;
					}
					
					int temp = numPaths.get(i);
					outgoing.setValue(temp);
					
					int endIndex = outgoing.getEnd().getIndex();
					temp = numPaths.get(endIndex);
					numPaths.put(i, numPaths.get(i) + temp);
				}
			}
		}
	}
	
	
	public String GetDOT(ArrayList<BasicBlock> blocks)
	{
		StringBuilder builder = new StringBuilder();
		builder.append("digraph graphname {\n");
		builder.append("\t");
		for(BasicBlock block: blocks)
		{
			builder.append(block.getId() + " [label=\""
					+ block.getDescription() + "\"];\n");

			
			for(Edge edge: block.getOutgoingEdges())
			{
				builder.append(edge.getStart().getId());
				builder.append("->");
				builder.append(edge.getEnd().getId());
				builder.append("[label=\"");
				
				builder.append(edge.getDescription() + ", ");
				
				int val = -1;
				
				if(edge.getStart().getId() < edge.getEnd().getId() || edge.getEnd().getId() == -666)
				{	
					val = edge.getValue();
					
				}
				builder.append(val);
				builder.append("\"];\n\t");
			}
		}
		
		builder.append("}");
		
		return builder.toString();
	}
}
