/*
 * This example shows how to use anonymous inner classes. Usually when you
 * need to subclass a class or implement an interface for one-time use you might need to use
 * anonymous classes. You create an object of type parent and you implement or override methods that you need. 
 */
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class SalaryCalculator6 extends JFrame{
	JLabel salaryLabel;
	JTextField salaryField;
	JTextField wageField;
	JButton button;
	JButton centerButton;
	SalaryCalculator6(){
		this.setSize(400, 400);
		this.getContentPane().setBackground(Color.pink);
		salaryLabel = new JLabel("0");
		salaryField = new JTextField("0");
		wageField = new JTextField("0");
		button = new JButton("Calculate");
		centerButton = new JButton("Raised Salary");
		//Adding anonymous class that implements ActionListener and an object of that will be attached to
		//the button for calculating the salary
		button.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String wage = wageField.getText();
				int value = Integer.parseInt(wage);
				int salary = value * 40 * 50;
				String str = String.valueOf(salary);
				salaryLabel.setText(str);
				salaryField.setText(str);
			}
			
		});
		//Similar as before, this time we give a raise in the wage and we calculate the salary accordingly
		centerButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String wage = wageField.getText();
				int value = Integer.parseInt(wage);
				int salary = (value + 5) * 40 * 50;
				String str = String.valueOf(salary);
				salaryLabel.setText(str);
				salaryField.setText(str);
			}
			
		});
		
		BorderLayout layout = new BorderLayout();
		this.setLayout(layout);
		
		this.add(wageField, BorderLayout.NORTH);
		this.add(salaryField, BorderLayout.WEST);
		this.add(salaryLabel, BorderLayout.EAST);
		this.add(button,  BorderLayout.SOUTH);
		this.add(centerButton, BorderLayout.CENTER);
		
		this.salaryField.setEditable(true);
		//Adding action listener to text field in the same way.
		salaryField.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String salary = salaryField.getText();
				salaryLabel.setText(salary);
			}
			
		});
		
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void main(String[] args) {
		SalaryCalculator6 frame = new SalaryCalculator6();	
	}
}
