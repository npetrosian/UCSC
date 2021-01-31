// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// The goal of this assignment is to learn the basics of inheritance
// and polymorphism. 

abstract class SpaceShip{
	// Properties of the class...
   protected int     shields;
   protected int     weapon;
   protected boolean dead;

   // Methods of the class...
   public int getWeapon() {
      return weapon;
   }
   public boolean isDead() {
      return dead;
   }
   public void hit(int damage) {
      shields = shields - damage;
      if (shields < 0) {
         System.out.println("BOOM!!!");
         dead = true;
      }
   }
   public String toString() {
      return ("Spaceship");
   }
}