/*
Program 5 CMPS 5J:

This program generates a random quilt quilt on startup and every time a key is pressed. A random panel in the quilt
will have an animation within it.

The following objectives in the requirement and rubric were followed:

1. Three required, parameterized methods are used named drawQuilt(), drawRow() and drawPanel()
2. DrawPanel() is based upon the drawPanel() method provided by Charlie McDowell
3. DrawPanel() was modified to generate different panels as follows:
Large square and centered circle (small panel)
Large square and centered circle (large panel)
Large circle and centered square (small panel)    
Large circle and centered square (large panel)
Random colors in all the panel elements based on the seed.
4. Animated rotating ellipse was added to a random square in the quilt, satisfying the extra credit requirement.
5. Program draws a different quilt each time it starts, satisfying rubric.
6. The large and small sizes of the quilt are easy to change as demonstrated with each key press
7. For loops and if statements were used to achieve the requirements
8. None of the functions are larger than 25 lines, satisfying rubric     

*/

// variables
int panelWidth = 50;
int panelHeight = 50;
int smallPanelWidth = 50;
int smallPanelHeight = 50;
int largePanelWidth = 100;
int largePanelHeight = 100;
int startingX = 10;
int startingY = 10;
int endingX = 300;
int endingY = 300;
int r;
int columnsOfPanels;
int rowsOfPanels;
int animatedPanelColumn;
int animatedPanelRow;
int centerAnimatedPanelX;
int centerAnimatedPanelY;
int seed = (int)random(100000); // for the random number generator

// A simple setup method which only sets up the screen size
void setup() {
 size(600, 400);
}

// This method makes a call to drawQuilt() which draws and entire quilt.
// It then selects a random panel in the quilt and animates a rotating
// ellipse on the center coordinates of that panel

void draw() {

 background(100);  // draw background and clear everything
 randomSeed(seed); // generate random seed
 drawQuilt(startingX, startingY, endingX, endingY); // draw the quilt

 // selecting the random panel for a rotating an ellipse in it
 columnsOfPanels = (endingX-startingX)/panelWidth; // find out how many columns in the quilt
 rowsOfPanels = (endingY-startingY)/panelHeight; // find out how many rows in the quilt
 animatedPanelColumn = (int)random(0, columnsOfPanels); // pick a random column
 animatedPanelRow = (int)random(0, rowsOfPanels); // pick a random row
 centerAnimatedPanelX = startingX+(animatedPanelColumn*panelWidth)+(panelWidth/2); // find X of the center of the panel
 centerAnimatedPanelY = startingY+(animatedPanelRow*panelHeight)+(panelHeight/2); // find Y of the center of the panel

 // rotate an ellipse at the center of the random panel as calculated above
 translate(centerAnimatedPanelX, centerAnimatedPanelY);
 fill(255);
 rotate(radians(r));
 ellipse(0, 0, panelWidth, panelHeight/4);
 r+=2;
}

// randomizes the length and height of the quilt when a key is pressed
void keyPressed() {
 //picks a new seed for a new quilt
 seed = (int)random(100000);
 endingX = (int)random(200, 400);
 endingY = (int)random(200, 300);

 // changes the panel dimensions when the seed is even or odd
 // using IF STATEMENT
 if (seed % 2 == 0) {
   panelWidth = smallPanelWidth;
   panelHeight = smallPanelHeight;
 } else {
   panelWidth = largePanelWidth;
   panelHeight = largePanelHeight;
 }
}

// draws panels across the top row
void drawRow(int x1, int y1, int x2) {
 for (int i = x1; i <= x2; i+= panelWidth) {
   drawPanel(i, y1, panelWidth, panelHeight);
 }
}

// rows of panels are drawn until the quilt is complete
// using FOR-LOOP
void drawQuilt(int x1, int y1, int x2, int y2) {
 for (int i = y1; i <= y2; i+=panelHeight) {
   drawRow(x1, i, x2);
 }
}

// ORIGINAL DRAW PANEL PROVIDED BY PROFESSOR MCDOWELL
// Code added to achieve rubric and objectives of Program 5

void drawPanel(int x, int y, int w, int h) {
 // draw this panel in an off screen image so it gets automatically clipped to the edges of the panel
 // img is where we will draw - use same commands as before preceeded by "img."
 PGraphics img = createGraphics(w, h);
 img.beginDraw();
 img.background(random(255), random(255), random(255));
 img.fill(random(255), random(255), random(255));
 // if-statement will draw an ellipse at the center of each panel if the seed is an even number
 if (seed % 2 == 0) {
   img.ellipse(w/2, h/2, w/4, h/4);
 } else {
   img.rect(w/2, h/2, w/4, h/4);
 } 
 img.translate(w/2, h/2);
 img.rotate(random(PI));
 img.fill(random(255), random(255), random(255));

 // draw rectangle or circle based on seed being even or odd
 if (seed % 2 == 0) {
   img.rect(0, 0, w, h);
 } else {
   img.ellipse(-w/2, 0, w/2, h/2);
 }
 img.endDraw();
 image(img, x, y);
}