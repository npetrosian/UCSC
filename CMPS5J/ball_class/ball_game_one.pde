Ball ballOne;

void setup(){
  size(600,600);
  ballOne = new Ball(random(height), random(width), random(-1,1), random(-1,1), int (random(10,40)));
  fill(255,0,0);
}

void draw(){
  background(255);
  ballOne.update();
}