interface Junk {
	int a = 5;
	int f();
}
public class TestClass implements Junk{
	public static void main(String[] args) {
		System.out.println(a);
	}
}