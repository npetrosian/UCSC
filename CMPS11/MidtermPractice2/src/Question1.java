public class Question1 {

	private static class IntListElement {
		IntListElement next;
		int data;
		IntListElement (int value, IntListElement e) {
			data = value;
			next = e;
		}
	}
	
	public static void main(String[] args) {
		
		IntListElement e2 = new IntListElement(2019, null);
		IntListElement e1 = new IntListElement(2018, e2);
		IntListElement current = e1;
		
		while (current != null) {
			System.out.println(current.data);
			current = current.next;
		}
	}

}

