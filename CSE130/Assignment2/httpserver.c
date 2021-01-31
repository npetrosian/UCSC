// Natalie Petrosian (npetrosi)
// CSE 130 Assignment 2
// Prof. Peter Alvaro

#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <unistd.h> // write
#include <string.h> // memset
#include <stdlib.h> // atoi 
#include <ctype.h>
#include <errno.h>
#include <pthread.h>

#define BUFFER_SIZE 2048
#define FOUR_KIB 4096
#define THIRTY_TWO_KIB 32768
// #define THIRTY_TWO_KIB 4096

typedef struct thread_arg_t {
    char req[FOUR_KIB];
    int client_sockd;
    pthread_mutex_t *pmutex;
    int requestsTotal;
    int failuresTotal;
    char logFilename[BUFFER_SIZE];
    int  logFilenameFD;
    int  logFileOffset;
    int  numMaxThreads;
} ThreadArg;


char* getFileName(char *buff);
int getContentLength(char *buff);
int errorCheckFileName(char fileName[]);
void dumphex(int fdin, int fdout);
int dumpHexString(char *buff, int fdout, int pos, int length);



// This function processes the PUT requests sent by the client

void* processPut(void *obj) {
	ThreadArg* argp = (ThreadArg*) obj;
	char request[FOUR_KIB];
	char* fileName;
	int contentLength;
	ssize_t bytes;
	uint8_t buff[THIRTY_TWO_KIB];
	int fout;
	int byteCount = 0;
	char errorMessage[BUFFER_SIZE]; 
	char serverMessage[BUFFER_SIZE]; 
	int retVal;
	

	// perform a lock here:
    pthread_mutex_lock(argp->pmutex);
    // CRITICAL SECTION

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(request)-1);

	// Get the file name from the request
	fileName = getFileName(request);

	// reset line logfile line offset to 0
    argp->logFileOffset = 0; 

	// Check the validity of the file name
	retVal = errorCheckFileName(fileName);

	// Issue the 400 Bad Request if file name is invalid
	if(retVal == -1) {
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		if (argp->logFilenameFD > 2) {
		    dprintf(argp->logFilenameFD,"FAIL: PUT %s HTTP/1.1 --- response 400\n========\n",fileName);
		}
		argp->failuresTotal++;
		return(NULL);
	}

	// healthcheck is a resource name reserved for GET only.
    // Generate a 403 for PUT
	if(!strcmp(fileName, "/healthcheck")) {
		// log error to the logfile
		if (argp->logFilenameFD > 2) {
		      dprintf(argp->logFilenameFD,"FAIL: PUT %s HTTP/1.1 --- response 403\n========\n",fileName);
		}
		// send error to the client on the socket connection
		sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
		send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);
		argp->failuresTotal++;
		return(NULL);
	}

	// If we are still here, file name was good, but we have to skip the leading slash
	fileName++;

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(request)-1);

	contentLength = getContentLength(request);
	if(contentLength == -1) {
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		if (argp->logFilenameFD > 2) {
		    dprintf(argp->logFilenameFD,"FAIL: PUT /%s HTTP/1.1 --- response 400\n========\n",fileName);
		}
		argp->failuresTotal++;
		return(NULL);
	}

	fout = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0744);
	if(fout == -1) {
		switch(errno)
		{
			case EISDIR: 
			    // log error to the logfile
			    if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: PUT /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
		        // prep error message to be sent over the socket to the client
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
			    // log error to the logfile
			    if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: PUT /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
		        // prep error message to be sent over the socket to the client
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
			    // log error to the logfile
			    if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: PUT /%s HTTP/1.1 --- response 404\n========\n",fileName);
		        }
		        // prep error message to be sent over the socket to the client
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
			    // log error to the logfile
			    if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: PUT /%s HTTP/1.1 --- response 500\n========\n",fileName);
		        }
		        // prep error message to be sent over the socket to the client
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}

		send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);
		argp->failuresTotal++;
		return(NULL);
	}

    // if we are still here then its time to log the success message to the logfile
	if (argp->logFilenameFD > 2) {
	     dprintf(argp->logFilenameFD,"PUT /%s length %d\n",fileName,contentLength);
	}

	while (byteCount < contentLength) {
		bytes = recv(argp->client_sockd, buff, THIRTY_TWO_KIB - 1, 0);
		buff[bytes] = 0; // null terminate
		write(fout, buff, bytes);
		byteCount += bytes;

		// write to the logfile while here
		if (argp->logFilenameFD > 2) {
		     argp->logFileOffset = dumpHexString((char *)buff, argp->logFilenameFD, argp->logFileOffset, bytes);
	    }

	}

	close(fout);

	// write the ending ====== to the logfile
	if (argp->logFilenameFD > 2) {
		if ((argp->logFileOffset % 20) == 0) {
	        dprintf(argp->logFilenameFD, "========\n");
	    } else {
            dprintf(argp->logFilenameFD, "\n========\n");
	    }
    }


	sprintf(serverMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 201, "Created", 0);
	send(argp->client_sockd, serverMessage, strlen(serverMessage), 0);

	// END CRITICAL SECTION
	// perform an unlock here:
	pthread_mutex_unlock(argp->pmutex);

	return(NULL);
}

