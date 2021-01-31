# CSE 130 Principles of Computer System Design 
# Assignment 0

In this assignment, we write a version of the Unix command 'cat'. It is called
'dog', and it processes the input parameters in the reverse order of 'cat'. 
'dog' is limited to buffers no larger than 32 KiB of memory and it shall not 
use FILE pointers or any library calls associated with them or iostream and 
fstream. 

'dog' specified without any parameters shall get its input from standard-in. 
Otherwise, file names can be specified as parameters. A - (dash) can be 
specified as a parameter, which shall be interpreted as processing the input 
from standard-in. 

A Makefilie has been provided along with dog.c into the repository. To compile
dog.c into dog, just run "make". 
