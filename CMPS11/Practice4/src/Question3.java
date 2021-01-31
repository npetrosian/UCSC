
public class Question3 {

	public static void main(String[] args) {
		String school = "";
		int grade = 100;
		
		if(grade <= 5) {
			school = "Elementary school";
		}
		if(grade <= 8 && grade > 5) {
			school = "Junior High";
		}
		if(grade <= 12 && grade > 8) {
			school = "High School";
		}
		if(grade > 12) {
			school = "College";
		}
		System.out.println(school);
	}

}
