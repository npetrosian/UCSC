
public class Circle {

	double radius;
	double centerX;
	double centerY;
	String color;
	
	// constructor
	// two different variables in different scopes with the same name
	Circle(double radius, double centerX, double centerY, String color){ 
		this.radius = radius;
		this.centerX = centerX;
		this.centerY = centerY;
		this.color = color;
	}
	
	Circle(){
		this(0, 0, 0, "white");
		//this.radius = 0;
		//this.centerX = 0;
		//this.centerY = 0;
		//this.color = "white";
	}
	
	void setRadius(double r) {
		if (r >= 0)
			this.radius = r;
			// radius = r;
	}
	
	void setCenterX(double x) {
		this.centerX = x;
	}
	
	void setCenterY(double y) {
		this.centerY = y;
	}
	
	void setColor(String color) {
		if(color.equals("white") || color.equals("red") || color.equals("blue") || color.equals("green")) {
			this.color = color;
		}
	}
	
	// don't need to pass radius as an argument
	double getArea() {
		// option 1: return 3.14 * this.radius * this.radius
		return Math.PI * Math.pow(this.radius, 2); // option 2
	}
	
	double getPerimeter() {
		return 2 * Math.PI * this.radius;
	}
	
	double distance(Circle other) {
		// (x1,y1) (x2,y2) --> ((x1-x2)^2 + (y1-y2)^2)
		double xDistance = Math.pow((this.centerX - other.centerX), 2);
		double yDistance = Math.pow((this.centerY - other.centerY), 2);
		return Math.sqrt(xDistance + yDistance);
	}
	
	public String toString() {
		return "Radius: " + this.radius + " Center: (" + this.centerX + ", " + this.centerY + ") Color: " + this.color;
	}
	
	// this.radius refers to c1
	public static void main(String[] args) {
		Circle c1 = new Circle(1, 3, 4, "blue");
		Circle c2 = new Circle();
		c1.setRadius(10);
		c1.setColor("black");
		System.out.println(c1.toString());
		System.out.println(c2.toString());

		double area1 = c1.getArea();
		double area2 = c2.getArea();
		
		double distance = c1.distance(c2);
		System.out.println(distance);
		

	}

}
