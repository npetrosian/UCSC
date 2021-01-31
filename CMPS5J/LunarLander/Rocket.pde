/*

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
    if (rocketCrashed == false && rocketLanded == false && fuelSupply > 0.0) {
      amount = constrain(amount, 0, 100);
      thrust = MAX_THRUST*amount/100;
      if (thrust < 0) thrust = 0;
    } else {
      thrust = 0;
      println("Fuel supply empty");
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
      // to make it more stable set very small values to 0
      if (abs(xVel) < 0.00005) xVel = 0;
      if (abs(yVel) < 0.00005) yVel = 0;
      fuelSupply = fuelSupply-(thrust*1000);
    }
      if (fuelSupply < 0.0) {
        lifeSupport--;
      if (lifeSupport < 0) {
        println("Life support diminished. Occupants are dead");
      }
    }
  }
    

    // draw it
    pushMatrix();
    translate(x, y);
    rotate(tilt - HALF_PI); 

    if (rocketCrashed == false && rocketLanded == false) {

      // draw the rocket body
      triangle(0, -30, 5, 0, -5, 0); // bad magic numbers here for the simple rocket body
      // draw the rocket thrust "flames" in RED
      stroke(255, 0, 0);
      line(0, 0, 0, thrust * FLAME_SCALE);
      // set stroke back to black
      stroke(0);
    } else if (rocketCrashed) {
      triangle(-25, -30, -15, -15, -5, -15); 
      triangle(-15, -15, -5, -13, -15, -3); 
      triangle(-17, 0, -7, -10, -1, 3); 
      triangle(-17, 0, -19, 2, -5, 5);
    } else if (rocketLanded) {
      triangle(0, -30, 5, 0, -5, 0);
    }

    popMatrix();
    println(x + ", " + y + ", " + xVel + ", " + yVel + ", " + thrust + ", " + fuelSupply + ", " + lifeSupport);

    if (x >= 360 && x <=450 && y >= 556 && y <= 560 && xVel < 0.2 && yVel < 0.2) {
      println("Rocket Landed");
      rocketLanded = true;
    } else if (y > 564) {
      println("Rocket Crashed");
      rocketCrashed = true;
    }
   }
  }
  private float x, y, xVel, yVel, thrust = GRAVITY, tilt = HALF_PI;
  private boolean rocketCrashed = false;
  private boolean rocketLanded = false; 
  private float fuelSupply = 1000.0;
  private float lifeSupport = 1000.0;

  // the values below were arrived at by trial and error
  // for something that had the responsiveness desired
  static final float GRAVITY = 0.001;
  static final float MAX_THRUST = 5*GRAVITY;
  static final float TILT_INC = 0.005;
  static final int FLAME_SCALE = 5000; // multiplier to determine how long the flame should be based on thrust
}