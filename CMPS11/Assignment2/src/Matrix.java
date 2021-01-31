import java.util.Scanner;

public class Matrix {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int m = sc.nextInt(); // rows
		int n = sc.nextInt(); // columns
		char command = ' ';
		int [][] matrix = new int [m][n];
		
		for (int row = 0; row < matrix.length; row++) {
			for (int column = 0; column < matrix[row].length; column++) {
				matrix[row][column] = sc.nextInt();
			}
		}
		
		while(command != 'Q') {
			command = sc.next().charAt(0);
			switch(command) {
			case 'T':
				Transpose(matrix, m, n);
				break;
			case 'R':
				RowMultiply(matrix);
				break;
			case 'C':
				ColumnMin(matrix, m, n);
				break;
			}
		}
		sc.close();
	}
	
	public static void Transpose(int [][] matrix, int m, int n) {

		for (int column = 0; column < n; column++) {
			for (int row = 0; row < m; row++) {
				if(row == m-1) {
					System.out.printf("%d",matrix[row][column]);
				}
				else {
					System.out.printf("%d ",matrix[row][column]);
				}
			}
			
			System.out.println();
		}
		
	}
	
	public static void RowMultiply(int [][] matrix) {
		int result = 0;
		for(int row = 0; row < matrix.length; row++) {
			result = 1;
			for(int column = 0; column < matrix[row].length; column++) {
				result *= matrix[row][column];
			}
			if(row == matrix.length-1) {
				System.out.printf("%d",result);
			}
			else {
				System.out.printf("%d ",result);
			}
		}
		System.out.println();
	}
	
	public static void ColumnMin(int [][] matrix, int m, int n) {
		
		int minimum;
		for(int column = 0; column < n; column++) {
			minimum = matrix[0][column];
			for(int row = 0; row < m; row++) {
				if(matrix[row][column] < minimum) {
					minimum = matrix[row][column];
				}
			}
			if(column == n-1) {
				System.out.printf("%d", minimum);
			}
			else {
				System.out.printf("%d ", minimum);
			}
		}
		System.out.println();
	}

}
