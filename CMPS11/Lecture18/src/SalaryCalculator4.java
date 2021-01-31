import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class SalaryCalculator4 extends JFrame implements ActionListener{

	JLabel salaryLabel;
	JTextField salaryField;
	JTextField wageField;
	JButton button;
	SalaryCalculator4(){
		this.setSize(400,400);
		this.getContentPane().setBackground(Color.pink);
		this.setBackground(Color.PINK);
		salaryLabel = new JLabel("0");
		salaryField = new JTextField("0");
		wageField = new JTextField("0");
		button  = new JButton("Calculate");
		
		button.addActionListener(this);
		
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
		SalaryCalculator4 frame = new SalaryCalculator4();
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		String wage = wageField.getText();
		int value = Integer.parseInt(wage);
		int salary = value * 40 * 50;
		String str = String.valueOf(salary);
		salaryLabel.setText(str);
		salaryField.setText(str);
	}

}

