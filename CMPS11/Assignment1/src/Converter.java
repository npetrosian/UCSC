import java.util.Scanner;

public class Converter {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		char userCharInput = sc.next().charAt(0);
		double userTempInput = sc.nextDouble();
		double result = 0.0;
		
		if (userCharInput == 'f') {
			result = (userTempInput-32) * 5/9;
			System.out.printf("%.2f",result);
		}
		else if (userCharInput == 'k') {
			result = (userTempInput - 273.15);
			System.out.printf("%.2f",result);
		}
		
		sc.close();
		
	}
}
