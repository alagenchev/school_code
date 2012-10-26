package TSPArt

import java.awt.image.BufferedImage;
import java.util.Random;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;

import TSPArt.TSPLine
import TSPArt.TSPNode
import javax.imageio.ImageIO;

import org.springframework.aop.support.ClassFilters.IntersectionClassFilter;
import org.springframework.uaa.client.VersionHelper.GetNumbersResult;




class IndexController {

	def index() {
		String fileName = "can"
		String path = "/home/alagenchev/"
		def url = path+fileName+".jpg"
		BufferedImage img = ImageIO.read(new File(url));

		def nodes = []
		ArrayList<TSPLine> lines = new ArrayList<TSPLine>()

		BufferedImage blackWhite = toBinaryImage(img);

		ImageIO.write(blackWhite, "jpg", new File(path + fileName + "_blackWhite.jpg"))
		
		slidingWindowPixelate(blackWhite, nodes)
		//ImageIO.write(blackWhite, "jpg", new File("/home/alagenchev/blackWhite.jpg"))

		//return
		//def result = pixelate(img, 1, nodes)

		//		nodes.add(new TSPNode(100, 100, false))
		//		nodes.add(new TSPNode(200, 200, false))
		//		nodes.add(new TSPNode(100, 200, false))
		//		nodes.add(new TSPNode(200, 100, false))

		BufferedImage result2 = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);



		def startNode = nodes[0]
		startNode.Visited = true

		TSPNode nearestNode = getNearestNode(startNode, nodes)

		while(nearestNode != null)
		{
			TSPLine line = createNearestLine(startNode, nearestNode)
			def distance = (line.EndX - line.StartX)* (line.EndX - line.StartX) + (line.EndY - line.StartY)*(line.EndY - line.StartY)

			if(distance < 3000)
			{
				lines.add(line)
			}
			nearestNode.Visited = true;

			startNode = nearestNode
			nearestNode = getNearestNode(nearestNode, nodes)

		}

		for(int i = 0; i < img.getWidth(); i ++) {
			for(int j = 0; j < img.getHeight(); j ++) {
				result2.setRGB(i, j, Color.WHITE.getRGB())
			}
		}

		nodes.each{
			result2.setRGB(it.X, it.Y, Color.BLACK.getRGB())
		}

		ImageIO.write(result2, "jpg", new File(path + fileName + "_dots.jpg"))
		
		
		Graphics2D g = result2.createGraphics()
		g.setColor(Color.BLACK)
		BasicStroke bs = new BasicStroke(2);
		g.setStroke(bs);


		/*
		 for(int i = 0; i < lines.size; i++)
		 {
		 /*if(i == 6 || i == 8)
		 {
		 lines[i].ShouldDraw = false
		 }*/

		/*
		 for(int j = 0; j < lines.size; j++)
		 {
		 if(j != i && lines[i].ShouldDraw && lines[j].ShouldDraw)
		 {
		 /*if(i == 6 && j == 8)
		 {
		 println "these intersect"
		 }*/
		/*
		 boolean doIntersect = intersection(lines[i].StartX, lines[i].StartY,
		 lines[i].EndX, lines[i].EndY,lines[j].StartX, lines[j].StartY, lines[j].EndX, lines[j].EndY)
		 if(doIntersect)
		 {
		 ArrayList<TSPLine> newTour = apply2optMove(lines,i ,j)
		 int length = getTourLength(newTour)
		 int oldLength = getTourLength(lines)
		 if(length < oldLength)
		 {
		 lines = newTour
		 }
		 }
		 }
		 }
		 }
		 */

		/*
		 int count = 0
		 while(count < 100)
		 {
		 ArrayList<TSPLine> newTour = apply2optMove(lines)
		 int newLength = getTourLength(newTour)
		 int oldLength = getTourLength(lines)
		 if(newLength < oldLength)
		 {
		 lines = newTour
		 }
		 count++
		 }
		 */
		lines.each {

			//if(distance < 20)
			//{
			g.drawLine(it.StartX, it.StartY, it.EndX, it.EndY)
			//}
		}

