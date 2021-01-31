public class PrivateOverride {
	
	private void f() { 
		System.out.println("private f()");
	} 
	// if "public" will print "public f()"
	
	public static void main(String[] args) {
		PrivateOverride po = new Derived();
		po.f();
	}
}
class Derived extends PrivateOverride {
	public void f() { 
		System.out.println("public f()"); 
	}
}
