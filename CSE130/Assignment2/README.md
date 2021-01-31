In this assignment, three additional features have been added to our HTTP
server: multithreading, logging, and a health check. 

A Makefile has been submitted along with the code.
To compile, just run 'make'.
To run the server, type './httpserver' followed by a port name. For example:
./httpserver 8080

Due to the additions of logging and a health check, there are two optional 
parameters: -N (followed by a positive integer) and -l (followed by a file
name). 

-N followed by a positive integer specifies the number of worker threads. 
For example, -N 5 specifies that the number of worker threads is 5. If this
optional parameter is left unspecified, N will default to 4 worker threads. 

-l followed by a file name logs the perforamance of the server into that 
file. For example, -l log_file puts the health check information into 
log_file. 

A port number has to be specified. The optional parameters and the port name
can be specified in any order. 

The following are examples of running the server with the optional parameters:
./httpserver 8080 -N 8 -l log_file
./httpserver 8080 -N 6
./httpserver 8080 -l log_file
