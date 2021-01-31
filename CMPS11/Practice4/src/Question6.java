public class Question6 {
	public static void main (String[] args) {
		Fruit[] elements = {new Gala(), new Fruit(), new Fuji(), new Apple()};
		for (int i = 0; i < elements.length; i++) {
		elements[i].method1();
		System.out.println();
		elements[i].method2();
		System.out.println();
		System.out.println(elements[i]);
		System.out.println();
		}
	}
}

class Gala extends Apple {
	public void method1() { System.out.print("gala 1 "); }
	public String toString() { return "gala " + super.toString(); }
}

 class Fruit {
	public void method1() { System.out.print("fruit 1 "); }
	public void method2() { System.out.print("fruit 2 "); }
	public String toString() { return "fruit"; }
}

 class Fuji extends Apple {
	public void method1() { System.out.print("fuji 1 "); }
}

 class Apple extends Fruit {
	public void method2() {
			method1();
			System.out.print("apple 2 ");
	}
    public String toString() { return "apple"; }
}
