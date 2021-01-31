
class Point {
	
	double x;
	double y;
	
	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double getX() {
		return x;
	}
	
	public double getY() {
		return y;
	}
	
	public double getDistance(Point point) {
		return Math.sqrt(Math.pow(point.x - this.x, 2) + Math.pow(point.y - this.y, 2));
	}
}

abstract class Shape{
	public abstract double getArea();
	
	public abstract double getPerimeter();
	
}

interface Symmetric{
	Point getPointOfSymmetry();
}

class Triangle extends Shape{
	
	Point firstPoint;
	Point secondPoint;
	Point thirdPoint;
	
	public Triangle(Point firstPoint, Point secondPoint, Point thirdPoint) {
		
		this.firstPoint = firstPoint;
		this.secondPoint = secondPoint;
		this.thirdPoint = thirdPoint;
	}
	
	public Triangle(Point topPoint, double side) {
		double x2;
		double y2;
		double x3;
		double y3;
		double height;
		
		height = (side * Math.sqrt(3.0) * 0.5);
		x2 = topPoint.x - side/2;
		y2 = topPoint.y - height;
		x3 = topPoint.x + side/2;
		y3 = y2;
		
		firstPoint = topPoint;
		secondPoint = new Point(x2, y2);
		thirdPoint = new Point(x3, y3);
		
	}
	
	public Point getFirstPoint() {
		return this.firstPoint;
	}
	
	public Point getSecondPoint() {
		return this.secondPoint;
	}
	
	public Point getThirdPoint() {
		return this.thirdPoint;
	}
	
	public double getArea() {
		double x1 = firstPoint.x;
		double x2 = secondPoint.x;
		double x3 = thirdPoint.x;
		double y1 = firstPoint.y;
		double y2 = secondPoint.y;
		double y3 = thirdPoint.y;
		
		return Math.abs(0.5*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));
	}
	
	public double getPerimeter() {
		return this.firstPoint.getDistance(this.secondPoint) + this.secondPoint.getDistance(this.thirdPoint) + this.thirdPoint.getDistance(this.firstPoint);
	}
}

class Rectangle extends Shape {
	
	Point topLeftPoint;
	double length;
	double width;
	
	public Rectangle (Point topLeftPoint, double length, double width) {
		this.topLeftPoint = topLeftPoint;
		this.length = length;
		this.width = width;
	}
	
	public Point getTopLeftPoint() {
		return topLeftPoint;
	}
	
	public double getLength() {
		return length;
	}
	
	public double getWidth() {
		return width;
	}
	
	public double getArea() {
		return length * width;
	}
	
	public double getPerimeter() {
		return (2 * length) + (2 * width);
	}
}

class Trapezoid extends Shape {
	
	Point topLeftPoint;
	Point bottomLeftPoint;
	double topSide;
	double bottomSide;
	
	public Trapezoid (Point topLeftPoint, Point bottomLeftPoint, double topSide, double bottomSide) {
		this.topLeftPoint = topLeftPoint;
		this.bottomLeftPoint = bottomLeftPoint;
		this.topSide = topSide;
		this.bottomSide = bottomSide;
	}
	
	public Point getTopLeftPoint() {
		return topLeftPoint;
	}
	
	public Point getBottomLeftPoint() {
		return bottomLeftPoint;
	}
	
	public double getTopSide() {
		return topSide;
	}
	
	public double getBottomSide() {
		return bottomSide;
	}
	
	public double getArea() {
		return ((bottomSide + topSide)*(topLeftPoint.y - bottomLeftPoint.y))/2;
	}
	
	public double getPerimeter() {
		
		double x1 = topLeftPoint.x;
		double y1 = topLeftPoint.y;
		double x2 = bottomLeftPoint.x;
		double y2 = bottomLeftPoint.y;
		double x3 = x2 + bottomSide;
		double y3 = y2;
		double x4 = x1 + topSide;
		double y4 = y1;
		Point bottomRightPoint;
		Point topRightPoint;
		
		bottomRightPoint = new Point (x3,y3);
		topRightPoint = new Point (x4,y4);
		
		return topSide + bottomSide + topLeftPoint.getDistance(bottomLeftPoint) + topRightPoint.getDistance(bottomRightPoint);
	}
}

