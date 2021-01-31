Ball  ball1;
Ball  ball2;


void setup() {
size(400, 400);
fill (255,0,0);

ball1 = new Ball(random(width), random(height), random(-1,1), 
                          random(-1,1), int(random(5,30)));

ball2 = new Ball(random(width), random(height), random(-1,1), 
                          random(-1,1), int(random(5,30)));

}

void draw(){
background(255);
ball1.update();
ball2.update();
}