// This routine processes the GET requests sent by the client

// int processGet(char* req, int client_sockd) {
void* processGet(void *obj) {
	ThreadArg* argp = (ThreadArg*) obj;
	char* fileName;
	char request[FOUR_KIB];
	struct stat fileStat;
	int retVal;
	int fin;
	char serverMessage[BUFFER_SIZE]; 
	char buff[THIRTY_TWO_KIB];
	int chars_read;
	char errorMessage[BUFFER_SIZE]; 
	



	// perform a lock here:
    pthread_mutex_lock(argp->pmutex);

    // CRITICAL SECTION

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(argp->req)-1);

	// Extract file name from request
	fileName = getFileName(request);

    // reset line logfile line offset to 0
    argp->logFileOffset = 0; 

	if(!strcmp(fileName, "/healthcheck")) {
		char buffer[20];
		int sumOfChars = 0;
		char message[500];
		
		// healthcheck should not count as a regular request
		// Commented out per TA suggestion during tests
		//argp->requestsTotal--;

        // if logfile has been specified 
        if (argp->logFilenameFD > 2) {

		       // itoa(argp->failuresTotal, buffer, 10);
		       sprintf(buffer, "%d", argp->failuresTotal);
		       sumOfChars += strlen(buffer);
       
		       // itoa(argp->requestsTotal, buffer, 10);
		       sprintf(buffer, "%d", argp->requestsTotal);
		       sumOfChars += strlen(buffer);

		       // add one more to the count for carriage return
		       sumOfChars += 1;
       
               // Per TA suggestion taking out header
		       // sprintf(message, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n%d\n%d", 200, "OK", sumOfChars, argp->failuresTotal, argp->requestsTotal);
		       sprintf(message, "\n%d\n%d", argp->failuresTotal, argp->requestsTotal-1);
		       send(argp->client_sockd, message, strlen(message), 0);

		       // log healthcheck like a regular GET
		       dprintf(argp->logFilenameFD,"GET %s length %d\n",fileName,sumOfChars);
		       sprintf(message, "%d\n%d", argp->failuresTotal, argp->requestsTotal-1);
		       dumpHexString((char *)message, argp->logFilenameFD, 0, strlen(message));
		       dprintf(argp->logFilenameFD,"\n========\n");
		} else {
			   // no logfiles were specified so we have to return a 404 to the client
			   sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
			   send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);
		}

		return(NULL);

	}


	// Error check validity of file name
	retVal = errorCheckFileName(fileName);

	// Send 400 Bad Request if file name is invalid
	if(retVal == -1) {
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		if (argp->logFilenameFD > 2) {
		    dprintf(argp->logFilenameFD,"FAIL: GET %s HTTP/1.1 --- response 400\n========\n",fileName);
		}
		argp->failuresTotal++;
		return(NULL);
	}


	// If we are still here, file name was good, but we have to skip the leading slash
	fileName++;

	// Open the file for reading
	fin = open(fileName, O_RDONLY);

	// Prepare the correct error response depending on the errno
	if(fin == -1) {
		switch(errno)
		{
			case EISDIR: 
			    // write the failure to the logfile
			    if (argp->logFilenameFD > 2) {
		             dprintf(argp->logFilenameFD,"FAIL: GET /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
			    // write the failure to the logfile
			    if (argp->logFilenameFD > 2) {
		             dprintf(argp->logFilenameFD,"FAIL: GET /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
			    // write the failure to the logfile
			    if (argp->logFilenameFD > 2) {
		             dprintf(argp->logFilenameFD,"FAIL: GET /%s HTTP/1.1 --- response 404\n========\n",fileName);
		        }
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
			    // write the failure to the logfile
			    if (argp->logFilenameFD > 2) {
		             dprintf(argp->logFilenameFD,"FAIL: GET /%s HTTP/1.1 --- response 404\n========\n",fileName);
		        }
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}


        // increment the failure count in the structure
		argp->failuresTotal++;

		// send the error message to the client
		send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);


		return(NULL);
	}


	// Check the status of the file, and get info
	retVal = fstat(fin, &fileStat);	

	// Prepare server message
	sprintf(serverMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %ld\r\n\r\n", 200, "OK", fileStat.st_size);

	// if we are still here then its time to log the success message to the logfile
	if (argp->logFilenameFD > 2) {
	     dprintf(argp->logFilenameFD,"GET /%s length %ld\n",fileName,fileStat.st_size);
	}

	// Get into read-write loop until broken by break
	while(1) {

		// Zero-out the buffer
		memset(buff, '\0', sizeof(buff));

		// Read from the open file
		chars_read = read(fin, buff, THIRTY_TWO_KIB - 1);

		buff[chars_read] = 0;

		// if there are no characters left, break
		if (chars_read == 0) {
			break;
		}
		retVal = send(argp->client_sockd, buff, chars_read, 0);
		if(retVal == -1) {
			// send() failed, not much we can do except return
			return(NULL);

		}

		// write to the logfile while here
		if (argp->logFilenameFD > 2) {
		    argp->logFileOffset = dumpHexString((char *)buff, argp->logFilenameFD, argp->logFileOffset, chars_read);	
	    }
	}

	close(fin);

    // write the ending ====== to the logfile
	if (argp->logFilenameFD > 2) {
		if ((argp->logFileOffset % 20) == 0) {
	        dprintf(argp->logFilenameFD, "========\n");
	    } else {
            dprintf(argp->logFilenameFD, "\n========\n");
	    }
    }
	


	// END CRITICAL SECTION

	// perform an unlock here:
	pthread_mutex_unlock(argp->pmutex);

	return(NULL);
}

// This routine processes the HEAD requests sent by the client

void* processHead(void *obj) {
	ThreadArg* argp = (ThreadArg*) obj;
	char* fileName;
	char request[FOUR_KIB];
	struct stat fileStat;
	int retVal;
	int fin;
	char serverMessage[BUFFER_SIZE];
	char errorMessage[BUFFER_SIZE]; 

	// CRITICAL SECTION START
	pthread_mutex_lock(argp->pmutex);


	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(request)-1);

	// Extract file name from request
	fileName = getFileName(request);

	// Error check the file name
	retVal = errorCheckFileName(fileName);

	// Send 400 Bad Request if the file name is invalid
	if(retVal == -1) {
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		// write error to the logfile
		if (argp->logFilenameFD > 2) {
		    dprintf(argp->logFilenameFD,"FAIL: HEAD %s HTTP/1.1 --- response 400\n========\n",fileName);
		}
		argp->failuresTotal++;
		return(NULL);
	}

	// healthcheck is a resource name reserved for GET only.
    // Generate a 403 for HEAD
	if(!strcmp(fileName, "/healthcheck")) {
		// log error to the logfile
		if (argp->logFilenameFD > 2) {
		      dprintf(argp->logFilenameFD,"FAIL: HEAD %s HTTP/1.1 --- response 403\n========\n",fileName);
		}
		// send error to the client on the socket connection
		sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
		send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);
		argp->failuresTotal++;
		return(NULL);
	}

	// If we are still here, file name was good, but we have to skip the leading slash
	fileName++;

	// Open the file for reading
	fin = open(fileName, O_RDONLY);

	// If open fails, prepare error messages depending on errno
	if(fin == -1) {
		switch(errno)
		{
			case EISDIR: 
			    // write error to the logfile
		        if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: HEAD /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
		        // prep error message to send over the socket
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
			    // write error to the logfile
		        if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: HEAD /%s HTTP/1.1 --- response 403\n========\n",fileName);
		        }
		        // prep error message to send over the socket
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
			    // write error to the logfile
		        if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: HEAD /%s HTTP/1.1 --- response 404\n========\n",fileName);
		        }
		        // prep error message to send over the socket
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
			    // write error to the logfile
		        if (argp->logFilenameFD > 2) {
		            dprintf(argp->logFilenameFD,"FAIL: HEAD /%s HTTP/1.1 --- response 500\n========\n",fileName);
		        }
		        // prep error message to send over the socket
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}
		
		// Send error message to the client
		send(argp->client_sockd, errorMessage, strlen(errorMessage), 0);
		argp->failuresTotal++;
		return(NULL);
	}

	// If we're still here, file opened ok
	// Get file status, and info from the file
	retVal = fstat(fin, &fileStat);	

	// Prepare server response to the client
	sprintf(serverMessage, "HTTP/1.1 %d %s\r\nContent-Length: %ld\r\n\r\n", 200, "OK", fileStat.st_size);

	// Send the response to the client
	send(argp->client_sockd, serverMessage, strlen(serverMessage), 0);

	// write Ok message to the logfile
	// if we are still here then its time to log the success message to the logfile
	if (argp->logFilenameFD > 2) {
	     dprintf(argp->logFilenameFD,"HEAD /%s length %ld\n",fileName,fileStat.st_size);
	}


	close(fin);

    // write the ending ====== to the logfile
    dprintf(argp->logFilenameFD, "========\n");
	    

	// CRITICAL SECTION END
	pthread_mutex_unlock(argp->pmutex);
	return(NULL);
}

