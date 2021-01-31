
public class Cubes1 {

	public static void main(String[] args) {
		for (int i = 1; i <= 4; i++) {
			int c = cube (i);
			//System.out.println(c);
		}

	}

	private static int cube(int i) {
		//System.out.println(c);
		int j = i * i * i;
		System.out.println(i + " " + j);
		return j;
		//return i * i * i;
		//i = i * i * i;
		//return i;
	}

}
