import java.util.Scanner;

public class Ordered {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int x = sc.nextInt();
		int y = sc.nextInt();
		int z = sc.nextInt();
		boolean b = true;
		
		if (x < y && y < z) {
			System.out.print(b);
		}
		else if (x > y && y > z) {
			System.out.print(b);
		}
		else {
			System.out.println(!b);
		}
		
		sc.close();
	}

}
