
public class Node {
	int item;
	Node next; // pointer
	Node prev;
	
	public Node(int item){
		this.item = item;
		this.next = null;
		this.prev = null;
	}

	public static void main(String[] args) {
		Node n1 = new Node(20);
		Node n2 = new Node(45);
		Node n3 = new Node(51);
		Node n4 = new Node(76);
		Node n5 = new Node(84);
		Node head;
		Node tail;
		head = n1;
		n1.next = n2;
		n2.prev = n1;
		n2.next = n3;
		n3.prev = n2;
		n3.next = n4;
		n4.prev = n3;
		n4.next = n5;
		n5.prev = n4;
		tail = n5;
		
		for(Node curr = head; curr!= null; curr = curr.next) {
			System.out.println(curr.item);
		}
		System.out.println();
		for(Node curr = tail; curr!= null; curr = curr.prev) {
			System.out.println(curr.item);
		}
	}
}
