int x = 50, xVel = 1;
void draw(){
  background(255);
  rect(20,20,60,60);
  ellipse(x,50,10,10);
  x = x + xVel;
  if (x > 75){
    xVel = -1;
  }
  else if (x < 25){
    xVel = 1;
  }
}
    