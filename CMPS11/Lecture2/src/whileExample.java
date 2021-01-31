import java.util.Scanner;

public class whileExample {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int number = sc.nextInt();
		while (number != 0) {
			number = sc.nextInt();
		}
		System.out.println("You entered 0");
	}

}
