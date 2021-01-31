// Name: Natalie Petrosian 
// CruzID: npetrosi
// File name: BinarySearchDeluxe.java
// Class: 12B


import java.util.*;

public class BinarySearchDeluxe{

	// Returns the index of the first key in a[] that equals the search key,
	// or -1 if no such key. 
	public static <Key> int firstIndexOf(Key[] a, Key key, Comparator<Key> comparator){
		if(a == null || key == null || comparator == null){
			throw new java.lang.NullPointerException(); 
		}
		for(int i = 0; i < a.length; i++){
			if(comparator.compare(key, a[i]) == 0){
				return i;
			}
		}
		return -1;
}

	// Returns the index of the last key in a[] that equals the search key, 
	// or -1 if no such key.
	public static <Key> int lastIndexOf(Key[] a, Key key, Comparator<Key> comparator){
		if(a == null || key == null || comparator == null){
			throw new java.lang.NullPointerException(); 
		}
		for(int i = a.length-1; i >= 0; i--){
			if(comparator.compare(key, a[i]) == 0){
				return i;
			}
		}
		return -1;

	}
	// unit testing
	public static void main(String[] args){
    	// Questions for Professor McDowell:
    	// 1. How do I call firstIndexOf() and lastIndexOf()? Answered myself
    	// 2. How do I increase the performance to reach log2N?
	    Term[] terms = {new Term("charlie", 3), new Term("natalie", 120), new Term("chas", 5), new Term("charlene", 10)};
	    Term searchTerm = new Term("chaster", 85);
	    // Note: The third parameter is actually a method in Term, which we are passing
	    // to firstIndexOf() so that when it calls compare() it will actually be using the
	    // comparison in byPrefixOrder() defined in Term.
	    int returnFirstIndex = firstIndexOf(terms, searchTerm, Term.byPrefixOrder(4));
	    int returnLastIndex = lastIndexOf(terms, searchTerm, Term.byPrefixOrder(4));
	    System.out.println(returnFirstIndex);
	    System.out.println(returnLastIndex);

	    
	}
}