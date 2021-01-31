import java.util.Scanner;

public class Series {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int w = sc.nextInt();
		int term = sc.nextInt();
		double euler_result = euler(w, term);
		System.out.printf("%.2f",euler_result);
		
		sc.close();
	}

	private static double euler(int w, int term) {
		double retVal = 0.0;
		if (term == 1) {
			retVal = 1;
		}
		else if (term == 2) {
			retVal = 1 + w;
		}
		else {
			if (term >= 3) {
				retVal = 1 + w;
				for (int i = 2; i <= term-1; i++) {
					retVal += Math.pow(w, i)/factorial(i);
				}
			}
		}
		return retVal;
	}

	private static int factorial(int n) {
		if(n == 0) {
			return 1;
		}
		else {
		 	return n*factorial(n-1);
		} 
		
	}
}