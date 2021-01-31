class Ball {
  float x, y, xVel, yVel;
  int diam;

  Ball (float xStart, float yStart, float xV, float yV, int diameter) {
    x = xStart;
    y = yStart;
    xVel = xV;
    yVel = yV;
    diam = diameter;
  }

  void update() {

    // if hits ground or ceiling reverse velocity
    if (y > height - diam/2 || y < diam/2) {
      yVel = -yVel;
    }

    if (x > width-diam/2 || x < diam/2) {
      xVel = -xVel;
    }

    // adjust position based on velocity
    y = y + yVel;
    x = x + xVel;

    ellipse(x, y, diam/2, diam/2);
  }

  void reverseX() {
    xVel = - xVel;
  }

  boolean collidedWithBall(Ball other) {
    return dist(x, y, other.x, other.y) <= (other.diam+this.diam)/2;
  }
}