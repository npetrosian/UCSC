
public class University {
	
	// Fields
	int rank;
	long numberOfStudents;
	String name;
	String country;
	String city;
	
	University(int r, long n, String newName, String c, String ci){
		rank = r;
		numberOfStudents = n;
		name = newName;
		country = c;
		city = ci;
	}
	void admit() {
		numberOfStudents++;
	}
	
	void changeName(String newName) {
		name = newName;
	}
	
	String getName() {
		return name;
	}
	
	
	// Methods
	public static void main(String[] args) {
		String name = new String("UCSC");
		University u = new University(1, 200, "UCSC", "USA", "Santa Cruz");
		
		System.out.println(u.numberOfStudents);
		
		u.rank = 1;
		u.country = "USA";
		u.changeName(name);
		System.out.println(u.getName());
		System.out.println(u.rank);
		
		u.admit();
		System.out.println(u.numberOfStudents);
		u.admit();
		System.out.println(u.numberOfStudents);
		
		String s = new String ("Hello");
		System.out.println(s);
		
		University [] universities = new University[10];
		universities[0] = new University(2, 200, "UCSC", "USA", "Santa Cruz");
		int rank = universities[0].rank;
		System.out.println(rank);
		
	}

}
