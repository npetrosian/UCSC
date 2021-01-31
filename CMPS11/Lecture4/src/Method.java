
public class Method {

	public static void main(String[] args) {
		int num1 = 10;
		int num2 = 20;
		int sum = add(num1, num2);
		System.out.println(sum);
		double [] d = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
		double avg = average(d);
		System.out.println(avg);
		addWithoutReturn(num1, num2);
		String str = StringOfAs(5);
		System.out.println(str);
	}
	
	private static String StringOfAs(int j) {
		String ret = "";
		for(int i = 0; i < i; i++) {
			ret += "a";
		}
		return ret;
	}

	private static void addWithoutReturn(int num1, int num2) {
		System.out.println(num1 + " + " + num2 + " = " + (num1 + num2));
		
	}

	private static double average(double []d) {
		double sum = 0;
		for(int i = 0; i < d.length; i++) {
			sum += d[i];
		}
		double average = sum/d.length;
		return average;
	}
		

	private static int add(int a, int b) {
		return a + b;
	}
	


}
