import java.util.Scanner;

public class Bits {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int N = sc.nextInt();
		int counter = 0;
	
		if (N <= 0) {
			System.out.println("Illegal input");
		}
		else {
			while (N >= 1) {
				N = N/2;
				counter++;
			}
			System.out.println(counter);
		}
			
		sc.close();
	}
	
}
