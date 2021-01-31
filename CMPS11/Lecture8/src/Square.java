
public class Square extends Shape{
	double side;
	Square(){
		super(); // equal to calling Shape();
		//side = 0;
		this(0);
	}
	
	Square(double side){
		this.side = side;
		
	}
	
	double getArea() {
		return side * side;
	}

	double getPerimeter() {
		return 4 * side;
	}
	
	public String toString() {
		return "Square with side = " + this.side;
	}
}
// what's an object what's a class?
// what is inheritance?
// short answer, writing code, giving the result, or giving the error
