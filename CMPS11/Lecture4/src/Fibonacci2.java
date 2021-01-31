
public class Fibonacci2 {

	public static void main(String[] args) {
		int n = 7;
		int[] fibs = new int[8];
		fibs[1] = 0;
		fibs[2] = 1;
		for(int i = 3; i <= n; i++)
			fibs[i] = fibonacci(i);
		System.out.println(fibs[7]);
	}
	private static int fibonacci(int n) {
		System.out.println("Calculate Fib of " + n);
		if(n == 1) {
			System.out.println("Returning Fib of 1");
			return 0;
		}
		else if(n == 2) {
			System.out.println("Returning Fib of 2");
			return 1;
		}
		else if(n >= 3) {
			int result = 0;
			int first = fibonacci(n-2);
			int second = fibonacci(n-1);
			result = first + second;
			System.out.println("Returning Fib of " + n);
			return result;
		}
		else {
			return 0;
		}
	}
}