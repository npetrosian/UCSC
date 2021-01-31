
public class Shape {
	String color = "";
	int id;
	
	Shape(){
		color = "white";
		id = 0;
	}
	Shape(String color, int id){
		this.color = color;
		this.id = id;
	}
	
	void setColor(String color) {
		if(color.equals("white") || color.equals("red") || color.equals("blue") || color.equals("green")) {
			this.color = color;
		}
	}
	
	public static void main(String[] args) {
		Shape s = new Shape();
		s.setColor("blue");
		System.out.println(s.color);
		
		Square sq = new Square();
		System.out.println(sq);
		System.out.println(sq.color + " " + sq.id);

	}

}
