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
		TSPHelper tspHelper = new TSPHelper()
		def nodes = []
		ArrayList<TSPLine> lines = new ArrayList<TSPLine>()

		BufferedImage blackWhite = toBinaryImage(img);

		//ImageIO.write(blackWhite, "jpg", new File(path + fileName + "_blackWhite.jpg"))

		slidingWindowPixelate(blackWhite, nodes)
		//ImageIO.write(blackWhite, "jpg", new File("/home/alagenchev/blackWhite.jpg"))


		BufferedImage result2 = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);



		def startNode = nodes[0]
		startNode.Visited = true

		TSPNode nearestNode = getNearestNode(startNode, nodes)

		Tour tour = new Tour()
		while(nearestNode != null)
		{
			TSPLine line = tspHelper.createNearestLine(startNode, nearestNode)
			tour.Lines.add(line)
			nearestNode.Visited = true;

			startNode = nearestNode
			nearestNode = getNearestNode(nearestNode, nodes)

		}

		for(int i = 0; i < img.getWidth(); i ++) {
			for(int j = 0; j < img.getHeight(); j ++) {
				result2.setRGB(i, j, Color.WHITE.getRGB())
			}
		}


		for(int i = 0; i < 1; i ++)
		{
			Tour modifiedTour = tspHelper.apply2Opt(tour)

			if(modifiedTour.getDistance() < tour.getDistance())
			{
				tour = modifiedTour
			}
		}

		nodes.each{
			result2.setRGB(it.X, it.Y, Color.BLACK.getRGB())
		}

		//ImageIO.write(result2, "jpg", new File(path + fileName + "_dots.jpg"))


		Graphics2D g = result2.createGraphics()
		g.setColor(Color.BLACK)
		BasicStroke bs = new BasicStroke(1);
		g.setStroke(bs);


		tour.Lines.each {
			g.drawLine(it.StartX, it.StartY, it.EndX, it.EndY)
		}

		ImageIO.write(result2, "jpg", new File(path + fileName + "_result.jpg"))

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

		Random random = new Random(Date.getMillisOf(new Date()))



		int blackRGB = Color.black.getRGB()
		for(int i = 0; i < image.getWidth(); i+=slidingWindow)
		{
			for(int j = 0; j< image.getHeight(); j+=slidingWindow)
			{
				int count = 0;
				boolean hasBlack = false;

				for(int k = i; k < i+slidingWindow && k< image.getWidth(); k++)
				{
					for(int m = j; m < j+slidingWindow && m < image.getHeight(); m++)
					{

						def rgb = image.getRGB(k, m)

						if(rgb == blackRGB)
						{
							count ++;
						}

						if(count > threshold && !hasBlack)
						{
							int addK = random.nextInt((int)slidingWindow/2)
							int addM = random.nextInt((int)slidingWindow/2)

							//	setColor(image, k, m, 1, Color.BLACK)
							if(random.nextBoolean())
							{
								nodes.add(new TSPNode(k + addK,m + addM, false))
							}
							else
							{
								nodes.add(new TSPNode(k,m , false))
							}
							hasBlack = true;
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

	private static void setColor(BufferedImage img, int x, int y, int size, Color color) {

		for(int i = x; i < x + size; i ++ ) {
			for(int j = y; j < y + size; j++) {
				img.setRGB(i, j, color.getRGB())
			}
		}
	}


}
