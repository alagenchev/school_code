package TSPArt

import java.awt.image.BufferedImage;
import java.util.Random;
import java.awt.Color;
import javax.imageio.ImageIO;



class IndexController {

	def index() {
		def url = "/home/alagenchev/IMG_2204.JPG"
		BufferedImage img = ImageIO.read(new File(url));
		def result = pixelate(img, 4)


		ImageIO.write(result, "jpg", new File("/home/alagenchev/result.jpg"))
	}

	public static BufferedImage pixelate(BufferedImage img, int size) {
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

				if(average < 120) {
					setColor(dest, x, y, 1, Color.WHITE)
				}
				else
				{
					setColor(dest, x, y, 1, Color.BLACK)
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
