Ball[] balls = new Ball[200];

void setup() {
size(400, 400);
fill (255, 0, 0);
for (int i = 0; i < balls.length; i++) {
  balls[i] = new Ball(random(400), random(height), random(-1, 1), 
    random(-1, 1), int(random(5, 30)));
}
}

void draw() {
background(0, 255, 0);
for (int i=0; i< balls.length; i++) {
  balls[i].update();
  for (int other = 0; other < balls.length; other++) {
    if (other != i && balls[i].collidedWithBall(balls[other])) {
      balls[i].reverseX();
      balls[other].reverseX();
    }
  }
}
}