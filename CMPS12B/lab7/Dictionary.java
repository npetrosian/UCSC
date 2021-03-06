// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// File name: Dictionary.java
//
// Description: This file implements a Dictionary ADT using 
// a Binary Search Tree. It is a translation from a C
// program that was provided in the rubric. 

public class Dictionary implements DictionaryInterface {
	
	private class Node {
		String key;
		String value;
		Node left;
		Node right;
		
		public Node(String key, String value) {
			left = null;
			right = null;
			this.key = key;
			this.value = value;
		}
	}
	
	// fields
	private Node root;
	private int numPairs;
	
	// private methods
	
	private Node findKey(Node R, String key) {
		if(R == null || key.compareTo(R.key) == 0) {
			return R;
		}
		if(key.compareTo(R.key) < 0) {
			return findKey(R.left, key);
		}
		else {
			return findKey(R.right, key);
		}
	}
	
	private Node findParent(Node N, Node R) {
		Node P = null;
		if(N!=R) {
			P = R;
			while(P.left != N && P.right != N) {
				if(N.key.compareTo(P.key) < 0) {
					P = P.left;
				}
				else {
					P = P.right;
				}
			}
		}
		return P;
	}
	
	private Node findLeftmost(Node R) {
		Node L = R;
		if(L != null) {
			for(; L.left != null; L = L.left);
		}
		return L;

	}
	
	private void printInOrder(Node R) {
		if(R != null) {
			printInOrder(R.left);
			System.out.println(R.key + " " + R.value);
			printInOrder(R.right);
		}
	}
	
	private void deleteAll(Node N) {
		if(N != null) {
			deleteAll(N.left);
			deleteAll(N.right);
		}
	}
	
	// end of private methods
	
	public Dictionary() {
		root = null;
		numPairs = 0;
	}
	
	public boolean isEmpty() {
		return (this.numPairs == 0);
	}
	
	public int size() {
		return (this.numPairs);
	}
	
	public String lookup(String key) {
		Node N;
		N = findKey(this.root, key);
		if(N == null) {
			return null;
		}
		else {
			return (N.value);
		}
	}
	
	public void insert(String key, String value) throws DuplicateKeyException{
		Node N;
		Node A;
		Node B;
		if(findKey(this.root, key)!=null) {
			throw new DuplicateKeyException("Dictionary Error: cannot insert() duplicate key: " + key + "\n");
		}
		N = new Node(key, value);
		B = null;
		A = this.root;
		while(A!=null) {
			B = A;
			if(key.compareTo(A.key) < 0) {
				A = A.left;
			}
			else {
				A = A.right;
			}
		}
		if(B == null) {
			this.root = N;
		}
		else if (key.compareTo(B.key) < 0){
			B.left = N;
		}
		else {
			B.right = N;
		}
		this.numPairs++;
	}
	
	public void delete(String key) throws KeyNotFoundException{
		Node N;
		Node P;
		Node S;
		N = findKey(this.root, key);
		if(N == null) {
			throw new KeyNotFoundException("Dictionary Error: cannot delete() non-existent key: " + key + "\n");
		}
		if(N.left == null && N.right == null) { // case 1 (no children)
			if(N == this.root) {
				this.root = null;
			}
			else {
				P = findParent(N, this.root);
				if(P.right == N) {
					P.right = null;
				}
				else {
					P.left = null;
				}
			}
		}
		else if(N.right == null) { // case 2 (left but no right child)
			if(N == this.root) {
				this.root = N.left;
			}
			else {
				P = findParent(N, this.root);
				if(P.right == N) {
					P.right = N.left;
				}
				else {
					P.left = N.left;
				}
			}
		}
		else if(N.left == null) { // case 3 (right but no left child)
			if(N == this.root) {
				this.root = N.right;
			}
			else {
				P = findParent(N, this.root);
				if(P.right == N) {
					P.right = N.right;
				}
				else {
					P.left = N.right;
				}
			}
		}
		else { // case 3: (two children: N.left != null && N.right!=null)
			S = findLeftmost(N.right);
			N.key = S.key;
			N.value = S.value;
			P = findParent(S,N);
			if(P.right == S) {
				P.right = S.right;
			}
			else {
				P.left = S.right;
			}
		}
		this.numPairs--;
		
	}
	
	 public void makeEmpty() {
		 deleteAll(this.root);
		 this.root = null;
		 this.numPairs = 0;
	 }
	 
	 public String toString() {
		 printInOrder(this.root);
		 return "";
	 }
}
