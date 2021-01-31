float x = 0;

void setup(){
  size(200,200);
  rectMode(CENTER);
}

void draw(){
  background(255);
  fill(0);
  rect(x, 100, 20, 20);
  
  x = x + 1;
  
  if (x > 100){
     x = 100;
  }
}