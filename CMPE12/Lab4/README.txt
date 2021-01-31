----------------------------
Lab 4: ASCII Decimal to 2SC
CMPE 012 Fall 2018

Petrosian, Natalie
npetrosi
----------------------------

What was your approach to converting each decimal number to two's complement form? 
First I created a mask like this:
10000000000000000000000000000000
Then I went into a loop that ANDed the mask with the integer sum and if it returned
a 0, I printed a character '0'. Otherwise, a '1'. At the end of each iteration, I 
performed a srl by 1 bit to cover all of the bits as follows:  
10000000000000000000000000000000
01000000000000000000000000000000
00100000000000000000000000000000
00010000000000000000000000000000
00001000000000000000000000000000
00000100000000000000000000000000
00000010000000000000000000000000
00000001000000000000000000000000
00000000100000000000000000000000
00000000010000000000000000000000
00000000001000000000000000000000
00000000000100000000000000000000
00000000000010000000000000000000
00000000000001000000000000000000
00000000000000100000000000000000
00000000000000010000000000000000
00000000000000001000000000000000
00000000000000000100000000000000
00000000000000000010000000000000
00000000000000000001000000000000
00000000000000000000100000000000
00000000000000000000010000000000
00000000000000000000001000000000
00000000000000000000000100000000
00000000000000000000000010000000
00000000000000000000000001000000
00000000000000000000000000100000
00000000000000000000000000010000
00000000000000000000000000001000
00000000000000000000000000000100
00000000000000000000000000000010
00000000000000000000000000000001

What did you learn in this lab? 
I learned how to access program arguments. 
I learned about converting program arguments to integers, and vice versa. 
I learned about several syscall codes. 
I learned about controlling the flow of code in assembly language by jumping to labels and back. 
I learned about jal and jr. 
I learned about masks and how to apply them. 
I completed the Morse code implementation and found it extremely challenging. 
I learned quite a bit about debugging in the MARS IDE. 

Did you encounter any issues? Were there parts of this lab you found enjoyable?
Overall, I found this lab to be very challenging and thought provoking.
I enjoyed converting the sum to 2SC binary using masks. 

How would you redesign this lab to make it better? 
I cannot think of a way to redesign this lab. It was designed to push and challenge us, and it 
achieved that. 
