Light light;
void setup() {
  size(400, 400);
  light = new Light(width/2, height/2, 20); 
  noStroke();
}
void draw() {
  light.draw();
}
void mousePressed() { 
  if (light.mouseOn())
    light.toggle();
}
void keyPressed() {
  if (key == 'n') light.turnOn();
  else if (key == 'f') light.turnOff();
}
class Light {
  int clr = color(255, 255, 0);
  int x, y, diam;
  boolean on = false;
  Light(int xPos, int yPos, int sz) {
    x = xPos;
    y = yPos;
    diam = sz;
  }
  void draw() {
    if (on) fill(clr);
    else fill(0);
    ellipse(x, y, diam, diam);
  }
  boolean mouseOn(){
    return dist(mouseX,mouseY,x,y) <= diam/2;
  }
  void toggle(){
    on = !on;
  }
  void turnOn(){
    on = true;
  }
  void turnOff(){
    on = false;
  }
}