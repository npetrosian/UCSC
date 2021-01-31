
public class Rational {

	int numerator;
	int denominator;
	int sign = 1;
	
	
	
	public Rational(int numerator) {
		if(numerator < 0) {
			sign = -1;
		}
		this.numerator = Math.abs(numerator);
		this.denominator = 1;
	}
	
	public Rational(int numerator, int denominator) {
		if((numerator >= 0 && denominator < 0) || (numerator < 0 && denominator >= 0)) {
			sign = -1;
		this.numerator = Math.abs(numerator);
		this.denominator = Math.abs(denominator);
		}
	}
	
	public Rational add (Rational other) {
		int num = this.sign * this.numerator * other.denominator +
				other.sign * other.numerator * this.denominator;
		int den = this.denominator * other.denominator;
		
		return new Rational(num, den);
	}
	
	public Rational sub(Rational other) {
		int num = this.sign * this.numerator * other.denominator -
				other.sign * other.numerator * this.denominator;
		int den = this.denominator * other.denominator;
		
		return new Rational(num, den);
	}
	
	public Rational mult(Rational other) {
		
		return new Rational(this.numerator * other.numerator * this.sign * other.sign,
				this.denominator * other.denominator);
		
	}
	
	public Rational divide(Rational other) {
		return this.mult(other.invert());
	}
	
	public Rational opposite() {
		return this.mult(new Rational (-1));
	}
	
	public Rational invert() {
		return new Rational(this.sign * this.denominator, this.numerator);
	}
	
	public Rational power(int p) {
		int s = 1;
		if(p % 2 == 1 && this.sign == -1) {
			s = -1;
		}
		return new Rational((int)(s * Math.pow(this.numerator, p)), (int)Math.pow(this.denominator, p));
	}
	
	public Rational simplify() {
		int num = this.numerator;
		int de = this.denominator;
		for(int i = 2; i <= num && i <= de; i++) {
			while(num % i == 0 && de % i == 0) {
				num = num / i;
				de = de / i;
			}
		}
		return new Rational(this.sign * num, de);
	}
	
	public String toString() {
		String s = "";
		if(this.sign == -1) {
			s = s + "-";
		}
		return s + this.numerator + "/" + this.denominator;
	}

}
