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
  
  
// declare a rocket
Rocket rocket;

// setup gets called once and sets up the screen size and creates a new rocket
void setup() {
  size(600, 600);
  rocket = new Rocket(width/2, height/2);
}

// draw gets called continuesly by the Processing Gremlin 60 times a second
void draw() {
  background(0);
  drawLandscape();
  adjustControls(rocket);
  rocket.update();
  rocket.displayFuelPercentage();
}

// The following subroutine draws a rough lunar landscape and a smooth safe landing surface
// The rough surface is just a bunch of triangles whose values were tweaked by the Tweak
// function under Sketch
void drawLandscape() {
  noStroke();
  fill(127);
  rect(0, 560, width, 40);
  triangle(0, 560, 80, 556, 100, 560);
  triangle(100, 560, 180, 554, 200, 560);
  triangle(200, 560, 240, 553, 300, 560);
  triangle(300, 560, 321, 556, 360, 560);
  triangle(450, 560, 480, 554, 500, 560);
  triangle(500, 560, 540, 553, 600, 560);
  stroke(255);
  strokeWeight(4);
  line(360, 560, 450, 560);
  stroke(0);
  strokeWeight(1);
  fill(255);
}

/*
 Control the rocket using mouseY for thrust and 'a' or left-arrow for rotating
 counter-clockwise and 'd' or right-arrow for rotating clockwise.
 It takes a single parameter, which is the rocket being controlled.
 */

void adjustControls(Rocket rocket) {
  // control thrust with the y-position of the mouse
  if (mouseY < height/2) {
    rocket.setThrust(height/2 - mouseY);
  } else {
    rocket.setThrust(0);
  }
  
  // allow for right handed control with arrow keys or
  // left handed control with 'a' and 'd' keys

  // right hand rotate controls
  if (keyPressed) {
    if (key == CODED) { // tells us it was a "special" key
      if (keyCode == RIGHT) {
        rocket.rotateRocket(1);
      } else if (keyCode == LEFT) {
        rocket.rotateRocket(-1);
      }
    }
    // left hand rotate controls
    else if (key == 'a') {
      rocket.rotateRocket(-1);
    } else if (key == 'd') {
      rocket.rotateRocket(1);
    }
  }
}