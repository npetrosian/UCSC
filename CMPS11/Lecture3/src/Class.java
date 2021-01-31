import java.util.Scanner;

public class Class {

	public static void main(String[] args) {
		int[] x = {1, 2, 3};
		int [] y = {4, 5, 6};
		int result = 0;
		for (int i = 0; i < 3; i++) {
			result += x[i]*y[i];
		}
		System.out.println(result);
		
		Scanner sc = new Scanner(System.in);
		
		for (int i = 0; i < 3; i++) {
			x[i] = sc.nextInt();
		}
		
		for (int i = 0; i < 3; i++) {
			System.out.print(x[i] + " ");
		}
		int size = sc.nextInt();
		char[] c = new char [size];
		
		for (int i = 0; i < size; i++) {
			c[i] = 'a';
		}
		for (int i = 0; i < size; i++) {
			System.out.print(c[i] + " ");

		}

	
		
	}

}
