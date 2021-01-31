// Natalie Petrosian (npetrosi)
// CSE 130 Assignment 1
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

#define BUFFER_SIZE 2048
#define FOUR_KIB 4096
#define THIRTY_TWO_KIB 32768
// #define THIRTY_TWO_KIB 4096


char* getFileName(char *buff);
int getContentLength(char *buff);
int errorCheckFileName(char fileName[]);

// This routine processes the PUT requests sent by the client

int processPut(char* req, int client_sockd) {
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

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, req, sizeof(request)-1);

	// Get the file name from the request
	fileName = getFileName(request);

	// Check the validity of the file name
	retVal = errorCheckFileName(fileName);

	// Issue the 400 Bad Request if file name is invalid
	if(retVal == -1) {
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(-1);
	}

	// If we are still here, file name was good, but we have to skip the leading slash
	fileName++;

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, req, sizeof(request)-1);

	contentLength = getContentLength(request);
	if(contentLength == -1) {
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(-1);
	}

	fout = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0744);
	if(fout == -1) {
		switch(errno)
		{
			case EISDIR: 
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}

		send(client_sockd, errorMessage, strlen(errorMessage), 0);
		return(-1);
	}


	while (byteCount < contentLength) {
		bytes = recv(client_sockd, buff, THIRTY_TWO_KIB - 1, 0);
		buff[bytes] = 0; // null terminate
		write(fout, buff, bytes);
		byteCount += bytes;
	}

	close(fout);

	sprintf(serverMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 201, "Created", 0);
	send(client_sockd, serverMessage, strlen(serverMessage), 0);

	return(1);
}

// This routine processes the GET requests sent by the client

int processGet(char* req, int client_sockd) {
	char* fileName;
	char request[FOUR_KIB];
	struct stat fileStat;
	int retVal;
	int fin;
	char serverMessage[BUFFER_SIZE]; 
	char buff[THIRTY_TWO_KIB];
	int chars_read;
	char errorMessage[BUFFER_SIZE]; 

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, req, sizeof(request)-1);

	// Extract file name from request
	fileName = getFileName(request);

	// Error check validity of file name
	retVal = errorCheckFileName(fileName);

	// Send 400 Bad Request if file name is invalid
	if(retVal == -1) {
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(-1);
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
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
				sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}

		send(client_sockd, errorMessage, strlen(errorMessage), 0);
		return(-1);
	}

	// Check the status of the file, and get info
	retVal = fstat(fin, &fileStat);	

	// Prepare server message
	sprintf(serverMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %ld\r\n\r\n", 200, "OK", fileStat.st_size);

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
		retVal = send(client_sockd, buff, chars_read, 0);
		if(retVal == -1) {
			// send() failed, not much we can do except return
			return(-1);

		}
	}

	close(fin);
	return(1);
}

// This routine processes the HEAD requests sent by the client

int processHead(char* req, int client_sockd) {
	char* fileName;
	char request[FOUR_KIB];
	struct stat fileStat;
	int retVal;
	int fin;
	char serverMessage[BUFFER_SIZE];
	char errorMessage[BUFFER_SIZE]; 

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, req, sizeof(request)-1);

	// Extract file name from request
	fileName = getFileName(request);

	// Error check the file name
	retVal = errorCheckFileName(fileName);

	// Send 400 Bad Request if the file name is invalid
	if(retVal == -1) {
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(-1);
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
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case EACCES:
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 403, "Forbidden", 0);
				break;

			case ENOENT:
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 404, "Not Found", 0);
				break;	

			default: 
				sprintf(errorMessage, "HTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
		}
		
		// Send error message to the client
		send(client_sockd, errorMessage, strlen(errorMessage), 0);
		return(-1);
	}

	// If we're still here, file opened ok
	// Get file status, and info from the file
	retVal = fstat(fin, &fileStat);	

	// Prepare server response to the client
	sprintf(serverMessage, "HTTP/1.1 %d %s\r\nContent-Length: %ld\r\n\r\n", 200, "OK", fileStat.st_size);

	// Send the response to the client
	send(client_sockd, serverMessage, strlen(serverMessage), 0);

	close(fin);
	return(1);
}

