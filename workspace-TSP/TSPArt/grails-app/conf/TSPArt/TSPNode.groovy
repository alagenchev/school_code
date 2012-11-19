package TSPArt

class TSPNode {

	int X
	int Y
	boolean Visited
	TSPNode(int x, int y, boolean visited)
	{
		X = x
		Y = y
		Visited = visited
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return super.toString() + "(" + X + ", " + Y + "), visited: " + Visited;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		if(obj instanceof TSPNode)
		{
			TSPNode other = (TSPNode)obj
			if(other.X == this.X && other.Y == this.Y && other.Visited == this.Visited)
			{
				return true;
			}
		}
		
		false
	}
}
