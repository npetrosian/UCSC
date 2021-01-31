abstract class Animal{}
class Horse extends Animal{}
class Cow extends Animal {}
public class Test {
	public static void main(String []args) {
		Animal animal;
		Horse horse;
		animal = new Cow();
		horse = (Horse)animal;
	}

}
