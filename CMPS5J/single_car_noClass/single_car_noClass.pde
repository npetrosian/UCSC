color c; 
float xpos;
float ypos;
float xspeed;

void setup(){
  size(400,400);
  c = color(175);
  xpos = width/2;
  ypos = height/2;
  xspeed = 1;
}

void draw(){
  background(127);
  rectMode(CENTER);
  stroke(0);
  fill(c);
  rect(xpos,ypos,20,10);

  xpos = xpos + xspeed;
  if (xpos > width) {
      xpos = 0;
  }

}