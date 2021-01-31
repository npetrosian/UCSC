// An abstract class since it has an abstarct method
public abstract class Vehicle {
	// General fields for a vehicle
	String licensePlate = null;
	int speed;
	
	void setLicensePlate(String plate) {
		this.licensePlate = plate;
	}
	// Abstract method for setting the maximum speed based on the type of vehicle
	abstract void setMaxSpeed(int speed);
}

class Car extends Vehicle{
	int numOfSeats = 0;
	// Field has the same name as the one in the parent.
	final static int speed = 100;
	
	// Implementation of the abstract method of the parent
	void setMaxSpeed(int speed) {
		if(speed < Car.speed) {
			super.speed = speed;
			//((Vehicle)(this)).speed = speed;
		}
	}
}

class Truck extends Vehicle{
	final static int maxSpeedTruck = 80;
	void setMaxSpeed(int speed) {
		if(speed < maxSpeedTruck) {
			this.speed = speed;
		}
	}
	
}

