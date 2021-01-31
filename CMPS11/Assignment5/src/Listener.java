import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class Listener extends JFrame{
	
	JLabel F1Label;
	JLabel F2Label;
	JTextField F1Text;
	JTextField F2Text;
	JButton reverse;
	JButton quit;
	
	Listener(){
		this.setSize(400, 200);
		F1Label = new JLabel("F1");
		F2Label = new JLabel("F2");
		F1Text = new JTextField("");
		F2Text = new JTextField("");
		reverse = new JButton("Reverse");
		quit = new JButton("Quit");
		
		this.setLayout(null);

		F1Label.setBounds(100,20,20,20);
		this.add(F1Label);
				
		F2Label.setBounds(300,20, 20, 20);
		this.add(F2Label);
		
		F1Text.setBounds(60,40,100,20);
		this.add(F1Text);
		
		F2Text.setBounds(260,40,100,20);
		this.add(F2Text);
		
		reverse.setBounds(140,100,150,20);
		this.add(reverse);
		
		quit.setBounds(350,150,40,20);
		this.add(quit);
		
		
		
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		reverse.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String text1 = F1Text.getText();
				String text1Reverse = "";
				for(int i = text1.length()-1; i >= 0; i--) {
					text1Reverse = text1Reverse + text1.charAt(i);
				}
				//System.out.println(text1Reverse);
				F2Text.setText(text1Reverse);
				
			}
			
		});
		
		F1Text.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String text1 = F1Text.getText();
				String text1Reverse = "";
				for(int i = text1.length()-1; i >= 0; i--) {
					text1Reverse = text1Reverse + text1.charAt(i);
				}
				//System.out.println(text1Reverse);
				F2Text.setText(text1Reverse);
				
			}
			
		});
		
		
		quit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				System.exit(0); // Googled this
			}
			
		});
			
	}

	public static void main(String[] args) {
		Listener frame = new Listener();

	}
}
