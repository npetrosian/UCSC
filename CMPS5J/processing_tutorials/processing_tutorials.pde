int startingX = 0;
int startingY = 0;

void setup() {
  size(500, 500);
}

void draw() {
  for (int y = startingY; y < height; y = y + 5){
    rect(startingX, y, 5, 5);
  }
  
  startingX += 5;
  startingY += 5;
    
}