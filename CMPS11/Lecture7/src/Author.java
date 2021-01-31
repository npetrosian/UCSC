
public class Author {
	String name = "";
	String email = "";
	
	Author(String name, String email){
		this.name = name;
		this.email = email;
	}
	// default constructor
	Author(){
		this.name = "John";
		this.email = "john@ucsc.edu";
		// this("John", "john@ucsc.edu");
	}
	
	void setName(String name) {
		this.name = name;
	}
	
	void setEmail(String email) {
		if(email.contains("@") && email.contains(".")) {
			this.email = email;
		}
	}
	
	public String toString() {
		return "Name: " + this.name + " Email: " + this.email;
	}
	
	public static void main(String[] args) {
		Author a = new Author("Narges", "na@ucsc.edu");
		System.out.println(a.toString());
		
		Author b = new Author();
		System.out.println(b.toString());
		
		Author c = new Author();
		System.out.println(c.toString());

	}

}

class Book{
	String name;
	double price;
	Author author;
	// Author[] authors;
	
	Book(String name, double price, Author author){
		this.name = name;
		this.price = price;
		this.author = author;
	}
	Book(){
		this("Book Template", 0, new Author());
		// Author a = new Author();
		// this(("Book Template", 0, a);
	}
	
	void setAuthor(Author author) {
		if(author != null) {
			this.author = author;
		}
	}
}
