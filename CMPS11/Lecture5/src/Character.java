
public class Character {
	
	// prints ASCII code

	public static void main(String[] args) {
		char a = 'a';
		char y = 'y';
		
		int aInt = (int) a; // casting
		int yInt = (int) y;
		
		System.out.println(aInt); // 97
		System.out.println(yInt); // 121
		int dist = 'y' - 'a';
		System.out.println(aInt + dist);
		
		char [] alphabet = new char[26];
		for (int i = 0; i < alphabet.length; i++) {
			alphabet[i] = (char)(97 + i);
			System.out.println(alphabet[i]);
		}
		

	}

}