// Extract command name from the request
char* getCommandName(char *buff) {
	
	char delimit[]=" \t\r\n\v\f"; 
    char *token;
    char *saveptr;

    token = strtok_r(buff, delimit, &saveptr);

    return(token);

}

// Extract file name from the request
char* getFileName(char *buff) {
	
	char delimit[]=" \t\r\n\v\f"; 
    char *token;
    char *saveptr;

    token = strtok_r(buff, delimit, &saveptr);
    token = strtok_r(NULL, delimit, &saveptr);

    return(token);
}

// Extract content length from the request
int getContentLength(char *buff) {
	
	char delimit[]=" :\t\r\n\v\f"; 
    char *token;
    int i;
    char *saveptr;

    // Keep going through the tokens searching for the string Content-Length
    token = strtok_r(buff, delimit, &saveptr);
    while(token != NULL) {
    	if(!strcmp("Content-Length", token)) {
    		token = strtok_r(NULL, delimit, &saveptr);
    		break;
    	}
    	token = strtok_r(NULL, delimit, &saveptr);
    }

    // Ensure that the string Content-Length is followed by valid number
    if(token != NULL){

    	for(i = 0; i < strlen(token); i++){
		
			if(!isdigit(token[i])){
				return(-1);
			}	
		}
		return(atoi(token));
    }
    
    return(-1);
}

