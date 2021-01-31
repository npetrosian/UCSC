
public class BankAccount {
	
	int accountNumber;
	int balance;
	
	BankAccount(int accountNumber){
		this.accountNumber = accountNumber;
		this.balance = 0;
	}

	void deposit(int amount) {
		this.balance += amount;
	}
	
	boolean withdraw(int amount) {
		if(this.balance >= amount) {
			this.balance -= amount;
			return true;
		}
		else {
			System.out.println("Transaction failed");
			return false;
		}
		
	}
	
	void transfer(int amount, BankAccount dest) {
		boolean success = this.withdraw(amount);
		if (success == true)
			dest.deposit(amount);
	}
	
	public static void main(String[] args) {
		BankAccount b1 = new BankAccount(1);
		BankAccount b2 = new BankAccount(2);
		System.out.println(b1.balance+" "+b2.balance);
		
		b1.deposit(100);
		b2.deposit(50);
		
		b1.transfer(70,b2);
		System.out.println(b1.balance+" "+b2.balance);
		
		

	}

}
