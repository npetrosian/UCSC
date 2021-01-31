// Name: Natalie Petrosian 
// CruzID: npetrosi
// File name: Term.java
// Class: 12B
// The starting point for the code here is Term.java, provided by Professor McDowell. 
// The constructor was provided except for the exception throwing. The 
// byReverseWeightOrder and main methods were also provided. 

import java.util.*;

public class Term implements Comparable<Term> {
  private String query;
  private long weight;
  
  // Initializes a term with the given query string and weight.
  public Term(String query, long weight) {
    this.query = query;
    this.weight = weight;
    if(query == null){
    		throw new java.lang.NullPointerException();
    }
    if(weight < 0){
    		throw new java.lang.IllegalArgumentException();
    }
  }

  // Compares the two terms in descending order by weight.
  public static Comparator<Term> byReverseWeightOrder() {
    return new Comparator<Term>() {
      public int compare(Term t1, Term t2) {
        return (int)(t2.weight - t1.weight);
      }
    };
  }

  // Compares the two terms in lexicographic order but using only the first r characters of each query.
  public static Comparator<Term> byPrefixOrder(int r) {
  	if(r < 0){
  		throw new java.lang.IllegalArgumentException();
    }
    return new Comparator<Term>() {
      public int compare(Term t1, Term t2) {
        return (int)(t1.query.substring(0,r).compareTo(t2.query.substring(0,r)));
      }
    };
  }

    // Compares the two terms in lexicographic order by query.
  public int compareTo(Term that) {
    return this.query.compareTo(that.query);
  }

  // Returns a string representation of this term in the following format:
  // the weight, followed by a tab, followed by the query.
  public String toString() {
    return weight + "\t" + query;
  }

  // unit testing (required)
  public static void main(String[] args)  {
    Term[] terms = {new Term("charlie", 3), new Term("chas", 5), new Term("charlene", 10)};
    System.out.println(Arrays.toString(terms));
    Arrays.sort(terms);
    System.out.println(Arrays.toString(terms));
    Arrays.sort(terms, Term.byReverseWeightOrder());
    System.out.println(Arrays.toString(terms));
    System.out.println(Term.byPrefixOrder(3).compare(terms[0], terms[1]));   
  }
}