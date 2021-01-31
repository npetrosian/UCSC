/*
  This program will display a sun with a mysterious object orbiting around it overlooking mountains in the ocean.
  As the the sun travels down the y-axis, the scene becomes darker. As the sun travels upwards, the scene 
  becomes brighter. 
*/
int r;

// variable declarations and initializations 
int backgroundRed = 0; // red color value for the background
int backgroundGreen = 0; // green color value for the background
int backgroundBlue = 255; // blue color value for the background

// color values for the sun
int sunRed = 245; // red color value for the sun
int sunGreen = 230; // green color value for the sun
int sunBlue = 57; // blue color value for the sun 

// dimensions of the sun
int sunX = 300;
int sunY = 300;
int sunSpeed = -1;
int sunWidth = 100; // width of the sun
int sunHeight = 100; // height of the sun

// color values for the ocean
int oceanRed = 0; // red color value for the ocean
int oceanGreen = 0; // green color value for the ocean
int oceanBlue = 150; // blue color value for the ocean

// coordinates and dimensions of the ocean
int oceanX = 0; // x coordinate for the ocean
int oceanY = 350; // y coordinate for the ocean
int oceanWidth = 600; // width of the ocean
int oceanHeight = 150; // height of the ocean

// color values for the first mountain
int firstMountainRed = 0; // red color value for the first mountain
int firstMountainGreen = 255; // green color value for the first mountain
int firstMountainBlue = 0; // blue color value for the first mountain

// coordinates for the first mountain
int firstMountainX1 = 50; // x1 coordinate for the first mountain
int firstMountainY1 = 350; // y1 coordinate for the first mountain 
int firstMountainX2 = 150; // x2 coordinate for the first mountain
int firstMountainY2 = 200; // y2 coordinate for the first mountain
int firstMountainX3 = 250; // x3 coorinate for the first mountain
int firstMountainY3 = 350; // y3 coordinate for the first mountain

// color values for the second mountain
int secondMountainRed = 0; // red color value for the second mountain 
int secondMountainGreen = 255; // green color value for the second mountain
int secondMountainBlue = 0; // blue color value for the second mountain

// coordinates for the second mountain
int secondMountainX1 = 0; // x1 coordinate for the second mountain
int secondMountainY1 = 400; // y1 coordinate for the second mountain
int secondMountainX2 = 100; // x2 coordinate for the second mountain
int secondMountainY2 = 200; // y2 coorindate for the second mountain
int secondMountainX3 = 200; // x3 coordinate for the second mountain
int secondMountainY3 = 400; // y3 coordinate for the second mountain

// color values for the third mountain
int thirdMountainRed = 0; // red color value for the third mountain
int thirdMountainGreen = 255; // green color value for the third mountain
int thirdMountainBlue = 0; // blue color value for the third mountain

// coordinates for the third mountain
int thirdMountainX1 = 401; // x1 coordinate for the third mountain
int thirdMountainY1 = 400; // y1 coordinate for the third mountain
int thirdMountainX2 = 500; // x2 coordinate for the third mountain
int thirdMountainY2 = 184; // y2 coordinate for the third mountain
int thirdMountainX3 = 600; // x3 coordinate for the third mountain
int thirdMountainY3 = 400; // y3 coordinate for the third mountain

// color value for the frosted mountain top
int frostedTopColor = 255; // white mountain top

// coordinates for the first mountain top 
int firstMountainTopX1 = 131; // x1 coordinate for the first mountain top
int firstMountainTopY1 = 262; // y1 coordinate for the first mountain top
int firstMountainTopX2 = 100; // x2 coordinate for the first mountain top
int firstMountainTopY2 = 200; // y2 coordinate for the first mountain top
int firstMountainTopX3 = 69; // x3 coordinate for the first mountain top
int firstMountainTopY3 = 262; // y3 coordinate for the first mountain top

// coordinates for the second mountain top
int secondMountainTopX1 = 179; // x1 coordinate for the second mountain top
int secondMountainTopY1 = 244; // y1 coordinate for the second mountain top
int secondMountainTopX2 = 150; // x2 coordinate for the second mountain top
int secondMountainTopY2 = 201; // y2 coordinate for the second mountain top
int secondMountainTopX3 = 121; // x3 coordinate for the second mountain top
int secondMountainTopY3 = 244; // y3 coordinate for the second mountain top

// coordinates for the third mountain top
int thirdMountainTopX1 = 522; // x1 coordinate for the third mountain top
int thirdMountainTopY1 = 232; // y1 coordinate for the third mountain top
int thirdMountainTopX2 = 478; // x2 coordinate for the third mountain top
int thirdMountainTopY2 = 232; // y2 coordinate for the third mountain top
int thirdMountainTopX3 = 500; // x3 coordinate for the third mountain top
int thirdMountainTopY3 = 183; // y3 coordinate for the third mountain top

void setup() {
  size(600, 500); // size of 600x500
}

void draw() {
  // draws the background
  background(backgroundRed, backgroundGreen, backgroundBlue-sunY);

  // draws the sun
  noStroke();
  fill(sunRed, sunGreen, sunBlue);
  ellipse(sunX,sunY, sunWidth, sunHeight);
  
  // little object orbiting the sun
  translate(sunX,sunY); // translate function
  rotate(radians(r)); // rotate function 
  fill(sunRed, sunGreen, sunBlue);
  ellipse(width/7, height/7, 15, 15);
  resetMatrix(); // resets the matrix so the entire scene does not rotate around the sun
  r+=2;

  // draws the ocean
  noStroke();
  fill(oceanRed, oceanGreen, oceanBlue-sunY/5);
  rect(oceanX, oceanY, oceanWidth, oceanHeight);

  // draws the mountains
  stroke(88,46,46);
  strokeWeight(2);
  fill(firstMountainRed, firstMountainGreen-sunY/3, firstMountainBlue);
  triangle(firstMountainX1, firstMountainY1, firstMountainX2, firstMountainY2, firstMountainX3, firstMountainY3);

  fill(secondMountainRed, secondMountainGreen-sunY/3, secondMountainBlue);
  triangle(secondMountainX1, secondMountainY1, secondMountainX2, secondMountainY2, secondMountainX3, secondMountainY3);

  fill(thirdMountainRed, thirdMountainGreen-sunY/3, thirdMountainBlue);
  triangle(thirdMountainX1, thirdMountainY1, thirdMountainX2, thirdMountainY2, thirdMountainX3, thirdMountainY3);

  // draws the frosted mountain tops
  fill(frostedTopColor);
  triangle(firstMountainTopX1, firstMountainTopY1, firstMountainTopX2, firstMountainTopY2, firstMountainTopX3, firstMountainTopY3);
  triangle(secondMountainTopX1, secondMountainTopY1, secondMountainTopX2, secondMountainTopY2, secondMountainTopX3, secondMountainTopY3);
  triangle(thirdMountainTopX1, thirdMountainTopY1, thirdMountainTopX2, thirdMountainTopY2, thirdMountainTopX3, thirdMountainTopY3);
  
// controls the direction of the sun
  if (sunY < 0) {
    sunSpeed = 1;
  }
  else if (sunY > oceanY) {
    sunSpeed = -1;
  }
  sunY+=sunSpeed;
}