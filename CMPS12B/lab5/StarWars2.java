// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// The goal of this assignment is to learn the basics of inheritance
// and polymorphism. 

class StarWars2 {
    /*
     * Fight to the death between two ships.
     * On return one of the ships will be dead.
     * This method must NOT BE MODIFIED.
     */
    private void duel(SpaceShip x, SpaceShip t) {
        while(!x.isDead() && !t.isDead()) {
            x.hit(t.getWeapon());       
            if (x.isDead()) {
                System.out.println(x + " is dead");
            }
            else {
                t.hit(x.getWeapon());
                if (t.isDead()) {
                    System.out.println(t + " is dead");
                }
            }
        }
    }
    /*
     * @param i - the index at which to start searching for the next Tie fighter
     * @param fighters - an array containing both Tie and XWing fighters
     * @return the first Tie fighter in the array at or beyond index i. -1 if
     *         there are no Tie fighters in the range i to the end of the array
     */
    private int nextTie(int i, SpaceShip[] fighters) {
        assert(i >= 0);
        while (i < fighters.length) {
            if (fighters[i] instanceof Tie) {
                return i;
            }
            i++;
        }
        return -1;
    }
    /*
     * @param i - the index at which to start searching for the next XWing fighter
     * @param fighters - an array containing both Tie and XWing fighters
     * @return the first XWing fighter in the array at or beyond index i. -1 if
     *         there are no XWing fighters in the range i to the end of the array
     */
    private int nextXWing(int i, SpaceShip[] fighters) {
        while (i < fighters.length) {
            if (fighters[i] instanceof XWing) {
                return i;
            }
            i++;
        }
        return -1;
    }
    /*
     * Simulate the battle between the XWing and Tie fighters in the given array.
     * @param the array of fighters, in no particular order.
     * The battle should proceed as it does in the StarWars class provided in the
     * reading. Specifically the first XWing in the array will battle the first Tie.
     * The winner of that will battle the next spaceship of the opposing type in the 
     * array, and so on.
     */
    void battle(SpaceShip[] fighters) {
	// to be completed
      int g = nextXWing(0,fighters);
      int e = nextTie(0,fighters);
      int goodDeaths = 0;
      int evilDeaths = 0;
      int totalEvil = 0;
      int totalGood = 0;

      for(int i = 0; i < fighters.length; i++){
           if(fighters[i] instanceof Tie){
               totalEvil++;
           }
           if(fighters[i] instanceof XWing){
               totalGood++;
           }
      }
     
      while (g != -1 && e != -1) {
         System.out.println("battling X-Wing #" + goodDeaths + " versus Tie Fighter #" + evilDeaths);
         duel(fighters[g],fighters[e]);
         if (fighters[g].isDead()) {
            g++;
            goodDeaths++;
         }
         if (fighters[e].isDead()) {
            e++;
            evilDeaths++;
         }
         g = nextXWing(g,fighters);
         e = nextTie(e, fighters);
      }
      
      int finalGood = totalGood - goodDeaths;
      int finalEvil = totalEvil - evilDeaths;

      System.out.println();
      System.out.println("Battle Report:\t\tX-Wings\t\tTie Fighters");
      System.out.println("------------------------------------------------------");
      System.out.println();
      System.out.println("Initial ships:\t\t" + totalGood + "\t\t" + totalEvil);
      System.out.println();
      System.out.println("Killed ships:\t\t"  + goodDeaths  + "\t\t" + evilDeaths);
      System.out.println();
      System.out.println("Final ships:\t\t"   + finalGood   + "\t\t" + finalEvil);
      System.out.println();
      if (finalGood > finalEvil) {
         System.out.println("The rebel alliance is victorious!");
      }
      else {
         System.out.println("The dark side has conquered!");
      }
      System.out.println();
    }

    /*public void doStuff() {
    
      // defines the fighters array
      SpaceShip[] fighters = new SpaceShip[6];

      // initializes the elements of the goodies array
      for (int i=0; i<3; i++) {
         fighters[i] = new XWing();
      }

      // initialises the elements of the baddies array
      for (int i=3; i<6; i++) {
         fighters[i] = new Tie();
      }
    
      battle(fighters);

   }  

   // The main method is the point of entry into the program...
   public static void main(String[] args) {
      StarWars me = new StarWars();
      me.doStuff();
   }
   */
}
