/* 
  This program will display an image of buildings, a road, a cloud, and the sun.
*/

size(400,400);
background(93,180,255); // light blue  

// draws buildings
fill(127); // gray 
rect(0,305,60,30); // building 1 
rect(50,275,30,60); // building 2
rect(80,215,30,120); // building 3
rect(85,205,20,10); // first addition to building 3
rect(90,195,10,10); // second addition to building 3
rect(110,250,30,85); // building 4
rect(140,275,60,60); // building 5
rect(200,200,30,135); // building 6
triangle(200,200,215,170,230,200); // addition to building 6
rect(230,240,30,95); // building 7
rect(260,295,110,40); // building 8
rect(370,260,30,75); // building 9

// draws the sun
strokeWeight(2);
stroke(255,255,0); // yellow outline
fill(255,212,54); // yellow-orange fill
ellipse(360,30,30,30); // circular sun
line(310,30,345,30); // sun rays
line(350,40,315,57); // sun rays
line(360,45,360,80); // sun rays

// draws the cloud
noStroke(); 
fill(255); // white
ellipse(50, 70, 40, 20); // first white circle
ellipse(70, 70, 50, 50); // second white circle
ellipse(100, 70, 40, 30); // third white circle
ellipse(120, 70, 20, 10); // fourth white circle

// draws the windows
fill(255,255,0,191); // yellow windows at 75% opacity
rect(10,317,10,5); // first window on building 1
rect(30,317,10,5); // second window on building 1
rect(57,285,5,10); // first window on building 2
rect(70,285,5,10); // second window on building 2
rect(57,310,5,10); // third window on building 2
rect(70,310,5,10); // fourth window on building 2
rect(87,225,5,10); // first window on building 3
rect(100,225,5,10); // second window on building 3
rect(87,250,5,10); // third window on building 3
rect(100,250,5,10); // fourth window on building 3
rect(87,275,5,10); // fifth window on building 3
rect(100,275,5,10); // sixth window on building 3
rect(87,300,5,10); // seventh window on building 3
rect(100,300,5,10); // eighth window on building 3
rect(117,260,5,10); // first window on building 4
rect(128,260,5,10); // second window on building 4
rect(117,285,5,10); // third window on building 4
rect(128,285,5,10); // fourth window on building 4
rect(117,310,5,10); // fifth window on building 4
rect(128,310,5,10); // sixth window on building 4
rect(150,285,15,5); // first window on building 5
rect(180,285,15,5); // second window on building 5
rect(150,303,15,5); // third window on building 5
rect(180,303,15,5); // fourth window on building 5
rect(150,320,15,5); // fifth window on building 5
rect(180,320,15,5); // sixth window on building 5
rect(207,210,5,10); // first window on building 6
rect(220,210,5,10); // second window on building 6
rect(207,235,5,10); // third window on building 6
rect(220,235,5,10); // fourth window on building 6
rect(207,260,5,10); // fifth window on building 6
rect(220,260,5,10); // sixth window on building 6
rect(207,285,5,10); // seventh window on building 6
rect(220,285,5,10); // eighth window on building 6
rect(207,310,5,10); // ninth window on building 6
rect(220,310,5,10); // tenth window on building 6
rect(237,250,5,10); // first window on building 7
rect(248,250,5,10); // second window on building 7
rect(237,275,5,10); // third window on building 7
rect(248,275,5,10); // fourth window on building 7
rect(237,300,5,10); // fifth window on building 7
rect(248,300,5,10); // sixth window on building 7
rect(270,305,15,5); // first window on building 8
rect(310,305,15,5); // second window on building 8
rect(350,305,15,5); // third window on building 8
rect(270,320,15,5); // fourth window on building 8
rect(310,320,15,5); // fifth window on building 8
rect(350,320,15,5); // sixth window on building 8
rect(377,270,5,10); // first window on building 9
rect(390,270,5,10); // second window on building 9
rect(377,290,5,10); // third window on building 9
rect(390,290,5,10); // fourth window on building 9
rect(377,310,5,10); // fifth window on building 9
rect(390,310,5,10); // sixth window on building 9

// draws the road
fill(0);
rect(0,330,400,70);
rectMode(CENTER);
fill(255); // white
rect(20,370,30,5); // first white line
rect(80,370,30,5); // second white line
rect(140,370,30,5); // third white line
rect(200,370,30,5); // fourth white line
rect(260,370,30,5); // fifth white line
rect(320,370,30,5); // sixth white line
rect(380,370,30,5); // seventh white line