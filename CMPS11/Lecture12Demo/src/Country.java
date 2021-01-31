// An interface with two methods for getting the name and capital of country
interface Country {
	String getName();
	String getCapital();
}

// A sub-type of Country that adds getAverageIncome functionality  
interface DevelopingCountry extends Country{
	int getAvergaeIncome();
}

//A sub-type of Country that adds getLifeExpectancy functionality  
interface DevelopedCountry extends Country{
	int getLifeExpectancy();
}

/* A concrete class of type DevelopedCountry.
 * It is a sub-type of ConcreteCountry class and implements DevelopedCountry interface.
 * Needs to implement only getLifeExpectancy() as it inherits implementation of 
 * getName() and getCapital() methods from the parent
 */
class ConcreteDevelopedCountry extends ConcreteCountry implements DevelopedCountry{
	int lifeExp = 0;
	ConcreteDevelopedCountry(String name, String capital, int lifeExp){
		super(name, capital);
		this.lifeExp = lifeExp;
	}
	public int getLifeExpectancy() {
		return lifeExp;
	}
}

/* A concrete class of type DevelopingCountry.
 * It is a sub-type of ConcreteCountry class and implements DevelopingCountry interface.
 * Needs to implement only getAverageIncome() as it inherits implementation of 
 * getName() and getCapital() methods from the parent
 */

class ConcreteDevelopingCountry extends ConcreteCountry implements DevelopingCountry{
	int average = 0;
	ConcreteDevelopingCountry(String name, String capital, int average){
		super(name, capital);
		this.average = average;
	}
	
	public int getAvergaeIncome() {
		return average;
	}
	
}
/* A concrete class of type Country and implements Country interface.
 * Needs to implement both of methods in the interface to be a concrete class. 
 */

class ConcreteCountry implements Country{
	String name;
	String capital;
	ConcreteCountry(String name, String capital){
		this.name = name;
		this.capital = capital;
	}
	
	public String getName() {
		return name;
	}
	public String getCapital() {
		return capital;
	}
	public static void main(String[] args) {
		// Creating two objects of types ConcreteDevelopedCountry and ConcreteDevelopingCountry
		// Remember that we cannot instantiate from an interface or an abstract class.
		ConcreteDevelopedCountry c1 = new ConcreteDevelopedCountry("Canada", "Ottawa", 90);
		ConcreteDevelopingCountry c2 = new ConcreteDevelopingCountry("Russia", "Moscow", 10000);
		
		//Printing common properties of a ConcreteCountry object
		System.out.println(c1.getName() + " " + c1.getCapital());
		System.out.println(c2.getName() + " " + c2.getCapital());
		
		//Checking if c1 is an instance of ConcreteDevelopedCountry.
		System.out.println(c1 instanceof ConcreteDevelopedCountry);
		//Checking if c1 is an instance of ConcreteCountry.
		System.out.println(c1 instanceof ConcreteCountry);
		//Checking if c1 is an instance of DevelopedCountry.
		System.out.println(c1 instanceof DevelopedCountry);
		//Checking if c1 is an instance of ConcreteCountry.
		System.out.println(c1 instanceof Country);

	}
}


