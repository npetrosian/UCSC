-----------------------
Lab 5: Subroutines
CMPE 012 Fall 2018

Petrosian, Natalie
npetrosi
-----------------------

What was your design approach? 
The approach is to create subroutines which break down the problem into smaller 
subsets of the problem and calling subroutines which solves those smaller problems. 
For example, check_user_input_string handles the timing issue but passes on the 
string comparison to compare_strings. compare_strings handles traversing the strings
character by character but passes on the actual character comparison to compare_chars.
Success or failure is recorded in $v0 and passed up the call tree. 

What did you learn in this lab?
Learned how subroutines work. 
Learned how to preserve $ra in the stack pointer. 
Learned how to restore $ra from the stack pointer and return to caller.
Learned how to break down a problem into subroutines.

Did you encounter any issues? Were there parts of this lab you found enjoyable?
This lab was very enjoyable, and I found it much easier than Lab 4. 

How would you redesign this lab to make it better? 
This lab was perfectly design to demonstrate and teach the interworkings of subroutines
and working with stacks. I can't think of a way to improve this lab assignment. 
