// Name: Natalie Petrosian 
// CruzID: npetrosi
// File name: AutoComplete.java
// Class: 12B


import java.io.File;
import java.io.FileNotFoundException;
import java.lang.*;
import java.util.Comparator;
import java.util.Scanner;
import java.util.Arrays;

public class Autocomplete {
	
  public Term[] queries;
  
  
  // Initializes the data structure from the given array of terms.
  public Autocomplete(Term[] terms) {
     // Returns all terms that start with
	 if(terms == null) {
		 throw new java.lang.NullPointerException();
	 }
	 this.queries = terms;
	 // arrray must be sorted or it won't work
	 Arrays.sort(this.queries);
  }
  
  // the given prefix, 
  // in descending order of weight. 
  public Term[] allMatches(String prefix) {
      if(prefix == null) {
    	     throw new java.lang.NullPointerException();
      }
      Term t = new Term(prefix, 0);
      int firstIndex = BinarySearchDeluxe.firstIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      int lastIndex = BinarySearchDeluxe.lastIndexOf(queries, t, Term.byPrefixOrder(prefix.length()));
      //System.out.println("firstIndex=" + firstIndex + " lastIndex=" + lastIndex);

      // matched is an array of Terms big enough to fit all matched terms
      Term[] matched = new Term[lastIndex - firstIndex + 1];

	  // Now we populate matched 
      if (firstIndex != -1  && lastIndex != -1) {
      	    int j = 0;
            for (int i = firstIndex; i <= lastIndex; i++) {
      	          matched[j] = queries[i];
      	          j++;
            }
      }
      
      // we have an array of matches but they 
      // need to be sorted to refelect the weight order
      Arrays.sort(matched, Term.byReverseWeightOrder());

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
      // int firstIndex = BinarySearchDeluxe.firstIndexOf(queries, t, Term.byReverseWeightOrder());
      // int lastIndex = BinarySearchDeluxe.lastIndexOf(queries, t, Term.byReverseWeightOrder());
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

	    // create an autocomplete class and initialize its array
	    Autocomplete autocomplete = new Autocomplete(terms);
	    while(sc2.hasNextLine()) {
	    	    String myQuery = sc2.nextLine();
	    	    Term[] output = autocomplete.allMatches(myQuery);
	    	    
	    	    // System.out.println(output[0]);
	    	    for(int i = 0; i < Math.min(maxMatch, autocomplete.numberOfMatches(myQuery)); i++){
	    	    	   System.out.println(output[i]);
	    	    }
	    	    
	    }
	    
	    
	    
	    sc.close();
	    sc2.close();
  }
}
