// This program writes a function that finds the maximum value between two numbers

int maxValue;

void setup(){
  maxValue = maximum(40,30);
  println(maxValue);
}

int maximum(int x, int y) {
  if (x >= y) {
    return x;
  }
  else {
    return y;
  } 
}