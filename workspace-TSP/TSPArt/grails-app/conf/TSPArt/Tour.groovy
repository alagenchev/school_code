package TSPArt

import com.sun.org.apache.xml.internal.serialize.LineSeparator;

class Tour {
	public Tour() {
		Lines = new ArrayList<TSPLine>()
	}
	ArrayList<TSPLine> Lines;

	public int getDistance() {
		int distance = 0
		Lines.each {
			distance += it.getDistance()
		}

		distance
	}
	@Override
	public String toString() {
		String temp = ":"
		Lines.each {
			temp+=it.toString()
			temp += "|"
		}
		return temp;
	}
}
