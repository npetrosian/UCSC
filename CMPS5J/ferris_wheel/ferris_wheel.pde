void setup(){
  size(800,800);
}

int radius = 300;
int numSpokes = 30;
int numLights = 10;
int lightSize = 10;
float angle = 0;

void draw(){
  background(255);
  translate(width/2,height/2);
  rotate(angle);
  angle = (angle + .01)%(2*PI);
  noFill();
  stroke(0);
  ellipse(0,0,radius*2,radius*2);
  for (int i = 1; i <= numSpokes; i++) {
    stroke(0);
    line(0,0,radius,0);
    rectMode(CENTER);
    fill(0,255,0);
    translate(radius,0);
    rotate(-angle-2*PI/numSpokes*(i-1));
    rect(0,0,40,40);
    rotate(angle+2*PI/numSpokes*(i-1));
    translate(-radius,0);

    for (int j = 1; j <= numLights; j++) {
      fill(255-j*20,j*20,0);
      noStroke();
      ellipse(j*radius/numLights,0,j*2,j*2);
    }
    rotate(2*PI/numSpokes);
  }
}