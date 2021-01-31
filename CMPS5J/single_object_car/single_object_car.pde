Car myCar;
Car redCar;
Car greenCar;
Car blackCar;

void setup(){
  size(400,400);
  redCar = new Car(80,80,4,color(255,0,0));
  greenCar = new Car(200,200,2,color(0,255,0));
  blackCar = new Car(300,200,-3);
  
}

void draw(){
  background(127);

  redCar.display();
  redCar.move();
  
  greenCar.display();
  greenCar.move();
  
  blackCar.display();
  blackCar.move();
  blackCar.collision(greenCar);
}


class Car { // Define a class below the rest of the program.
  color c; // Variables.
  float xpos;
  float ypos;
  float xspeed;

  Car(int tempX,int tempY, float tempSpeed, color tempC) { // A constructor.
    c = color(tempC);
    xpos = tempX;
    ypos = tempY;
    xspeed = tempSpeed;
  }
  
   Car(int tempX,int tempY, float tempSpeed) { // A constructor.
    c = color(0);
    xpos = tempX;
    ypos = tempY;
    xspeed = tempSpeed;
  }

  void display() { // Function.
    // The car is just a square
    rectMode(CENTER);
    stroke(0);
    fill(c);
    rect(xpos,ypos,20,10);
  }

  void move() { // Function.
    xpos = xpos + xspeed;
    if (xpos > width) {
      xpos = 0;
    }
    else if (xpos < 0)
      xpos = width;
  }
  
  void collision(Car otherCar){
    if (dist(this.xpos, this.ypos, otherCar.xpos, otherCar.ypos) <= 20){
      println("crash");
      this.ypos += 10;
      otherCar.ypos -= 10; 
    }
    
  }
}