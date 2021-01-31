public class NameTest {
	
	public static void main(String[] args) {
		Name n1 = new Name("Narges", "Norouzi");
		Name n2 = new Name("Jane", "Programmer");
		System.out.println(n1);
		System.out.println(n2);
		System.out.println(n1.initials());
		System.out.println(n2.initials());		
	}
	
}

class Name {
	
	String firstName;
	String lastName;
	
	Name (String f, String l) {
		firstName = f;
		lastName = l;
	}
	public String initials() {
		return firstName.substring(0,1) + lastName.substring(0,1);		
	}
	public String toString() {
		return lastName + ", " + firstName;
	}
}