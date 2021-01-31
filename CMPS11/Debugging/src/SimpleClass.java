public class SimpleClass {
	int num1;
	String string1;
	
	public SimpleClass(int n, String s) {
		num1 = n;
		string1 = s;
	}
	
	public void A() {
		string1 = "A";
	}
	
	public void B() {
		string1 = "B";
	}
	
	public void C(String s) {
		string1 = s;
	}
	
	public void callsC(String s) {
		String getsPassedToC = s;
		C(getsPassedToC);
	}
	
	public static void main(String[] args) {
		SimpleClass sc = new SimpleClass(1, "CMPS11");
		
		sc.A();
	}
}

