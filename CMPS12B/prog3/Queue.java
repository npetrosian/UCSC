// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// File name: Queue.java
// The purpose of this file is to implement the QueueInterface and 
// provide all the necessary methods for Queue operations

public class Queue implements QueueInterface {
	
	// fields
	Node front;
	int numItems;
	
	// class definition for the Nodes in the linked list Queue
	private class Node {
		Object item;
		Node next;
		
		public Node(Object newItem) {
			this.item = newItem;
			this.next = null;
		}
	}
	
	public Queue() {
		front = null;
		numItems = 0;
	}
	
	public boolean isEmpty() {
		if(numItems == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public int length() {
		return numItems;
	}
	
	public void enqueue(Object newItem) {
		if (front == null) {
			front = new Node(newItem);
		}
		else {
			Node curr = front;
			while(curr.next!=null) {
				curr = curr.next;
			}
			curr.next = new Node(newItem);
		}
		numItems++;
	}
	
	public Object dequeue() throws QueueEmptyException {
		// if the queue is empty, throw an exception
		if (front == null) {
			throw new QueueEmptyException("The queue is empty, no dequeing allowed!");
		}
		else {
			// save where front is pointing to for returning 
			Node returnNode = front;
			// set front to the next node - it's okay if it is null
			front = front.next;
			// reduce the number of items by 1
			numItems--;
			// return the item of the dequeued node
			return returnNode.item;
		}
	}

	public Object peek() throws QueueEmptyException {
		if (front == null) {
			throw new QueueEmptyException("The queue is empty, no peeking allowed!");
		}
		else {
			return front.item;
		}
	}
	
	public void dequeueAll() throws QueueEmptyException {
		if (front == null) {
			throw new QueueEmptyException("The queue is empty, no emptying allowed!");
		}
		else {
			front = null;
			numItems = 0;
		}
	}
	
	public String toString() {
		String str = "";
		Node curr = front;
		if(!isEmpty()) {
			while (curr != null) {
				str += curr.item.toString() + " ";
				// str += curr.item.toString();
				// if (curr.next != null) {
				// 	str += " ";
				// }
				curr = curr.next;
			}
		}
		return str;
	}

}
