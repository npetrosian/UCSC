public class Path {

	Point[] points = new Point[200];
	int numberOfPoints;
	
	public Path() {
		this.numberOfPoints = 0;
	}
	
	Path addPoint(int x, int y) {
		points[numberOfPoints] = new Point(x,y);
		numberOfPoints++;
		return this;
	}
	
	String getPoint(int i) {
		return "(" + points[i].x + ", " + points[i].y + ")";
	}
	
	int numOfPoints() {
		return numberOfPoints;
	}
	
	public boolean removePoint(int r) {
		
		if (r >= numberOfPoints) {
			 return false;
		} 
		else {
			for (int i = r; i < numberOfPoints; i++) {
				points[i] = points[i+1];
			}
		}
		numberOfPoints--;
		return true;
		
	}
	
	void addPath(Path p) {
		for(int i = 0; i < p.numberOfPoints; i++) {
			this.points[this.numberOfPoints] = p.points[i];
			numberOfPoints++;
		}
	}
	
	double getLength() {
		double result = 0.0;
		if(numberOfPoints < 2) {
			return 0.0;
		}
		for(int i = 0; i <= numberOfPoints-2; i++) {
			result += Math.sqrt(Math.pow(points[i].x - points[i+1].x, 2) + Math.pow(points[i].y - points[i+1].y, 2));
		}
		return result;
	}
	
	double getDistance() {
		if(numberOfPoints < 2) {
			return 0.0;
		}
		return Math.sqrt(Math.pow(points[0].x - points[numberOfPoints-1].x, 2) + Math.pow(points[0].y - points[numberOfPoints-1].y, 2));
	}
	
	boolean isLonger(Path p) {
		if (this.getLength() > p.getLength()) {
			return true;
		}
		else {
			return false;
		}
	}

	public void printPoints(){
		for(int i = 0; i < numberOfPoints; i++) {
			System.out.printf("%d, %d \n", points[i].x, points[i].y);
		}
		System.out.println();
	}

}

class Point {
	int x;
	int y;
	public Point(int x, int y){
		this.x = x;
		this.y = y;
	}
	public String toString() {
		return x + ", " + y;
	}
}

