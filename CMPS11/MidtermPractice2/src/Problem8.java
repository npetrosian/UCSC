import java.util.Scanner;
public class Problem8 {

	static final Scanner in = new Scanner(System.in);
	public static void main(String[] args) {
	    int length = in.nextInt();
	    for (int i = 1; i <= length; i++) {
	    		printXOs(length, length-i);
	    }
	}
	static void printXOs (int len, int xLen) {
		
		for (int i=0; i <= xLen; i++) {
			System.out.print("X");
		}
		for (int i=1; i < len - xLen; i++) {
			System.out.print("O");
		}
		System.out.println();
	}
}