class Circle extends Shape implements Symmetric {
	
	Point center;
	double radius;
	
	public Circle (Point center, double radius) {
		this.center = center;
		this.radius = radius;
	}
	
	public Point getCenter() {
		return center;
	}
	
	public double getRadius() {
		return radius;
	}
	
	public double getArea() {
		return Math.PI * radius * radius;
	}
	
	public double getPerimeter() {
		return 2 * Math.PI * radius;
	}
	
	public Point getPointOfSymmetry() {
		return center;
	}
}

class EquilateralTriangle extends Triangle implements Symmetric{
	
	Point topPoint;
	double side;
	
	public EquilateralTriangle(Point topPoint, double side) {
		
		super(topPoint, side);
		this.topPoint = topPoint;
		this.side = side;
	}
	
	public Point getTopPoint() {
		
		return topPoint;
	}
	
	public double getSide() {
		
		return side;
	}
	
	public Point getPointOfSymmetry() {
		
		double height;
		double x;
		double y;
		Point pointOfSymmetry;
		
		height = firstPoint.y - secondPoint.y;
		x = firstPoint.x;
		y = firstPoint.y - (2/3 * height);
		
		pointOfSymmetry = new Point(x, y);
		
		return pointOfSymmetry; 
	}
	
}

class Square extends Rectangle implements Symmetric {
	
	Point topLeft;
	double side;
	
	public Square (Point topLeft, double side) {
		
		super(topLeft, side, side);
		this.topLeft = topLeft;
		this.side = side;
	}
	
	public double getSide() {
		
		return side;
	}
	
	public Point getPointOfSymmetry() {
	
		double x;
		double y;
		Point pointOfSymmetry;
		
		x = topLeft.x + side/2;
		y = topLeft.y - side/2;
		
		pointOfSymmetry = new Point(x, y);
		
		return pointOfSymmetry;
	}
}

public class Plane {
	
	Shape[] shapes = new Shape[200];
	int numberOfShapes;
	
	public Plane() {
		
		this.numberOfShapes = 0;
	}
	
	public Shape[] getShape () {
		
		return shapes;
	}
	
	public void addShape(Shape shape) {
		
		shapes[numberOfShapes] = shape;
		numberOfShapes++;
	}
	
	public double getSumOfAreas() {
		
		double sumOfAreas = 0.0;
		
		for(int i = 0; i < numberOfShapes; i++) {
			sumOfAreas += shapes[i].getArea(); 
		}
		
		return sumOfAreas;
	}
	
	public double getSumOfPerimeters() {
		
		double sumOfPerimeters = 0.0;
		
		for(int i = 0; i < numberOfShapes; i++) {
			sumOfPerimeters += shapes[i].getPerimeter();
		}
		
		return sumOfPerimeters;
	}
	
	public Point getCenterOfPointOfSymmetries() {
		
		Point point;
		double sumOfX = 0.0;
		double sumOfY = 0.0;
		int counter = 0;
		
		for(int i = 0; i < numberOfShapes; i++) {
			
			if(shapes[i] instanceof Symmetric) {
				point = ((Symmetric) shapes[i]).getPointOfSymmetry(); // cast fixed by eclipse
				sumOfX += point.x;
				sumOfY += point.y;
				counter++;
			}
		}
		
		if(counter == 0) {
			return null;
		}
		
		else {
			
			double xAverage;
			double yAverage;
			Point centerOfPointOfSymmetry;
			
			xAverage = sumOfX/counter;
			yAverage = sumOfY/counter;
			
			centerOfPointOfSymmetry = new Point(xAverage, yAverage);
			
			return centerOfPointOfSymmetry;
		}
			
	}
	
	public static void main(String[] args) {
		Point p1 = new Point(1,2);
		Point p2 = new Point(3,4);
		Point p3 = new Point(5,6);
		Triangle t1 = new Triangle(p1, p2, p3);
		Plane plane1 = new Plane();
		plane1.addShape(t1);
		
	}
}