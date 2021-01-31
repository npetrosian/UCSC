import java.io.File;
import java.io.FileNotFoundException;
import java.lang.*;
import java.util.Comparator;
import java.util.Scanner;
import java.util.Arrays;

public class AutoComplete {
	
  public Term[] queries;
  
  
  // Initializes the data structure from the given array of terms.
  public AutoComplete(Term[] terms) {
     // Returns all terms that start with
	 if(terms == null) {
		 throw new java.lang.NullPointerException();
	 }
	 this.queries = queries;
	 Arrays.sort(queries);
  }
  
  //the given prefix, 
  // in descending order of weight.
  public Term[] allMatches(String prefix) {
      if(prefix == null) {
    	     throw new java.lang.NullPointerException();
      }
      Term t = new Term(prefix, 0);
      int firstIndex = BinarySearchDeluxe.firstIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      int lastIndex = BinarySearchDeluxe.lastIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      Term[] matched = new Term[lastIndex - firstIndex + 1];
      matched = Arrays.copyOfRange(queries, firstIndex, lastIndex);
      return matched;
  }
  // Returns the number of terms that start with the given prefix.
  public int numberOfMatches(String prefix) {
	  if (prefix == null) {
  		throw new java.lang.NullPointerException();
  	  }
	  Term t = new Term(prefix, 0);
      int firstIndex = BinarySearchDeluxe.firstIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      int lastIndex = BinarySearchDeluxe.lastIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      return lastIndex - firstIndex + 1;
	  
  }
  // unit testing (required)
  public static void main(String[] args) throws FileNotFoundException   {
	    File file = new File(args[0]);
	    int maxMatch = Integer.parseInt(args[1]);
	    Scanner sc = new Scanner(file);
	    Scanner sc2 = new Scanner(System.in);
	    int N = sc.nextInt(); 
	    Term[] terms = new Term[N];
	    long weight;
	    String query;
	    for(int i = 0; i < N; i++) {
	        weight = sc.nextLong();
	        query  = sc.next();
	        //System.out.println(weight + " " + query);
	        terms[i] = new Term(query, weight);
	    }
	    AutoComplete autocomplete = new AutoComplete(terms);
	    while(sc2.hasNextLine()) {
	    	    String myQuery = sc2.nextLine();
	    	    Term[] output = autocomplete.allMatches(myQuery);
	    	    for(int i = 0; i < Math.min(maxMatch, autocomplete.numberOfMatches(myQuery)); i++){
	    	    	   System.out.println(output[i]);
	    	    }
	    }
	    
	    
	    
	    sc.close();
	    sc2.close();
  }
}
