// File name: DictionaryTest.java
// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// Description: This tests the methods in Dictionary.java

public class DictionaryTest {
	
	public static void main(String[] args) {
		String v;
	      Dictionary A = new Dictionary();
	      A.insert("1","Rachel");
	      A.insert("2","Ross");
	      A.insert("3","Monica");
	      A.insert("4","Chandler");
	      A.insert("5","Joey");
	      A.insert("6","Phoebe");
	      A.insert("7","Janice");
	      System.out.println(A);

	      v = A.lookup("1");
	      System.out.println("key=1 "+(v==null?"not found":("value="+v)));
	      v = A.lookup("3");
	      System.out.println("key=3 "+(v==null?"not found":("value="+v)));
	      v = A.lookup("7");
	      System.out.println("key=7 "+(v==null?"not found":("value="+v)));
	      v = A.lookup("8");
	      System.out.println("key=8 "+(v==null?"not found":("value="+v)));
	      System.out.println();

	      // A.insert("2","f");  // causes DuplicateKeyException

	      A.delete("1");
	      A.delete("3");
	      A.delete("7");
	      System.out.println(A);

	      // A.delete("8");  // causes KeyNotFoundException

	      System.out.println(A.isEmpty());
	      System.out.println(A.size());
	      A.makeEmpty();
	      System.out.println(A.isEmpty());
	      System.out.println(A);
	}

}
