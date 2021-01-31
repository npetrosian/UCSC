public class practice1question1 {

public static void main (String[] args) {

   for (int i = 1; i <= 5; i++) {

      switch (i) {
         case 1:
         case 2:
              System.out.println("Two");
              break;
         case 4:
              System.out.println("Four");
         case 5:
              System.out.println("Five");
         default:
              System.out.println("default");
       }
   	}
 }
}