import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class Calculator extends JFrame{
	
	JLabel output;
	JLabel F1Label;
	JLabel F2Label;
	JTextField F1Text;
	JTextField F2Text;
	JButton addition;
	JButton subtraction;
	JButton multiplication;
	JButton division;
	JButton F1Copy;
	JButton F2Copy;
	JButton quit;
	
	Calculator(){
		this.setSize(400, 400);
		output = new JLabel("0.0");
		F1Label = new JLabel("F1");
		F2Label = new JLabel("F2");
		F1Text = new JTextField("0.0");
		F2Text = new JTextField("0.0");
		addition = new JButton("+");
		subtraction = new JButton("-");
		multiplication = new JButton("*");
		division = new JButton("/");
		F1Copy = new JButton("Copy to F1");
		F2Copy = new JButton("Copy to F2");
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
		
		output.setBounds(200,100,100,20);
		this.add(output);
		
		addition.setBounds(100,150,20,20);
		this.add(addition);
		
		subtraction.setBounds(300,150,20,20);
		this.add(subtraction);
		
		multiplication.setBounds(100,200,20,20);
		this.add(multiplication);
		
		division.setBounds(300, 200, 20, 20);
		this.add(division);
		
		F1Copy.setBounds(140,260,150,20);
		this.add(F1Copy);
		
		F2Copy.setBounds(140,300,150,20);
		this.add(F2Copy);
		
		quit.setBounds(350,350,40,20);
		this.add(quit);
		
		
		
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		addition.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num1 = F1Text.getText();
				String num2 = F2Text.getText();
				
				if(validFields(num1, num2)) {
					double value1 = Double.parseDouble(num1);
					double value2 = Double.parseDouble(num2);
					double sum = value1 + value2;
					String str = String.valueOf(sum);
					output.setText(str);
				}
				
				
			}
			
		});
		
		subtraction.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num1 = F1Text.getText();
				String num2 = F2Text.getText();
				
				if(validFields(num1, num2)) {
					double value1 = Double.parseDouble(num1);
					double value2 = Double.parseDouble(num2);
					double difference = value1 - value2;
					String str = String.valueOf(difference);
					output.setText(str);
				}
			}
			
		});
		
		multiplication.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num1 = F1Text.getText();
				String num2 = F2Text.getText();
				
				if(validFields(num1, num2)) {
					double value1 = Double.parseDouble(num1);
					double value2 = Double.parseDouble(num2);
					double product = value1 * value2;
					String str = String.valueOf(product);
					output.setText(str);
				}
			
			}
			
		});
		
		division.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num1 = F1Text.getText();
				String num2 = F2Text.getText();
				
				if(validFields(num1, num2)) {
					double value1 = Double.parseDouble(num1);
					double value2 = Double.parseDouble(num2);
					double quotient = value1 / value2;
					String str = String.valueOf(quotient);
					output.setText(str);
				}
			}
			
		});
		
		F1Copy.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num = output.getText();
				double value = Double.parseDouble(num);
				String str = String.valueOf(value);
				F1Text.setText(str);
			}
			
		});
		
		F2Copy.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				String num = output.getText();
				double value = Double.parseDouble(num);
				String str = String.valueOf(value);
				F2Text.setText(str);
			}
			
		});
		
		quit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				System.exit(0);
			}
			
		});
			
	}
	
	private boolean validFields(String F1, String F2) {
		if(F1.length() == 0 || F2.length() == 0) {
			//System.out.println("ERROR, no empty fields!");
			JOptionPane.showMessageDialog(null, "No empty fields allowed!", "Error Message", JOptionPane.ERROR_MESSAGE);
			return false;
		}
		 
		return true;
		
	}
	
	public static void main(String[] args) {
		Calculator frame = new Calculator();	
		
	}
}