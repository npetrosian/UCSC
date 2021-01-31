// Natalie Petrosian (npetrosi)
// CSE 130 Principles of Computer System Design
// Assignment 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define MAX_SIZE 32000
#define ERR_MSG_SIZE 500

int readFromStandardInput() {

	char buff[MAX_SIZE];
	int chars_read;

	while(1) {
		// read from standard in
		chars_read = read(STDIN_FILENO, buff, MAX_SIZE);
		// when the user inputs EOF ctl-D read returns a 0
		// and we return from this function
		if (chars_read == 0) {
			return 1;
		}
		write(STDOUT_FILENO, buff, chars_read);
	}

}

int main(int argc, char** argv) {
	int i;
	char buff[MAX_SIZE];
	char error_message[ERR_MSG_SIZE];
	int chars_read;
	int input_fds;


    // when no input parameters are specified just read from standard input
    // until EOF ctl-D
	if(argc == 1) {
		readFromStandardInput();
	}

	else {
		// process the parameters one by one in reverse order
		for (i = argc - 1; i >= 1; i--) {

			// if a - is specified just read from standard input 
			if (!strcmp(argv[i], "-")) {
                readFromStandardInput();		
			}

			else {

				// open file for reading
				input_fds = open(argv[i], O_RDONLY);
				
				// if an error occured set up an error message similar to cat and 
				// use perror() to print it
			    if (input_fds == -1){
			    	sprintf(error_message, "dog: %s", argv[i]);
			    	perror(error_message);
			    } else {
                    // read from the file handle and write to 
                    // standard out
                    while(1) {
			    		chars_read = read(input_fds, buff, MAX_SIZE);
			    		if (chars_read == 0) {
			    			break;
			    		}
			    		write(STDOUT_FILENO, buff, chars_read);
			    	}
			    }
			}
			
		}
	}
}