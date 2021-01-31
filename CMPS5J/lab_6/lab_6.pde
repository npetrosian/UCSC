void setup() {
  size(200,200);
}

void draw() {
  background(255);
  carBody(50,80,100,30);
  carWheels(60,110,20);
  carWheels(140,110,20);
}

void carBody(int xPos, int yPos, int widthLength, int heightLength) {
  fill(255,0,0);
  rect(xPos, yPos, widthLength, heightLength);
}

void carWheels(int xPos, int yPos, int radius) {
  fill(127);
  ellipse(xPos, yPos, radius, radius);
}