// Make sure command name is valid

int errorCheckCommandName(char* name) {
	if (!strcmp("PUT",name) || !strcmp("GET",name) || !strcmp("HEAD",name)) {
		return(1);
	}
	else{
		return(-1);
	}
}

// Ensure the file name is valid, and per rubric

int errorCheckFileName(char fileName[]) {
	int i;
	int legalLength = 28;

	// Fail if file name does not start with a slash
	if(fileName[0] != '/') {
		return(-1);
	}

	// Fail if file name is too long
	if(strlen(fileName) > legalLength){
		return(-1);
	}
	
	// Fail if file name has illegal characters
	for (i = 1; i < strlen(fileName); i++){
		if(!(isalpha(fileName[i]) || isdigit(fileName[i]) || fileName[i] == '-' 
			                    || fileName[i] == '_')){

			return(-1);
		}
		
	}

	return(1);
}



//This function prints an asscii representation of the buff into
// its output file which is the log files file descriptor
int dumpHexString(char *buff, int fdout, int pos, int length) {

	int i;
    int chars_read;


    if (buff != NULL) {

        // for (i=0; i < strlen(buff); i++) {
    	for (i=0; i < length; i++) {

            // if we're at the beginning of a new line
    	    if ((pos % 20) == 0) {
    	    	dprintf(fdout, "%08d ",pos);
    	    }

            // if we're at the end of the line
        	if (pos>0 && ((pos+1)%20 == 0)) {
        		dprintf(fdout,"%02hhx\n", (unsigned char)buff[i]);
        	} else {
        		if ((length -i)==1) {
        		     dprintf(fdout,"%02hhx",(unsigned char)buff[i]);
        		} else {
        			 dprintf(fdout,"%02hhx ",(unsigned char)buff[i]);
        		}
        	}
    
            pos++;
        }                    
    }
    
    return(pos);

}


