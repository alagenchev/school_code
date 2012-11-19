package TSPArt

class TSPLine {
	def StartX
	def StartY
	def EndX
	def EndY
	boolean ShouldDraw
	
	TSPLine(int startX, int startY, int endX, int endY)
	{
		StartX = startX
		StartY = startY
		EndX = endX
		EndY = endY
		ShouldDraw = true
	}
	
	TSPLine makeCopy()
	{
		def temp = new TSPLine(StartX, StartY, EndX, EndY)
		temp.shouldDraw = ShouldDraw
		temp
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "(" + StartX + ", " + StartY + ")--(" + EndX + ", " + EndY + ")"  ;
	}
	
	public boolean isEquivalent(TSPLine line)
	{
		if(StartX == line.StartX && EndX == line.EndX && StartY == line.StartY && EndY == line.EndY)
		{
			return true;
		}
		else if(EndX == line.StartX && EndY == line.StartY && StartX == line.EndX && StartY == line.StartY)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	public int getDistance()
	{
		(EndX - StartX)* (EndX - StartX) + (EndY - StartY)*(EndY - StartY)
	}
}
