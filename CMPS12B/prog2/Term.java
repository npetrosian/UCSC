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

  
  
  public static Comparator<Term> byPrefixOrder(int r) {
        return new Comparator<Term>(){
            public int compare(Term t1, Term t2) {
                // We have to base substringing on the minimum length
                // otherwise we will generate an out of bounds exception
                int min;
                if (t1.query.length() < t2.query.length()) {
                  min = t1.query.length();
                } else {
                  min = t2.query.length();
                }

                if (min >= r) {
                    return t1.query.substring(0, r).compareTo(t2.query.substring(0, r));
                } 
                // If they match when compared at the shortest string's length then ...
                else if (t1.query.substring(0, min).compareTo(t2.query.substring(0, min))==0)   {
                  // if the short string is from the wiktionary
                  if (t1.query.length() == min) {
                          return -1;
                  } else {  // otherwise if our prefix was the short strung
                          return 1;
                  }
                }
                // if we're still here just compare at the shortest substring length
                return t1.query.substring(0, min).compareTo(t2.query.substring(0, min));
                
            } 
        };
        
    }
    
    

    // Compares the two terms in lexicographic order by query.
  public int compareTo(Term that) {
    //System.out.println(this.query +  " compareTo " + that.query);
    return this.query.compareTo(that.query);
  }

  // Returns a string representation of this term in the following format:
  // the weight, followed by a tab, followed by the query.
  public String toString() {
    return weight + "\t" + query;
  }

  // unit testing (required)
  /*public static void main(String[] args)  {
    Term[] terms = {new Term("charlie", 3), new Term("chas", 5), new Term("charlene", 10)};
    System.out.println(Arrays.toString(terms));
    Arrays.sort(terms);
    System.out.println(Arrays.toString(terms));
    Arrays.sort(terms, Term.byReverseWeightOrder());
    System.out.println(Arrays.toString(terms));
    System.out.println(Term.byPrefixOrder(3).compare(terms[0], terms[1]));   
  }*/
}
