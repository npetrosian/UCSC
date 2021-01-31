int pos = 0;
void draw(){
  background(255);
  if (pos < width/2){
    pos++;
  }
  ellipse(pos,pos,20,20);
}