Car redCar;
Car blueCar; // Two objects!

void setup() {
 size(480, 400);
 redCar = new Car(color(255,0,0), 0, 100, 2, 20, 10); // Parameters go inside the parentheses when the object is constructed.
 blueCar = new Car(color(0,0,255), 0, 300, 1, 20, 10);
}

void draw() {
 background(255);

 redCar.move();
 redCar.display();

 blueCar.move();
 blueCar.display();
}

class Car { // Even though there are multiple objects, we still only need one class. No matter how many cookies we make, only one cookie cutter is needed.Isn’t object-oriented programming swell?
 color c;
 float xpos;
 float ypos;
 float xspeed;
 int carWidth;
 int carHeight;

 Car(color tempC, float tempXpos, float tempYpos, float tempXspeed, int tempWidth, int tempHeight) { // The Constructor is defined with arguments.
   c = tempC;
   xpos = tempXpos;
   ypos = tempYpos;
   xspeed = tempXspeed;
   carWidth = tempWidth;
   carHeight = tempHeight;
 }

 void display() {
   stroke(0);
   fill(c);
   rectMode(CENTER);
   rect(xpos, ypos, carWidth, carHeight);
 }

 void move() {
   xpos = xpos + xspeed;
   if (xpos > width) {
     xpos = 0;
   }
 }
}