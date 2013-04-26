package cfg_parser;

import java.util.ArrayList;
import java.util.Hashtable;

import ball_larus.BasicBlock;
import ball_larus.BlockFactory;
import ball_larus.Edge;

public class BasicBlockParser
{
	private BlockFactory _factory;
	private ArrayList<BasicBlock> _blocks;
	private Hashtable<Integer, ArrayList<Integer>> _blocksToEdges;

	private BasicBlock getBlock(int id) throws Exception
	{
		for (BasicBlock block : _blocks)
		{
			if( block.getId() == id )
			{
				return block;
			}
		}
		throw new Exception("basic block not found");
	}

	public BasicBlockParser(BlockFactory factory)
	{
		_blocks = new ArrayList<BasicBlock>();
		_blocksToEdges = new Hashtable<Integer, ArrayList<Integer>>();
		_factory = factory;
		BasicBlock start = factory.GetBlock(1, "Start", false);
		_blocks.add(start);
	}

	public String BlocksToDOT() throws Exception
	{
		StringBuilder builder = new StringBuilder();
		builder.append("digraph graphname {\n");
		builder.append("\t");

		ArrayList<BasicBlock> blocks = GetBlocks();
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (BasicBlock block : blocks)
		{
			ArrayList<Edge> myEdges = block.getOutgoingEdges();
			
			edges.addAll(myEdges);
			builder.append(block.getId() + " [label=\""
					+ block.getDescription() + "\"];\n");

			builder.append("\t");
		}
		
		builder.append("\n\t");

		int count = 0;
		
		for (Edge edge : edges)
		{
			builder.append(edge.getStart().getId());
			builder.append("->");
			builder.append(edge.getEnd().getId());
			builder.append("[label=");
			builder.append(edge.getDescription() + ", ");
			builder.append(edge.getValue());
			builder.append("];\n");
			
			if(count < edges.size() - 1)
			{
				builder.append("\t");
			}
			
			count++;
		}

		builder.append("}");

		return builder.toString();
	}

	public ArrayList<BasicBlock> GetBlocks() throws Exception
	{
		BasicBlock exitBlock = _factory.GetBlock(-666, "End", true);
		_blocks.add(exitBlock);

		for (int i = 0; i < _blocks.size(); i++)
		{
			BasicBlock current = _blocks.get(i);
			current.setIndex(i);
			if( current.getDescription() == "Start" && i < _blocks.size() - 1 )
			{
				Edge newEdge = new Edge(current, _blocks.get(i + 1));
				current.getOutgoingEdges().add(newEdge);
			}
			else if( current.getId() != -666 )
			{
				for (int edgeEnd : _blocksToEdges.get(current.getId()))
				{
					BasicBlock end = getBlock(edgeEnd);
					Edge edge = new Edge(current, end);
					current.getOutgoingEdges().add(edge);
				}
			}
			
			for(int j = 0; j < current.getOutgoingEdges().size(); j++)
			{
				if(j == 0)
				{
					current.getOutgoingEdges().get(0).setDescription("True");
				}
				else
				{
					current.getOutgoingEdges().get(j).setDescription("False");
				}
			}
		}
		
		return _blocks;
	}
	
	public void parseBBL(String line)
	{
		String originalLine = line;

		int end = line.indexOf(">:");
		if( end < 0 )
		{
			return;
		}
		String temp = line.substring(4, end);

		BasicBlock block = _factory.GetBlock(Integer.parseInt(temp),
				temp.toString(), false);
		ArrayList<Integer> edges = new ArrayList<Integer>();

		int next = line.indexOf('|');
		boolean addedNextEdge = false;
		while (next != -1)
		{
			next++;// skip over the |
			temp = line.substring(0, next);

			if( temp.contains("if") || (temp.contains("(") && temp.contains(");")))
			{
				temp = temp.replace("\"", "\\\"");
				block.setDescription(block.getDescription() + " " + temp);
			}
			else if( temp.contains("goto") )
			{
				int index = temp.indexOf("goto <bb ");
				if( index > -1 )
				{
					temp = temp.substring(index + 9, temp.indexOf(">;"));

					int id = Integer.parseInt(temp);
					edges.add(id);
				}
			}
			else if( !originalLine.contains("goto")
					&& !originalLine.contains("exit (")
					&& !originalLine.contains("return ") 
					&& !addedNextEdge)
			{
				edges.add(block.getId() + 1);// point to next block
				addedNextEdge = true;
			}
			
			if( temp.contains("exit (") || temp.contains("return") )
			{
				edges.add(-666);
			}

			line = line.substring(next, line.length());
			next = line.indexOf('|');
		}

		_blocks.add(block);
		_blocksToEdges.put(block.getId(), edges);
	}
}
