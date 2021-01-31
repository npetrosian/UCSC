import java.util.Scanner;

public class Average {
	
	public static void main (String[] args) {
		Scanner myScan = new Scanner(System.in);
		String word = "";
		int totalWordLengths = 0;
		int totalNumWords = 0;
		int avgWordLength = 0;
		word = myScan.nextLine();
		while (word.length() > 0) {
			totalWordLengths += word.length();
			totalNumWords += 1;
			word = myScan.nextLine();
		}
		avgWordLength = totalWordLengths / totalNumWords;
		System.out.println(avgWordLength);
		myScan.close();
		
	}

}
