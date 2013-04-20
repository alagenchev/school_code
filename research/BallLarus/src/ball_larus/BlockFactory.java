package ball_larus;

public class BlockFactory
{
	private int idGen;
	
	public BlockFactory()
	{
		idGen = 0;
	}
	public BasicBlock GetBlock(String description, boolean isExit)
	{
		BasicBlock block = GetBlock(description);
		block.setIsExit(isExit);
		
		return block;
	}
	public BasicBlock GetBlock(String description)
	{
		BasicBlock block = new BasicBlock(description);
		block.setId(idGen);
		idGen++;
		return block;
	}
}
