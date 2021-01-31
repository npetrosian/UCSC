import java.awt.FlowLayout;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class TestFieldExample {

	public static void main(String[] args) {
		//Scanner sc = new Scanner(System.in);
		//String output = sc.nextLine();
		JFrame frame = new JFrame("Basic GUI");
		frame.setSize(500, 500);
		frame.setVisible(true);
		JLabel label1 = new JLabel("This is a label");
		JLabel label2 = new JLabel();
		label2.setText("Label 2");
		frame.add(label1);
		//frame.add(label2);
		FlowLayout layout = new FlowLayout();
		frame.setLayout(layout);
		
		JButton button = new JButton("button");
		frame.add(button);
		
		JTextField textfield = new JTextField();
		//textfield.setSize(300, 300);
		//textfield.setText(output);
		frame.add(textfield);
		textfield.setText("This is my textfield");
		//frame.setVisible(true);
		
		String[] options = {"red", "blue", "green"};
		JComboBox comboBox = new JComboBox(options);
		frame.add(comboBox);
		frame.setVisible(true);
		
		
	}
}
