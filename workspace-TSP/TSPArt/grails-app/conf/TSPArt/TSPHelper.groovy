package TSPArt

class TSPHelper {

	private Tour apply2Opt(Tour tour) {
		Tour newTour = new Tour()

		tour.Lines.each {
			newTour.Lines.add(it)
		}

		for(int i = 0; i < newTour.Lines.size; i++) {
			def line = newTour.Lines[i];
			
			for(int j = 0; j< newTour.Lines.size;j++) {
				def otherLine = newTour.Lines[j];
				
				if(!line.isEquivalent(otherLine)) {

					def intersect = doesIntersect(line.StartX, line.StartY, line.EndX, line.EndY,
							otherLine.StartX, otherLine.StartY, otherLine.EndX, otherLine.EndY)



					if(intersect) {

						
					//println "starting tour:" + newTour
					//	println "" + line + " intersects " + otherLine + " fixed to "
						fix_intersection(line, otherLine, i, j, newTour)
					//	println "" + line + " and " + otherLine
						//println ""
					}
				}
			}
		}

		return newTour

		//now apply 2opt algo on newTour
	}

	public void fix_intersection(TSPLine line1, TSPLine line2, int line1Index, int line2Index, Tour tour) {


		int distance1 = 0;
		int distance2 = 0;

		def newLine1 = line1.makeCopy()
		def newLine2 = line2.makeCopy()
		
		def tempLine = new TSPLine(line2.StartX, line2.StartY, line1.EndX, line1.EndY)
		if(!hasEdge(tempLine, tour)) {
			int temp = line1.StartX
			line1.StartX = line2.StartX
			line2.StartX = temp

			temp = line1.StartY
			line1.StartY = line2.StartY
			line2.StartY = temp

			distance1 = (line1.getDistance() + line2.getDistance())
		}

		tempLine = new TSPLine(newLine2.EndX, newLine2.EndY, newLine1.EndX, newLine1.EndY)
		if(!hasEdge(tempLine, tour)) {
			int temp = newLine1.StartX
			newLine1.StartX = newLine2.EndX
			newLine2.EndX = temp

			temp = newLine1.StartY
			newLine1.StartY = newLine2.EndY
			newLine2.EndY = temp
			distance2 = (newLine1.getDistance() + newLine2.getDistance())
		}
		
		if(line1Index < line2Index)
		{
			tour.Lines.remove(line2Index)
			tour.Lines.remove(line1Index)
		}
		else
		{
			tour.Lines.remove(line1Index)
			tour.Lines.remove(line2Index)
		}
		

		if(distance2 <= distance1 && distance2!=0) {
			line1 = newLine1
			line2 = newLine2

			tour.Lines.add(line1)
			tour.Lines.add(line2)
			//println "end w:" + tour 
		}
		else
		{
			tour.Lines.add(line1)
			tour.Lines.add(line2)
		}
	}

	boolean hasEdge(TSPLine line, Tour tour) {
		for(TSPLine tLine in tour.Lines) {

			if(tLine.isEquivalent(line)) {
				return true
			}
			/*
			 if(tLine.StartX == line.StartX && tLine.StartY == line.StartY && tLine.EndX == line.EndX && tLine.EndY == line.EndY) {
			 return true;
			 }
			 else if(tLine.StartX == line.EndX && tLine.StartY == line.EndY && tLine.EndX == line.StartX && tLine.EndY == line.StartY) {
			 return true;
			 }*/
		}
	}


	public static boolean doesIntersect(double l1x1, double l1y1, double l1x2, double l1y2, double l2x1, double l2y1, double l2x2,
			double l2y2) {

		if(l1x1 == l2x1 && l1y1 == l2y1) {
			return false;
		}
		else if(l1x2 == l2x2 && l1y2 == l2y2) {
			return false
		}
		else if(l1x2 == l2x1 && l1y2 == l2y1) {
			return false;
		}

		else if(l1x1 == l2x2 && l1y1 == l2y2) {
			return false;
		}


		double denom = ((l2y2 - l2y1) * (l1x2 - l1x1)) - ((l2x2 - l2x1) * (l1y2 - l1y1));

		if (denom == 0.0f) {
			return false;
		}

		double ua = (((l2x2 - l2x1) * (l1y1 - l2y1)) - ((l2y2 - l2y1) * (l1x1 - l2x1))) / denom;
		double ub = (((l1x2 - l1x1) * (l1y1 - l2y1)) - ((l1y2 - l1y1) * (l1x1 - l2x1))) / denom;

		return ((ua >= 0.0d) && (ua <= 1.0d) && (ub >= 0.0d) && (ub <= 1.0d));
	}

	private TSPLine getNonAdjacentLine(TSPLine line, Tour tour) {
		TSPNode startNode = new TSPNode(line.StartX, line.StartY, false)
		TSPNode endNode = new TSPNode(line.EndX, line.EndY, false)

		def notDirectlyAdjacentEdges = []
		def adjacentNodes = []

		adjacentNodes.add(startNode)
		adjacentNodes.add(endNode)

		tour.Lines.each {
			if((it.StartX == startNode.X && it.StartY == startNode.Y) || (it.StartX == endNode.X && it.StartY == endNode.Y)) {
				def node = new TSPNode(it.EndX, it.EndY, false)
				def node2 = new TSPNode(it.StartX, it.StartY, false)

				if(!adjacentNodes.contains(node)) {
					adjacentNodes.add(node)
				}

				if(!adjacentNodes.contains(node2)) {
					adjacentNodes.add(node2)
				}
			}
			else if((it.EndX == startNode.X && it.EndY == startNode.Y)||(it.EndX == endNode.X && it.EndY == endNode.Y)) {
				def node = new TSPNode(it.EndX, it.EndY, false)
				def node2 = new TSPNode(it.StartX, it.StartY, false)

				if(!adjacentNodes.contains(node)) {
					adjacentNodes.add(new TSPNode(it.StartX, it.StartY, false))
				}

				if(!adjacentNodes.contains(node2)) {
					adjacentNodes.add(node2)
				}
			}
			else {
				notDirectlyAdjacentEdges.add(new TSPLine(it.StartX, it.StartY, it.EndX, it.EndY))
			}
		}

		//	println "adjacent nodes: " + adjacentNodes
		//go through all non directly adjacent and see if you can find a non-adjacent
		notDirectlyAdjacentEdges.find{
			boolean isAdjacent = false
			for(TSPNode adjacentNode : adjacentNodes)
			{
				if((adjacentNode.X == it.StartX && adjacentNode.Y == it.StartY) ||(adjacentNode.X == it.EndX && adjacentNode.Y == it.EndY))
				{
					//			println "(" + it.StartX + ", " + it.StartY + ")--(" + it.EndX + ", " + it.EndY + ") is adjacent"
					isAdjacent = true;
				}
			}

			if(!isAdjacent)
			{
				return it
			}
		}

	}

	private TSPLine createNearestLine(TSPNode source, TSPNode destination) {
		new TSPLine(source.X, source.Y, destination.X, destination.Y)
	}
}
