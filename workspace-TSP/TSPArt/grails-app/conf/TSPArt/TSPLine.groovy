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
}
