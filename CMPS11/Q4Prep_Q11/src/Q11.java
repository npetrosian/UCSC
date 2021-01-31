import java.util.Arrays;

public class Q11 {
	
	public static void sortWords(String[] W){
		int i;
		int j;
		String temp;
		for(j = 1; j < W.length; j++){
		     temp = W[j];
		     i = j - 1;
		     while (i >= 0 && temp.compareTo(W[i]) <= 0){
		        W[i+1] = W[i];
		        i--;
		     }
		     W[i+1] = temp;

		 }
	}


	public static void main(String[] args) {
		String[] inputArray = {"Rachel","Phoebe","Joey","Chandler","Monica","Ross"};
	       
	    System.out.println(Arrays.toString(inputArray));
	    sortWords(inputArray);
	    System.out.println(Arrays.toString(inputArray));

	}

}