// Ensure the request is valid

int errorCheckRequest(char *req) {
	char* token;
	char delimit[] = "\r\n";
	char buff[FOUR_KIB];
	int counter = 0;
	char *saveptr;

	// Fail if request is NULL
	if(req == NULL) {
		return(-1);
	}

	// Fail if request is too long, per rubric
	if(strlen(req) > FOUR_KIB) {
		return(-1);
	}

	// Fail if HTTP version is NOT 1.1
  	if (!strstr(req, "HTTP/1.1")) {
  		return(-1);
  	}

	// Tokenize for carriage return and line feed
	// Make sure that all tokens have a colon

	token = strtok_r(buff, delimit, &saveptr);
	// Skip the first token, which contains the command and file name
	// Get the second token, which is probably a header
	token = strtok_r(NULL, delimit, &saveptr);

	while(token != NULL) {

		// Count the number of Content-Lengths' encountered
		if(strstr("Content-Length", token)){
			counter++;
		}

		// If we don't see a colon, return error
    	if(!strstr(":", token)) {
    		return(-1);
    	}

    	token = strtok_r(NULL, delimit, &saveptr);
    }

    // Encountered too many Content-Lengths, return error
    if(counter > 1) {
    	return(-1);
    }

    return(1);
}

// Parse the request and call the proper processing routines

void* parseRequest(void *obj) {
	ThreadArg* argp = (ThreadArg*) obj;
	char request[FOUR_KIB];
	char *commandName;
	int retVal;

	pthread_t thread_id;
	// ThreadArg arg;
	pthread_mutex_t my_mutex;


	pthread_mutex_init(&my_mutex, NULL);

	argp->requestsTotal++;


	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(request)-1);

	// Check the validity of the request
	retVal = errorCheckRequest(request);

	// Send the server response if an error in the request is detected
	if(retVal == -1){
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(NULL);
	}

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, argp->req, sizeof(request)-1);

	// The first thing is to get the command name from the request
	commandName = getCommandName(request);

	// We need to make sure this is a valid command name
	retVal = errorCheckCommandName(commandName);

	// If the command name is invalid, send a 400 Bad Request response
	// Otherwise, call the pertinent routines
	if(retVal == -1) {
		send(argp->client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
	}
	else {
		if (!strcmp(commandName, "PUT")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, argp->req, sizeof(request)-1);

			// arg.client_sockd = argp->client_sockd;
			// strncpy(arg.req, argp->req, sizeof(request)-1);
			// arg.pmutex = &my_mutex;
			// arg.requestsTotal = argp->requestsTotal;
			// arg.failuresTotal = argp->failuresTotal;

			argp->pmutex = &my_mutex;


			pthread_create(&thread_id, NULL, processPut, argp);

			// retVal = processPut(request, client_sockd);

			pthread_join(thread_id, NULL);
		}
		else if (!strcmp(commandName, "GET")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, argp->req, sizeof(request)-1);

			// arg.client_sockd = argp->client_sockd;
			// strncpy(arg.req, argp->req, sizeof(request)-1);
			// arg.pmutex = &my_mutex;
			// arg.requestsTotal = argp->requestsTotal;
			// arg.failuresTotal = argp->failuresTotal;

			argp->pmutex = &my_mutex;

			pthread_create(&thread_id, NULL, processGet, argp);

			// retVal = processGet(request, client_sockd);

			pthread_join(thread_id, NULL);


		}
		else if (!strcmp(commandName, "HEAD")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, argp->req, sizeof(request)-1);

			// arg.client_sockd = argp->client_sockd;
			// strncpy(arg.req, argp->req, sizeof(request)-1);
			// arg.pmutex = &my_mutex;
			// arg.requestsTotal = argp->requestsTotal;
			// arg.failuresTotal = argp->failuresTotal;

			argp->pmutex = &my_mutex;


			pthread_create(&thread_id, NULL, processHead, argp);

			// retVal = processHead(request, client_sockd);

			pthread_join(thread_id, NULL);
		}	
	}
	return(NULL);
}




