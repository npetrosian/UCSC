size(400,400);
rectMode(CENTER);
translate(width/2,height/2);
float w = width;
for(int i = 1; i <= 10; i++){
  rect(0,0,w,w);
  w = sqrt((w/2)*(w/2)*2);
  rotate(PI/4);
}