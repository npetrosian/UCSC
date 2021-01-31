/*
 * This program is built on the Rocket Class and Lunar Lander program delivered by
 * professor Charles McDowell with the following features added:
 *
 * 1.  The Rocket has a limited fuel supply controlled by the private float fuelSupply added to the Rocket class
 * 2.  Once fuelSupply is used up thrust will not work anymore
 * 3.  Once fuelSupply has been used up, a private float named lifeSupport will start to decrement by 1 point 60 times a second until it's all used up
 * 4.  Once lifeSupport is all used up the program will print a message that life support has diminished and occupants are dead
 * 5.  A landscape drawing has been added with rough terrain and a flat horizontal landing area
 * 6.  Safe landing is detected while xVel and yVel are below a threshold and on the safe landing area
 * 7.  Crashes cause the rocket to look crumbled
 * 8.  Rocket maintains its shape when it lands safely
 * 9.  Messages are printed when the rocket lands, crashes or occupants are dead due to lack of life support 
 * 10. The private modifier was maintained on all original private data.
 * 11. Additional data were also created as private 
 * 12. Percentage Fuel left is displayed by a new Rocket method named displayFuelPercentage()
 */

 /*
  * Full Credit Grading requirements are met as follows:
  * See https://cmps005j-fall17-01.courses.soe.ucsc.edu/program6
  *
  * 1.  The Rocket has a limited fuel supply controlled by the private float fuelSupply added to the Rocket class
  * 2.  Crashes cause the rocket to look crumbled when horizontal velocity is higher than SAFE_LANDING_THRESHOLD while landing
  * 3.  Crashes cause the rocket to look crumbled when vertical velocity is higher than SAFE_LANDING_THRESHOLD while landing
  * 4.  Once lifeSupport is all used up the program will print a message that life support has diminished and occupants are dead
  * 5.  Landing surface and rough terrain are displayed by a subroutine named drawLandscape()
  * 6.  Percentage of fuel remaining is printed by a method named displayFuelPercentage() added to the Rocket class
  * 7.  Two additional methods checkRocketStatus() and displayFuelPercentage() were added to the Rocket class
  * 8.  Magic numbers were minimized by adding SAFE_LANDING_THRESHOLD, STARTING_FUEL_SUPPLY, STARTING_LIFE_SUPPORT fuelSupply and lifeSupport to the Rocket class
  * 9.  Block of comments was added to LunarLander and Rocket class
  * 10. None of the functions exceed 40 lines
  */
  
class Rocket {
  /**
   Initial location of the rocket.
   @param startX - horizontal location
   @param startY - vertical location
   */
  Rocket(int startX, int startY) {
    x = startX;
    y = startY;
  }

  /**
   Decrease the thrust by the specified amount where decreasing by 100 will
   immediately reduce thrust to zero.
   */
  void setThrust(int amount) {
    // calculate thrust only if rocket has not crashed or landed
    // otherwise set it to 0
    if (rocketCrashed == false && rocketLanded == false && fuelSupply > 0.0) {
      amount = constrain(amount, 0, 100);
      thrust = MAX_THRUST*amount/100;
      if (thrust < 0) thrust = 0;
    } else {
      thrust = 0;
    }
  }

  /**
   Rotate the rocket positive means right or clockwise, negative means
   left or counter clockwise.
   */
  void rotateRocket(int amt) {
    tilt = tilt + amt*TILT_INC;
  }

  /**
   Adjust the position and velocity, and draw the rocket.
   */
  void update() {
    if (rocketCrashed == false && rocketLanded == false) {
      x = x + xVel;
      y = y + yVel;
      xVel = xVel - cos(tilt)*thrust;
      yVel = yVel - sin(tilt)*thrust + GRAVITY;
      if (abs(xVel) < 0.00005) xVel = 0;
      if (abs(yVel) < 0.00005) yVel = 0;
      fuelSupply = fuelSupply-(thrust*1000);
      if (fuelSupply < 0.0) {
        lifeSupport--;
        // println(lifeSupport);
        if (lifeSupport < 0.0) {
          println("life suport has been used up. Occupants are dead");
        }
      }
    }
    // draw it
    pushMatrix();
    translate(x, y);
    rotate(tilt - HALF_PI); 
    // Draw the rocket and thrust line if rocket has not crashed and has not landed
    if (rocketCrashed == false && rocketLanded == false) {
      // draw the rocket body
      triangle(0, -30, 5, 0, -5, 0); // bad magic numbers here for the simple rocket body
      // draw the rocket thrust "flames" in RED
      stroke(255, 0, 0);
      line(0, 0, 0, thrust * FLAME_SCALE);
      // set stroke back to black
      stroke(0);
    } else if (rocketCrashed) { // Draw a crumbled rocket if it has crashed
      triangle(-25, -30, -15, -15, -5, -15); 
      triangle(-15, -15, -5, -13, -15, -3); 
      triangle(-17, 0, -7, -10, -1, 3); 
      triangle(-17, 0, -19, 2, -5, 5);
    } else if (rocketLanded) { // Just draw the rocket if it has landed
      triangle(0, -30, 5, 0, -5, 0);
    }
    popMatrix();
    checkRocketStatus();
  }
  
  // This method checks for conditions to see if we have safely landed OR crashed OR are we out of fuel supply
  // it then sets the proper boolean values and prints the status
  void checkRocketStatus() {
    if (x >= 360 && x <=450 && y >= 556 && y <= 560 && xVel < SAFE_LANDING_THRESHOLD && yVel < SAFE_LANDING_THRESHOLD) { // Safe landing is only allowed on the smooth surface while xVel and yVel are at or below SAFE_LANDING_THRESHOLD
      println("Rocket Landed");
      rocketLanded = true;
    } else if (y > 564) {  // otherwise if we detect landing too fast we call it a crash
      println("Rocket Crashed");
      rocketCrashed = true;
    // check to see if there's enough fuel left
    } else if (fuelSupply <= 0.0) {
      println("Fuel Supply has been used up!");
    }
  }
 
  // This method prints the percentage of fuel left
  void displayFuelPercentage() {
    if (fuelSupply > 0.0) {
         println("Percentage Fuel Supply Left: " + (int) fuelSupply/STARTING_FUEL_SUPPLY*100 + "%");
    }
    else {
         println("Percentage Fuel Supply Left: 0%");
    }
  }
  
  private float x, y, xVel, yVel, thrust = GRAVITY, tilt = HALF_PI;
  private boolean rocketCrashed = false;  // boolean to detects crashed state
  private boolean rocketLanded = false;   // boolean to detect safe landing
  private float fuelSupply = STARTING_FUEL_SUPPLY; // float to control fuel supply requirement
  private float lifeSupport = STARTING_LIFE_SUPPORT;     // float to control life support requirement

  // the values below were arrived at by trial and error
  // for something that had the responsiveness desired
  static final float GRAVITY = 0.001;
  static final float MAX_THRUST = 5*GRAVITY;
  static final float TILT_INC = 0.005;
  static final int FLAME_SCALE = 5000; // multiplier to determine how long the flame should be based on thrust
  static final float SAFE_LANDING_THRESHOLD = 0.2; // xVel and yVel safe landing threshold
  static final float STARTING_FUEL_SUPPLY = 2000.0;
  static final float STARTING_LIFE_SUPPORT = 500.0;
}