void setup () {

 size(600,600);
 // draw a red line showing the actual value of PI
 stroke(255,0,0);
 line (0, scaleAndTranslate(PI), width, scaleAndTranslate(PI));
 stroke(0); //use black for future drawing
}

int scaleAndTranslate(float est) {
 int precision = 1000; // bigger means better PI precision
 float guess = 3; // close but on the low side
 return height-int(precision *(est -guess));
}

void draw() {
 strokeWeight(3);
 // point(frameCount, scaleAndTranslate(3+sin(radians(frameCount))));
 point( frameCount, scaleAndTranslate(random(3, 3.2)));
}