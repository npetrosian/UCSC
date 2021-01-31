
public class Fibonacci {
	
	public static void main(String[] args) {
		int n = 7;
		int result = fibonacci(n);
		System.out.println(result);
	}
	//0, 1, 1, 2, 3, 5, 8
	private static int fibonacci(int n) {
		System.out.println("Calculate Fib of " + n);
		if(n == 1) {
			System.out.println("Returning Fib of 1");
			return 0;
		}
		if(n == 2) {
			System.out.println("Returning Fib of 2");
			return 1;
		}
		int result = 0;
		int first = fibonacci(n-2);
		int second = fibonacci(n-1);
		result = first + second;
		System.out.println("Returning Fib of " + n);
		return result;
	}
}
