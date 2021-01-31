
public class Arrays {

	public static void main(String[] args) {
		int[][] a = new int [3][4];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				a[i][j] = i;
			}
		}
		
		//int []c = {1, 2, 3};
		
		int [][] b = {
				{1, 2, 3, 3},
				{2, 3, 4, 4},
				{3, 4, 5, 5} 
				};
		//int [][] c = new int [3][4];
		int [][] c = new int[3][4];
		// First Row
		c[0] = new int [4];
		// Second row
		c[1] = new int [4];
		// third row
		c[2] = new int [4];
 		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				c[i][j] = a[i][j] + b[i][j];
				}
			}
		
		for (int i = 0; i < c.length; i++) {
			for (int j = 0; j < c[i].length; j++) {
				System.out.print(c[i][j] + " ");
			}
			System.out.println();
		}
			

	}

}
