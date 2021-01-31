
public class Factorial {

	public static void main(String[] args) {
		int n = 7;
		int result = factorial(n);
		System.out.println(result);
	}

	private static int factorial(int n) {
		if (n == 0)
			return 1;
		int result = 0;
		int temp = factorial(n-1);
		result = temp * n; // n * (n-1)!
		return result;
	}

}
