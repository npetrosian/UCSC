public class Shape {
	boolean shapeIsCalled;
	Shape(){
		shapeIsCalled = true;
		System.out.println("A shape is created.");
	}
	public static void main(String args[]) {
		new Circle();
	}

}
