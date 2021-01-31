public class Question7 {

public static void main(String[] args) {
	int[] a1 = {1,3,4,7,10};
	int[] a2 = {2,0,4,3,12};
	int[] result;

	result = diff(a1,a2);

// check the result
	for (int i = 0; i < result.length; i++) {
		System.out.println(result[i]);
		}
	}
	public static int[] diff(int[] a1, int[] a2) {
		int[] a3 = new int[a1.length];
		for(int i = 0; i < a1.length; i++) {
			a3[i] = a1[i] - a2[i];
		}
		return(a3);
	}

}