int main(int argc, char** argv) {

	pthread_t thread_id;
	ThreadArg arg;


	// initialize totals that will be tallied during the run
    arg.requestsTotal = 0;
    arg.failuresTotal = 0;
    // initialize logfile name
    strcpy(arg.logFilename,"");
    // initialize the offset into the log file to 0
    arg.logFileOffset = 0;
    // initialize max number of worker threads
    // Default is 4 per the rubric
    arg.numMaxThreads = 4;



	if(argc < 2){
		printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
		return(-1);
	}

	// retrieve the -l and -N and port number parameters
    int opt;
    int portnum;
	while(1) { 
		opt = getopt(argc, argv, "N:l:");
		if (opt == -1) {break;}
		if (opt == 'N') {
			// printf ("N = <%s>\n", optarg);
			arg.numMaxThreads = atoi(optarg);
			if (arg.numMaxThreads == 0) {
				printf("-N must be followed by a valid non-zero int\n");
			    printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
		        return(-1);
			}

		} else if (opt == 'l') {
			// printf ("logfile is = <%s>\n", optarg);
			strncpy(arg.logFilename, optarg, sizeof(arg.logFilename)-1);
			if (!strcmp(arg.logFilename,"-N")) {
				printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
			    return(-1);
			}
			arg.logFilenameFD = open(arg.logFilename, O_RDWR | O_CREAT | O_TRUNC, 0744);
		} else {
			printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
			return(-1);
		}   
	}


	if (optind != argc) {
		portnum = atoi(argv[optind]);
		if (portnum == 0) {
			printf("port number must be a valid non-zero int\n");
			printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
		    return(-1);
		} 
		if (argc - optind != 1) {
			printf("irregularity detected in the arguments\n");
			printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
		    return(-1);
		}
	} else {
		printf("-N and -l should follow the expected parameters and a port should be specified\n");
		printf("Usage: httpserver <port_numer> [-N <number of threads>] [-l <log_file_name>]\n");
		return(-1);
	}

	char* port = argv[optind];
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr)); 
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(atoi(port)); 
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	socklen_t addrlen = sizeof(server_addr);

	char* commandName;
	int retVal;
	int contentLength;
	char request[FOUR_KIB];
    int i;
	

	// if -l was specified open the logfile and truncate it to 0 length if
	// it already exists
    // if (strlen(arg.logFilename) > 0) {
    //      arg.logFilenameFD = open(arg.logFilename, O_RDWR | O_CREAT | O_TRUNC, 0744);
    // }

	/*
		Create server socket
	*/

	int server_sockd = socket(AF_INET, SOCK_STREAM, 0);

	/*
		Check if server_sockd < 0 (an error)
	*/

	if(server_sockd < 0) {
		perror("socket");
	}

	/*
		Configure server socket
	*/

	int enable = 1;

	/*
		This avoids: 'Bind: Address Already in Use' error
	*/

	int ret = setsockopt(server_sockd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

	/*
		Bind server address to socket that is open
	*/

	ret = bind(server_sockd, (struct sockaddr *) &server_addr, addrlen);

	/*
		Listen for incoming connections
	*/

	ret = listen(server_sockd, 5); /* 5 should be enough, if not use SOMAXCONN */

	if (ret < 0) {
		return 1;
	}

	/*
		Connecting with a client
	*/

	struct sockaddr client_addr;
	// Piazza post 809 -> change to socklen_t client_addrlen = sizeof(client_addr);
	socklen_t client_addrlen;

	while(1){
		printf("[+] server is waiting...\n");
		// printf("N = %d  logfile = %s  port = %s\n", arg.numMaxThreads, arg.logFilename, port);
	
		int client_sockd = accept(server_sockd, &client_addr, &client_addrlen); 
		// Remember errors happen
	
		uint8_t buff[BUFFER_SIZE + 1];
		// char buff[BUFFER_SIZE + 1];
		ssize_t bytes = recv(client_sockd, buff, BUFFER_SIZE, 0);
		buff[bytes] = 0; // null terminate

		// Zero-out the request buffer and copy request into it
		// We need to do this before calling routines that use strtok()
		// because strtok() mangles the string sent to it
		memset(request, '\0', sizeof(request));
		strncpy(request, (char*)buff, sizeof(request)-1);


		arg.client_sockd = client_sockd;
		strncpy(arg.req, (char*)buff, sizeof(arg.req)-1);
		pthread_create(&thread_id, NULL, parseRequest, &arg);

		pthread_join(thread_id, NULL);

		// retVal = parseRequest(request, client_sockd);

		printf("[+] received %ld bytes from client\n[+] response: ", bytes);
	
		close(client_sockd);
		// close(arg.logFilenameFD);

	}

    close(arg.logFilenameFD);

	return 0;
}


