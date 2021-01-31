import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class SalaryCalculator extends JFrame{
	JLabel salaryLabel;
	JTextField salaryField;
	JTextField wageField;
	JButton button;
	SalaryCalculator(){
		this.setSize(200,200);
		this.getContentPane().setBackground(Color.pink);
		this.setBackground(Color.PINK);
		salaryLabel = new JLabel("0");
		salaryField = new JTextField("0");
		wageField = new JTextField("0");
		button  = new JButton("Calculate");
		
		BorderLayout layout = new BorderLayout();
		this.setLayout(layout);
		
		this.add(wageField, BorderLayout.NORTH);
		this.add(salaryField, BorderLayout.WEST);
		this.add(salaryLabel, BorderLayout.EAST);
		this.add(button, BorderLayout.SOUTH);
		
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args) {
		SalaryCalculator frame = new SalaryCalculator();
	}

}
