
public class Clock {
	// Static fields can be defined as final
	static final int maxHour = 12;
	static final int maxMinute = 59;
	static final int maxSecond = 59;
	
	int hour, minute, second;
	
	Clock(int h, int m, int s){
		if(h < maxHour)
			this.hour = h;
		if(m < maxMinute)
			this.minute = m;
		if(s < maxSecond)
			this.second = s;
	}
	// Defining a method as final will keep subclasses
	// from overriding the method
	final void resetHour() {
		hour = 0;
	}
	// We can define arguments as final to keep them  
	// from any changes in the body of the method
	void setMinute(final int m) {
		this.minute = m;
		//m++;
	}
	public static void main(String[] args) {
		// Defining a local variable as final
		final int numOfClock = 2;
		for (int i = 0; i < numOfClock; i++) {
			new Clock(0, 0, i);
		}
	}
}
// If the Clock class was final we were not able to subclass it
class ChildClock extends Clock{

	ChildClock(int h, int m, int s) {
		super(h, m, s);
	}
	// This is not allowed because resetHour() is a final method
	/*
	void resetHour() {
	hour = 4;
	}*/
	
	}
	

