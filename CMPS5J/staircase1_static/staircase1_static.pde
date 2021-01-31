int startingX = 0;
int startingY = 0;

size(500, 500);

for (int count = 1; count <= width; count = count + 1){
  for (int y = startingY; y < height; y = y + 5){
    rect(startingX, y, 5, 5);
  }
  
  startingX += 5;
  startingY += 5;
}
    

    