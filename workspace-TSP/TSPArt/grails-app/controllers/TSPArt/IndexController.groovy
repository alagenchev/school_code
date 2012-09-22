package TSPArt

import java.awt.image.BufferedImage;
import java.util.Random;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import TSPArt.TSPLine
import TSPArt.TSPNode
import javax.imageio.ImageIO;

import org.springframework.uaa.client.VersionHelper.GetNumbersResult;




class IndexController {

	def index() {
		def url = "/home/alagenchev/gabi.jpg"
		BufferedImage img = ImageIO.read(new File(url));

		def nodes = []
		def lines = []

		def result = pixelate(img, 4, nodes)

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
			lines.add(line)
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

		Graphics2D g = result2.createGraphics()
		g.setColor(Color.BLACK)
		BasicStroke bs = new BasicStroke(2);
		g.setStroke(bs);

		lines.each {
			g.drawLine(it.StartX, it.StartY, it.EndX, it.EndY)
		}

		ImageIO.write(result2, "jpg", new File("/home/alagenchev/result2.jpg"))
		
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
}
