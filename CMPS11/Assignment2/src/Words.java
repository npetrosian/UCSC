import java.util.Scanner;

public class Words {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String [] arrayOfWords = new String[n];
		int counter = 0;
		boolean returnVal;
		sc.nextLine(); 
		for(int i = 0; i <= n-1; i++) {
			arrayOfWords[i] = sc.nextLine();
		}
		for(int i = 0; i <=n-1; i++) {
			returnVal = repeatedCharacters(arrayOfWords[i]);
			if(returnVal == false) {
				counter++;
			}
		}
		System.out.println(counter);
		
		sc.close();
	}
		
	public static boolean repeatedCharacters(String word) {
		int [] alphabetposition = new int [26];
		int asciiCode;
		char letter; 
		int index;
		for(int i = 0; i < 26; i++) {
			alphabetposition[i] = 0;
		}
		for(int i = 0; i < word.length(); i++) {
			letter = word.charAt(i);
			asciiCode = (int)letter;
			index = asciiCode-97;
			alphabetposition[index] += 1;
		}
		for(int i = 0; i < 26; i++) {
			if(alphabetposition[i] > 1) {
				return true;
			}
		}
		return false;
		
	}
}
