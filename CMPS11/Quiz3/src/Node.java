class Node {
	int item;
	Node next;
	Node(int x){
		item = x;
		next = null;
	}
	static int product(Node H) {
		if(H == null) {
			return 1;
		}
		else {
			return H.item * product(H.next);
		}
	}
	public static void main(String[] args) {
		Node H = new Node(9);
		H.next = new Node(7);
		H.next.next = new Node(5);
		System.out.println(product(H));
	}
}