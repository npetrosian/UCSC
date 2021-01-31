// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// File name: QueueTest.java
// The purpose of this file is to test the methods in Queue.

public class QueueTest {
	
	public static void main(String[] args) {
		Queue friends = new Queue();
		String s1 = "Rachel";
		String s2 = "Ross";
		String s3 = "Chandler";
		String s4 = "Joey";
		String s5 = "Monica";
		String s6 = "Pheobe";
		
		friends.enqueue(s1);
		friends.enqueue(s2);
		friends.enqueue(s3);
		friends.enqueue(s4);
		friends.enqueue(s5);
		friends.enqueue(s6);
		
		System.out.println(friends.isEmpty());
		System.out.println(friends.length());
		System.out.println(friends);
		System.out.println(friends.dequeue());
		System.out.println(friends.length());
		System.out.println(friends.peek());
		System.out.println(friends);
		friends.dequeueAll();
		System.out.println(friends.length());






	}

}
