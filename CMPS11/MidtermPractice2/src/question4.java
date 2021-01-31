

public class question4 {

public static void main (String[] args) {
    printMultiples();
}

public static void printMultiples() {

    for (int i=1; i <= 160; i++) {
       if (i % 4 == 0) {
           System.out.println(i);
       }
    }
}

}
