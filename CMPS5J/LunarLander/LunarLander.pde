/*

 */

Rocket rocket;

void setup() {
  size(600, 600);
  rocket = new Rocket(width/2, height/2);
}

void draw() {
  background(0);
  drawLandscape();
  adjustControls(rocket);
  rocket.update();
}
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