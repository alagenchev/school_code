package ball_larus;

import java.util.ArrayList;

public class Main
{

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		ArrayList<BasicBlock> blocks = new ArrayList<BasicBlock>();
		BlockFactory factory = new BlockFactory();
		
		BasicBlock blockA = factory.GetBlock("A");
		blocks.add(blockA);
		
		BasicBlock blockB = factory.GetBlock("B");
		blocks.add(blockB);
		
		BasicBlock blockC = factory.GetBlock("C");
		blocks.add(blockC);
		
		BasicBlock blockD = factory.GetBlock("D");
		blocks.add(blockD);
		
		BasicBlock blockE = factory.GetBlock("E");
		blocks.add(blockE);
		
		BasicBlock blockF = factory.GetBlock("F", true);
		blocks.add(blockF);
		
		Edge edgeAB = new Edge(blockA, blockB);
		Edge edgeAC = new Edge(blockA, blockC);
		Edge edgeBC = new Edge(blockB, blockC);
		Edge edgeBD = new Edge(blockB, blockD);
		Edge edgeCD = new Edge(blockC, blockD);
		Edge edgeDE = new Edge(blockD, blockE);
		Edge edgeDF = new Edge(blockD, blockF);
		Edge edgeEF = new Edge(blockE, blockF);
		
		blockA.getOutgoingEdges().add(edgeAB);
		blockA.getOutgoingEdges().add(edgeAC);
		
		blockB.getOutgoingEdges().add(edgeBC);
		blockB.getOutgoingEdges().add(edgeBD);
		
		blockC.getOutgoingEdges().add(edgeCD);
		
		blockD.getOutgoingEdges().add(edgeDE);
		blockD.getOutgoingEdges().add(edgeDF);
		
		blockE.getOutgoingEdges().add(edgeEF);
		
		BallLarus larus = new BallLarus();
		larus.CalculateValues(blocks);
		
		System.out.println(larus.GetDOT(blocks));
		

	}

}
