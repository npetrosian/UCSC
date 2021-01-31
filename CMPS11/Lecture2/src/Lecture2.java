import java.util.Scanner;

public class Lecture2 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int number = sc.nextInt();
		number++;
		System.out.println(number++);
		System.out.println(++number);
		
		String str = sc.next();
		char c = str.charAt(0);
		System.out.println(c);
		System.out.println(str);
		
		String str2 = sc.nextLine();
		System.out.println(str2);
		
		boolean b1 = sc.nextBoolean();
		boolean b2 = sc.nextBoolean();
		
		System.out.println(b1 && b2);
		
		sc.close();

	}

}
