package TSPArt

import java.awt.image.BufferedImage;
import java.util.Random;
import java.awt.Color;
import javax.imageio.ImageIO;




class IndexController {

	def index() {
		def url = "/home/alagenchev/dog.jpg"
		BufferedImage img = ImageIO.read(new File(url));

		def nodes = []
				
		def result = pixelate(img, 4, nodes)


		BufferedImage result2 = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);

		for(int i = 0; i < img.getWidth(); i ++) {
			for(int j = 0; j < img.getHeight(); j ++) {
					result2.setRGB(i, j, Color.WHITE.getRGB())
				}
		}
		
		nodes.each{
			result2.setRGB(it.X, it.Y, Color.BLACK.getRGB())
		}

		ImageIO.write(result2, "jpg", new File("/home/alagenchev/result2.jpg"))
		ImageIO.write(result, "jpg", new File("/home/alagenchev/result.jpg"))
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
					nodes.add(new TSPNode(x,y))
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