// Extract command name from the request
char* getCommandName(char *buff) {
	
	char delimit[]=" \t\r\n\v\f"; 
    char *token;

    token = strtok(buff,delimit);

    return(token);

}

// Extract file name from the request
char* getFileName(char *buff) {
	
	char delimit[]=" \t\r\n\v\f"; 
    char *token;

    token = strtok(buff,delimit);
    token = strtok(NULL,delimit);

    return(token);
}

// Extract content length from the request
int getContentLength(char *buff) {
	
	char delimit[]=" :\t\r\n\v\f"; 
    char *token;
    int i;

    // Keep going through the tokens searching for the string Content-Length
    token = strtok(buff,delimit);
    while(token != NULL) {
    	if(!strcmp("Content-Length", token)) {
    		token = strtok(NULL,delimit);
    		break;
    	}
    	token = strtok(NULL,delimit);
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
	if (!strcmp("PUT",name) || !strcmp("GET",name) || !strcmp("HEAD",name) || !strcmp("POST", name)) {
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

// Ensure the request is valid

int errorCheckRequest(char *req) {
	char* token;
	char delimit[] = "\r\n";
	char buff[FOUR_KIB];
	int counter = 0;

	// Fail if request is NULL
	if(req == NULL) {
		return(-1);
	}

	// Fail if request is too long, per rubric
	if(strlen(req) > FOUR_KIB) {
		return(-1);
	}

	// Tokenize for carriage return and line feed
	// Make sure that all tokens have a colon

	token = strtok(buff,delimit);
	// Skip the first token, which contains the command and file name
	// Get the second token, which is probably a header
	token = strtok(NULL,delimit);

	while(token != NULL) {

		// Count the number of Content-Lengths' encountered
		if(strstr("Content-Length", token)){
			counter++;
		}

		// If we don't see a colon, return error
    	if(!strstr(":", token)) {
    		return(-1);
    	}

    	token = strtok(NULL,delimit);
    }

    // Encountered too many Content-Lengths, return error
    if(counter > 1) {
    	return(-1);
    }

    return(1);
}

// Parse the request and call the proper processing routines

int parseRequest(char* buff, int client_sockd) {
	char request[FOUR_KIB];
	char *commandName;
	int retVal;

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, buff, sizeof(request)-1);

	// Check the validity of the request
	retVal = errorCheckRequest(request);

	// Send the server response if an error in the request is detected
	if(retVal == -1){
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
		return(-1);
	}

	// Zero-out the request buffer and copy request into it
	// We need to do this before calling routines that use strtok()
	// because strtok() mangles the string sent to it
	memset(request, '\0', sizeof(request));
	strncpy(request, buff, sizeof(request)-1);

	// The first thing is to get the command name from the request
	commandName = getCommandName(request);

	// We need to make sure this is a valid command name
	retVal = errorCheckCommandName(commandName);

	// If the command name is invalid, send a 400 Bad Request response
	// Otherwise, call the pertinent routines
	if(retVal == -1) {
		send(client_sockd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n"), 0);
	}
	else {
		if (!strcmp(commandName, "PUT")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, buff, sizeof(request)-1);

			retVal = processPut(request, client_sockd);
		}
		else if (!strcmp(commandName, "GET")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, buff, sizeof(request)-1);

			retVal = processGet(request, client_sockd);
		}
		else if (!strcmp(commandName, "HEAD")) {
			memset(request, '\0', sizeof(request));
			strncpy(request, buff, sizeof(request)-1);

			retVal = processHead(request, client_sockd);
		}	
	}
	return(retVal);
}


int main(int argc, char** argv) {

	/*
		Create sockaddr_in with server information
	*/

	if(argc != 2){
		printf("Usage: httpserver <port number>\n");
		return(0);
	}
	char* port = argv[1];
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
	socklen_t client_addrlen;

	while(1){
		printf("[+] server is waiting...\n");
	
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

		retVal = parseRequest(request, client_sockd);

		printf("[+] received %ld bytes from client\n[+] response: ", bytes);
	
		close(client_sockd);

	}

	return 0;
}


