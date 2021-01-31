int circleWidth = 40;
int circleHeight = 40;
int xpos = circleWidth/2;
int ypos = 200;
int rightSideLimit;
int leftSideLimit;
int delta = 1;
color bgc = color(random(255),random(255), random(255));

void setup(){
  size(400,400);
}

void draw(){
  background(127);
  fill(bgc);
  ellipse(xpos,ypos,circleWidth,circleHeight);
  xpos = xpos + delta;
  rightSideLimit = width - (circleWidth/2);
  leftSideLimit = circleWidth/2;
  
 if (xpos == rightSideLimit){
   delta = -1;
 }
 
 if (xpos == leftSideLimit){
   delta = 1;
 }
 
 if (mousePressed){
   bgc = color(255,0,0);
   fill(bgc);
   ellipse(xpos,ypos,circleWidth,circleHeight);
 }

}