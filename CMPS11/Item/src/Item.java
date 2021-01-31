public class Item {
	String name;
	int id;
	// Counts the number of Item instances we created
	// Inline initialization of static fields
	static int count = 0;
	// Stores all instances of Item in an array
	static Item[] objects;
	// Static block. It will be called only once 
	// to initialize static fields
	static {
		objects = new Item[0];
	}
	
	Item(String name){
		count++;
		// Increasing the size of the array
		// to store the latest instance we created just now
		Item[] newObjects = new Item[count];
		// Copying all existing instances in a new array
		for(int i = 0; i < objects.length; i++) {
			newObjects[i] = objects[i];
		}
		// Storing current instance in the last index of array
		newObjects[count - 1] = this;
		// Updated array of Item objects is newObjects
		objects = newObjects;
		// Setting all object fields now
		this.name = name;
		id = count;
	}
	// Static method since it deals with static fields only
	static void removeLastItem() {
		// We assume that we are not interested in storing last object
		// Decreasing the count by 1
		count--;
		// Removing last object from the array an updating the array
		Item[] newObjects = new Item[count];
		for(int i = 0; i < count; i++) {
			newObjects[i] = objects[i];
		}
		objects = newObjects;
	}
	
	public static void main(String[] args) {
		Item item1 = new Item("First");
		Item item2 = new Item("Second");
		Item item3 = new Item("Third");
		new Item("Extra");
		
		// Instead of storing all object in an array as a local variable, 
		// We can use the static field in the Item class that holds all instances
		for(int i = 0; i < Item.objects.length; i++)
			System.out.println(Item.objects[i].name + " " + Item.objects[i].id);
		
		// Accessing a static field using the name of the class
		System.out.println(Item.count);
		
		// Calling a static method using the name of the class
		Item.removeLastItem();
		
		for(int i = 0; i < Item.objects.length; i++)
			System.out.println(Item.objects[i].name + " " + Item.objects[i].id);
		
	}

}

