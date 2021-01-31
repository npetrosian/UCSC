import javax.swing.JFrame;

class MyFrame extends JFrame{
	MyFrame(){
		//super();
		this.setTitle("MyFrame Instance");
		this.setSize(400, 200);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void main(String[] args) {
		JFrame myframe = new MyFrame();
	}
}
