String labelOne = "one";
String labelTwo = "two";
int rectOneX = 50;
int rectOneY = 50;
int rectOneWidth = 100;
int rectOneHeight = 50;
int rectTwoX = 250;
int rectTwoY = 50;
int rectTwoWidth = 100;
int rectTwoHeight = 50;

void setup(){
  size(400,400);
}

void draw(){
  int boxClicked = 0;
  fill(255,0,0);
  rect(rectOneX,rectOneY,rectOneWidth,rectOneHeight);
  rect(rectTwoX,rectTwoY,rectTwoWidth,rectTwoHeight);
  fill(0,0,255);
  text(labelOne,rectOneX+30,rectOneY+25);
  text(labelTwo,rectTwoX+30,rectOneY+25); //<>//
  
  if (mousePressed){
    boxClicked = determineBox();
    if (boxClicked == 1){
      println("Box one was clicked");
    }
    else if (boxClicked == 2){
      println("Box two was clicked");
    }
      
  }
   
}

int determineBox(){
  if (mouseX >= rectOneX && mouseX <= rectOneX + rectOneWidth && mouseY >= rectOneY && mouseY <= rectOneY + rectOneHeight){
    return 1;
  }
  if (mouseX >= rectTwoX && mouseX <= rectTwoX + rectTwoWidth && mouseY >= rectTwoY && mouseY <= rectTwoY + rectTwoHeight){
    return 2;
  }
  return 0;
}