int maxValue;

void draw(){
  maxValue = maxFunction(mouseX,mouseY);
  println(maxValue);
}

int maxFunction(int x, int y) {
  if (x >= y){
    return x;
  }
  else {
    return y;
  }
}