int startingX;
int startingY;

void setup() {
  size(500, 500);
  startingX = width - 5;
  startingY = 0;
}

void draw() {
  for (int y = startingY; y < height; y = y + 5){
    fill(random(255), random(255), random(255));
    rect(startingX, y, 5, 5);
    println(y);
  }
  
  startingX -= 5;
  startingY += 5;
  
    
}