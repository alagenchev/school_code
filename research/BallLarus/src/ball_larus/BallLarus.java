package ball_larus;

import java.util.ArrayList;

public class BallLarus
{
	public void CalculateValues(ArrayList<BasicBlock> blocks)
	{
		int[] numPaths = new int[blocks.size()];
		
		for(int i = blocks.size() - 1; i >= 0; i--)
		{
			BasicBlock v = blocks.get(i);
			if(v.getIsExit())
			{
				numPaths[i] = 1;
			}
			else
			{
				numPaths[i] = 0;
				
				for(Edge outgoing: v.getOutgoingEdges())
				{
					int temp = numPaths[i];
					outgoing.setValue(temp);
					
					temp = outgoing.getEnd().getId();
					numPaths[i]+=numPaths[temp];
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
			for(Edge edge: block.getOutgoingEdges())
			{
				builder.append(edge.getStart().getDescription());
				builder.append("->");
				builder.append(edge.getEnd().getDescription());
				builder.append("[label=");
				builder.append(edge.getValue());
				builder.append("];\n\t");
			}
		}
		
		builder.append("}");
		
		return builder.toString();
	}
}
