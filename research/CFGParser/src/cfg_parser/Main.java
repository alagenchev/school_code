package cfg_parser;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;
import ball_larus.*;

public class Main
{

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception
	{
		BlockFactory factory = new BlockFactory();
		
		BasicBlockParser parser = new BasicBlockParser(factory);
		FileReader reader = new FileReader("iwconfig.c.013t.cfg");
		Scanner scanner = new Scanner(reader);
		boolean finish = false;
		String line = "";
		String bbl = "";
		while (scanner.hasNext())
		{
			if(!finish)
			{
				line = scanner.nextLine();
				line+="|";
			}
			
			if(line.contains("}"))
			{
				finish = true;
			}
			
			if( line.indexOf("<bb ") == 0 && line.contains(">:") || finish)
			{
				if(bbl!=null && line!="")
				{
					parser.parseBBL(bbl);
				}
				if(finish)
				{
					break;
				}
				
				bbl = new String();
				bbl+=line;
			}
			else
			{
				bbl+=line;
				
			}
		}
		
		String graph = parser.BlocksToDOT();
		System.out.println(graph);

	}



}
