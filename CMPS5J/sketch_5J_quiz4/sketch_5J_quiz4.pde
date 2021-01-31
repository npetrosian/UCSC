void setup(){
  int sz = 5;
  for (int y = 5; y < height; y = y + sz*2) {
    blackBox(width/2,y,sz);
    fill(255);
    ellipse(width/2, y + sz, sz, sz);
    sz = sz + 2;
  }
}

void blackBox(int x, int y, int sz){
  rectMode(CENTER);
  fill(0);
  rect(x,y,sz,sz);
  
}