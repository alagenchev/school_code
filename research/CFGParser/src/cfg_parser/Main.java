package cfg_parser;

import java.io.FileReader;
import java.io.PrintWriter;
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
		String file = "/home/alagenchev/school_code/research/research_software/sudo-1.8.0/src/sudo.c.013t.cfg";
		FileReader reader = new FileReader(file);
		Scanner scanner = new Scanner(reader);
		boolean finish = false;
		String line = "";
		String label = "";
		
		boolean inLabel = false;
		while(scanner.hasNext())
		{
			line = scanner.nextLine();
			
			if(line.startsWith("<L") && line.endsWith(">:"))
			{
				inLabel = true;
			}
			else if(inLabel && line.trim().equals(""))
			{
				System.out.println("label: " + label);
				inLabel = false;
				label = "";
			}
			
			if(inLabel)
			{
				label += line;
				label+="|";
			}
		}
		
		
		
		reader.close();
		System.exit(0);
		reader = new FileReader(file);
		scanner = new Scanner(reader);
		
		line = "";
		String bbl = "";
		while (scanner.hasNext())
		{
			if( !finish )
			{
				line = scanner.nextLine();
				line += "|";
			}

			if( line.contains("}") )
			{
				finish = true;
			}

			if( line.startsWith("<bb ") && line.endsWith(">:") || finish )
			{
				if( bbl != null && line != "" )
				{
					parser.parseBBL(bbl);
				}
				if( finish )
				{
					break;
				}

				bbl = new String();
				bbl += line;
			}
			else
			{
				bbl += line;

			}
		}
		
		

		
		BallLarus larus = new BallLarus();
		ArrayList<BasicBlock> blocks = parser.GetBlocks();
		larus.CalculateValues(blocks);
		String graph = larus.GetDOT(blocks);
		
		
		//String graph = parser.BlocksToDOT();

		PrintWriter writer = new PrintWriter(
				"/home/alagenchev/parser_graph.dot", "UTF-8");
		graph = graph.replace("|", "\\n");
		writer.println(graph);
		writer.close();

		System.out.println("done");

	}

}
