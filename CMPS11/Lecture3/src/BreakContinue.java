import java.util.Scanner;

public class BreakContinue {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		/*
		while(true) {
			int number = sc.nextInt();
			if(number == -1)
				break;
			else 
				System.out.println(number + 1);
		}
		*/
		for (int i = 1; ; i++) {
			if(i == 51)
				break;
			if(i%2 == 1)
				continue;
			else
				System.out.println(i/2);
		}
		

	}

}
