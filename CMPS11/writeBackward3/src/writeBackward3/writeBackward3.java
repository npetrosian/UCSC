package writeBackward3;

public class writeBackward3 {

	public static void main(String[] args) {
		writeBackward3("abc");

	}
	static void writeBackward3(String s) {
		if(s.length() > 0) {
			System.out.print(s.charAt(0));
			writeBackward3(s.substring(1));
			System.out.print(s.charAt(0));
		}
	}

}
