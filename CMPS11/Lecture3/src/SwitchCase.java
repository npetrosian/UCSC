import java.util.Scanner;

public class SwitchCase {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int number = sc.nextInt();
		switch(number) {
		case 0: 
			System.out.println("Done");
			break;
		case 1: 
			System.out.println("One");
			break;
		case 2: 
			int first = sc.nextInt();
			int second = sc.nextInt();
			System.out.println(first + second);
			break;
		default:
			System.out.println("Not a valid option");
			break; // break statement after default is optional
		}
		sc.close();

	}

}
