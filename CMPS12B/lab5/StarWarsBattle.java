// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// The goal of this assignment is to learn the basics of inheritance
// and polymorphism. 

// You are to use and submit this file unmodified with your submission.
public class StarWarsBattle {

    // The main method is the point of entry into the program...
    public static void main(String[] args) {
        StarWars2 galaxy = new StarWars2();
        SpaceShip[] fighters = new SpaceShip[6];
        // initializes the elements of the fighters array
        for (int i=0; i<fighters.length; i++) {
            if (i%2 == 0) {
                fighters[i] = new XWing();
            }
            else {
                fighters[i] = new Tie();
            }
        }
        galaxy.battle(fighters);

	// try a different arrangment - should produce the same output
        for (int i=0; i<fighters.length; i++) {
            if (i < fighters.length/2) {
                fighters[i] = new XWing();
            }
            else {
                fighters[i] = new Tie();
            }
        }
        galaxy.battle(fighters);
    }

}