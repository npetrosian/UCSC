import javax.swing.JFrame;

class EmptyFrame {
	/*
	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setSize(500, 500);
		frame.setTitle("My Personalized Frame");
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	*/
}

class myFrame extends JFrame{
	MyFrame(){
		super();
		this.setTitle("MyFrame Instance");
		this.setSize(400, 200);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		public static void main(String[] args) {
			JFrame myframe = new MyFrame();
		}

		
	}
}
