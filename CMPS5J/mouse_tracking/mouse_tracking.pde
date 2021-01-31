void setup () {
 size(800,600);
 background(255);
 strokeWeight(3);
}

void draw() {
 if (mousePressed) {
   line(pmouseX, pmouseY, mouseX, mouseY);
 }
}

void keyPressed() {
 save("image.tif");
}