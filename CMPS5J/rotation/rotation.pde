int r;

void setup(){
  size(400,400);
}

void draw(){
  background(0);
  fill(255,255,0);
  ellipse(200,200,40,40);
  translate(width/2, height/2);
  rotate(radians(r));
  fill(0,0,255);
  ellipse(100,100,20,20);
  r+=1;
  
}
  