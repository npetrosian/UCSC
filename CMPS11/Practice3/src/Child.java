public class Child extends Parent{
	public int a = 2;
	public void f(){System.out.println("child’s f(),a = "+ a);}
	public static void main(String []args){
		Parent p = new Child();
		p.a = 3;
		p.f();
	}
}
class Parent {
	public int a = 1;
	public void f(){System.out.println("parent’s f(),a = "+a);}
}
