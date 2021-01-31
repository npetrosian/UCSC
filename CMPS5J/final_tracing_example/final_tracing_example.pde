int maxXY = 0;

void setup(){
  size(400,400);
  frameRate(10);
}

void draw(){
  background(255);
  if (maxXY > mouseX || maxXY > mouseY) maxXY = 0;
  for (int col = 0; col < maxXY; col = col + 10){
    int row = 0;
    while (row < maxXY) {
      rect(row, col, 10, 10);
      row = row + 10;
    }
  }
  maxXY = maxXY + 10;
}