		ImageIO.write(result2, "jpg", new File("/home/alagenchev/result2.jpg"))

	}

	private int getTourLength(ArrayList<TSPLine> lines)
	{
		int length = 0

		lines.each
		{
			def distance = (it.EndX - it.StartX)* (it.EndX - it.StartX) + (it.EndY - it.StartY)*(it.EndY - it.StartY)
			length +=distance
		}

		length
	}
	private ArrayList<TSPLine> apply2optMove(ArrayList<TSPLine> lines, int i , int j)
	{
		ArrayList<TSPLine> list = new ArrayList<TSPLine>()
		lines.each
		{ list.add(it) }


		int tempx = list[i].EndX
		int tempy = list[i].EndY
		list[i].EndX = list[j].EndX
		list[i].EndY = list[j].EndY
		list[j].EndX = tempx
		list[j].EndY = tempy


		list
	}

	private TSPLine createNearestLine(TSPNode source, TSPNode destination)
	{
		new TSPLine(source.X, source.Y, destination.X, destination.Y)
	}

	private TSPNode getNearestNode(TSPNode source, def nodes)
	{
		int currentDistance = Integer.MAX_VALUE
		TSPNode nearestNode = null

		nodes.each {
			if(!it.Visited)
			{
				def distance = (it.X - source.X)* (it.X - source.X) + (it.Y - source.Y)*(it.Y - source.Y)
				if(currentDistance > distance)
				{
					currentDistance = distance
					nearestNode = it
				}
			}
		}

		if(currentDistance == Integer.MAX_VALUE){
			println ""
		}
		nearestNode
	}

	public static void slidingWindowPixelate(BufferedImage image, def nodes)
	{
		int slidingWindow = 4
		int threshold = 4
		
		int blackRGB = Color.black.getRGB()
		for(int i = 0; i < image.getWidth(); i+=slidingWindow)
		{
			for(int j = 0; j< image.getHeight(); j+=slidingWindow)
			{
				int count = 0;
				for(int k = i; k < i+slidingWindow && k< image.getWidth(); k++)
				{
					for(int m = j; m < j+slidingWindow && m < image.getHeight(); m++)
					{

						def rgb = image.getRGB(k, m)

						if(rgb == blackRGB)
						{
							count ++;
						}
					}
				}


				boolean lastBlack = false
				
				for(int k = i; k < i+slidingWindow && k< image.getWidth(); k++)
				{
					for(int m = j; m < j+slidingWindow && m < image.getHeight(); m++)
					{
						def random = new java.util.Random()
						int nextInt = random.nextInt(100)

						if(count > threshold && nextInt < 20 && !lastBlack)//make this pixel black
						{
							setColor(image, k, m, 1, Color.BLACK)
							nodes.add(new TSPNode(k,m, false))
							lastBlack = true
						}

						//else if(count < threshold && nextInt < 2 && !lastBlack)
						//{
							//setColor(image, k, m, 1, Color.BLACK)
							//nodes.add(new TSPNode(k,m, false))
							//lastBlack = true
						//}
						else//make all others white
						{
							lastBlack = false
							setColor(image, k, m, 1, Color.WHITE)
						}
					}
				}

			}
		}

	}
	public static BufferedImage toBinaryImage(final BufferedImage image) {
		final BufferedImage blackAndWhiteImage = new BufferedImage(
				image.getWidth(null),
				image.getHeight(null),
				BufferedImage.TYPE_BYTE_BINARY);
		final Graphics2D g = (Graphics2D) blackAndWhiteImage.getGraphics();
		g.drawImage(image, 0, 0, null);
		g.dispose();
		return blackAndWhiteImage;
	}

	public static BufferedImage pixelate(BufferedImage img, int size, def nodes) {
		BufferedImage dest = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);


		for (int x = 0; x < dest.getWidth(); x+=1) {
			for (int y = 0; y < dest.getHeight(); y+=1) {
				dest.setRGB(x, y, Color.WHITE.getRGB())
			}
		}

		for (int x = 0; x < img.getWidth(); x+=size) {
			for (int y = 0; y < img.getHeight(); y+=size) {


				int rgbVal = img.getRGB(x, y)

				def color = new Color(rgbVal)

				def red = color.getRed()
				def green = color.getGreen()
				def blue = color.getBlue()

				def average = (red + green + blue)/3

				if(average > 120) {
					setColor(dest, x, y, 1, Color.WHITE)
				}
				else {
					setColor(dest, x, y, 1, Color.BLACK)
					nodes.add(new TSPNode(x,y, false))
				}
			}
		}

		return dest;
	}
	private static void setColor(BufferedImage img, int x, int y, int size, Color color) {

		for(int i = x; i < x + size; i ++ ) {
			for(int j = y; j < y + size; j++) {
				img.setRGB(i, j, color.getRGB())
			}
		}
	}

	public static boolean intersection( double x1,double y1,double x2,double y2, double x3, double y3, double x4,double y4 )
	{
		if(x2 == x3 && y2 == y3)
		{
			return false;
		}

		if(x1 == x4 && y1 == y4)
		{
			return false;
		}
		double d = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
		if (d == 0)
			return false;
		double xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/d;
		double yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/d;
		if(x3==x4)
		{
			if ( yi < Math.min(y1,y2) || yi > Math.max(y1,y2) )
				return false;
		}

		if (xi < Math.min(x1,x2) || xi > Math.max(x1,x2))
			return false;
		if (xi < Math.min(x3,x4) || xi > Math.max(x3,x4))
			return false;

		return true;
	}

	static boolean IsOnSegment(double xi, double yi, double xj, double yj,
			double xk, double yk) {
		return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
		(yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
	}

	static char ComputeDirection(double xi, double yi, double xj, double yj,
			double xk, double yk) {
		double a = (xk - xi) * (yj - yi);
		double b = (xj - xi) * (yk - yi);
		return a < b ? -1 : a > b ? 1 : 0;
	}

	/** Do line segments (x1, y1)--(x2, y2) and (x3, y3)--(x4, y4) intersect? */
	static boolean DoLineSegmentsIntersect(double x1, double y1, double x2, double y2,
			double x3, double y3, double x4, double y4) {
		if(x2 == x3 && y2 == y3)
		{
			return false;
		}

		if(x1 == x4 && y1 == y4)
		{
			return false;
		}
		char d1 = ComputeDirection(x3, y3, x4, y4, x1, y1);
		char d2 = ComputeDirection(x3, y3, x4, y4, x2, y2);
		char d3 = ComputeDirection(x1, y1, x2, y2, x3, y3);
		char d4 = ComputeDirection(x1, y1, x2, y2, x4, y4);
		boolean result = (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
				((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
				(d1 == 0 && IsOnSegment(x3, y3, x4, y4, x1, y1)) ||
				(d2 == 0 && IsOnSegment(x3, y3, x4, y4, x2, y2)) ||
				(d3 == 0 && IsOnSegment(x1, y1, x2, y2, x3, y3)) ||
				(d4 == 0 && IsOnSegment(x1, y1, x2, y2, x4, y4));

		if(result)
		{
			System.out.printf("(%f, %f)--(%f, %f) and (%f, %f)--(%f, %f) intersect\n", x1,y1,x2,y2,x3,y3,x4,y4)
		}

		return result
	}
}
