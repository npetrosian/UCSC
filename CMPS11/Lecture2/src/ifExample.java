import java.util.Scanner;

public class ifExample {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int number = sc.nextInt();
		if(number > 0) 
			System.out.println("Number was positive");
		else if (number == 0)
			System.out.println("Number is 0");
		else
			System.out.println("Number was negative");
		
		
	}

}
