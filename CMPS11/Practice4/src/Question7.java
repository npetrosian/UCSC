public class Question7 {
public static void main(String[] args) {
Sandwich x = new Sandwich(1.0,2.0);
Sub y = new Sub(3.0,4.0);
x = y;
y = x;    // type mismatch cannot convert from Sandwich to Sub
y = new Sandwich(1.0,2.0);  // type mismatch cannot convert from Sandwich to Sub
x = new Sub(1.2,1.4);
}
}


class Sandwich {

private double x;
private double y;

public Sandwich(double x, double y) {
this.x = x;
this.y = y;
}

public double getX() {
return x;
}

public double getY() {
return y;
}

public double getDistance(Sandwich point) {
return Math.sqrt(Math.pow(point.x - this.x, 2) + Math.pow(point.y - this.y, 2));
}
}

class Sub extends Sandwich {

public Sub(double x, double y) {
super(x, y);
System.out.println("Sub is ready");
}

}
