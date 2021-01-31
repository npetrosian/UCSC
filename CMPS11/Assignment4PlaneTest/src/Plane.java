
class Point {
	
	private double x;
	private double y;
	
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
	
	private Point firstPoint;
	private Point secondPoint;
	private Point thirdPoint;
	
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
		x2 = topPoint.getX() - side/2;
		y2 = topPoint.getY() - height;
		x3 = topPoint.getX() + side/2;
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
		double x1 = firstPoint.getX();
		double x2 = secondPoint.getX();
		double x3 = thirdPoint.getX();
		double y1 = firstPoint.getY();
		double y2 = secondPoint.getY();
		double y3 = thirdPoint.getY();
		
		return Math.abs(0.5*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)));
	}
	
	public double getPerimeter() {
		return this.firstPoint.getDistance(this.secondPoint) + this.secondPoint.getDistance(this.thirdPoint) + this.thirdPoint.getDistance(this.firstPoint);
	}
}

class Rectangle extends Shape {
	
	private Point topLeftPoint;
	private double length;
	private double width;
	
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
	
	private Point topLeftPoint;
	private Point bottomLeftPoint;
	private double topSide;
	private double bottomSide;
	
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
		return ((bottomSide + topSide)*(topLeftPoint.getY() - bottomLeftPoint.getY()))/2;
	}
	
	public double getPerimeter() {
		
		double x1 = topLeftPoint.getX();
		double y1 = topLeftPoint.getY();
		double x2 = bottomLeftPoint.getX();
		double y2 = bottomLeftPoint.getY();
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
	
	private Point center;
	private double radius;
	
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
	
	private Point topPoint;
	private double side;
	
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
		
		height = getFirstPoint().getY() - getSecondPoint().getY();
		x = getFirstPoint().getX();
		y = getFirstPoint().getY() - ((2.0/3.0) * height);

		pointOfSymmetry = new Point(x, y);
		
		return pointOfSymmetry; 
	}
	
}

class Square extends Rectangle implements Symmetric {
	
	private Point topLeft;
	private double side;
	
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
		
		x = topLeft.getX() + side/2;
		y = topLeft.getY() - side/2;
		
		pointOfSymmetry = new Point(x, y);
		
		return pointOfSymmetry;
	}
}

public class Plane {
	
	private Shape[] shapes = new Shape[200];
	private int numberOfShapes;
	
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
				sumOfX += point.getX();
				sumOfY += point.getY();
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
}