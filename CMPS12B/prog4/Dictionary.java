// File name: Dictionary.java
// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// Description: Implements a Dictionary ADT using 
// a linked list data structure. 

public class Dictionary implements DictionaryInterface {
	
	private class Node {
		String key;
		String value;
		Node next;
		
		public Node(String key, String value) {
			this.key = key;
			this.value = value;
			next = null;
		}
	}
	
	// fields
	private Node head;
	private int numOfNodes;
	
	// private methods
	
	private Node findKey(String key) {
		for(Node curr = head; curr != null; curr = curr.next) {
			if(curr.key.compareTo(key) == 0) {
				return curr;
			}
		}
		// if we didn't return earlier, then we didn't find a match. 
		return null; 
	}
	
	// end of private methods
	
	// constructor for Dictionary class
	public Dictionary() {
		head = null;
		numOfNodes = 0;
	}
	
	public boolean isEmpty() {
		return (this.numOfNodes == 0);
	}
	
	public int size() {
		return (this.numOfNodes);
	}
	
	public String lookup(String key) {
		Node N;
		N = findKey(key);
		if(N == null) {
			return null;
		}
		else {
			return (N.value);
		}
	}
	
	public void insert(String key, String value) throws DuplicateKeyException{
		Node N;
		Node curr;
		
		if(findKey(key)!=null) {
			throw new DuplicateKeyException("Dictionary Error: cannot insert() duplicate key: " + key + "\n");
		}
		
		N = new Node(key, value);
		
		if(head == null) {
			head = N;
			this.numOfNodes++;

			
		}
		else {
		
			for(curr = head; curr.next != null; curr = curr.next) {
				;
			}
			curr.next = N;
		
			this.numOfNodes++;
			
		}
	}
	
	public void delete(String key) throws KeyNotFoundException{
		Node N;
		Node curr = head;
		
		N = findKey(key);
		if(N == null) {
			throw new KeyNotFoundException("Dictionary Error: cannot delete() non-existent key: " + key + "\n");
		}
		if(curr.key.compareTo(key) == 0) {
			head = curr.next;
			this.numOfNodes--;
		}
		else {
			while(curr.next != null && curr.next.key.compareTo(key) != 0) {
				curr = curr.next;
			}
		
			// just in case the while loop terminated because curr.next was null
			if(curr.next != null) {
				curr.next = curr.next.next;
				this.numOfNodes--;
			}
		}		
		
	}
	
	 public void makeEmpty() {
		 this.head = null;
		 this.numOfNodes = 0;
	 }
	 
	 public String toString() {
		 for(Node curr = head; curr != null; curr = curr.next) {
			 System.out.println(curr.key + " " + curr.value);
		 }
		 return "";
	 }
}
