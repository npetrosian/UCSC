// Natalie Petrosian (npetrosi)
// CSE 130 Assignment 3
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
#include <err.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

void* server_get_health(void *obj);

typedef struct thread_args_t {
    pthread_mutex_t *pmutex;
    uint16_t port;
    int  health;
    int  requestsTotal;
    int  failuresTotal;
    int  index;
    char response[500];
    char message[500];
    int  server_sock_id;
} ThreadArg;

int client_connect(uint16_t connectport);

void threadsOfHealthCheckers(ThreadArg args[], uint16_t ports[], int numOfPorts, int maxNumConnections) {

    int i,j;
    pthread_t threads_array[1024];
    pthread_mutex_t my_mutex;
    pthread_mutex_init(&my_mutex, NULL);


    int groups = numOfPorts / maxNumConnections;
    int remain = numOfPorts % maxNumConnections;

    int saveIndex;
    int index = 0;

    // printf("\ngroups=%d remain=%d maxConns=%d\n",groups, remain, maxNumConnections);

    for (i=0; i<groups; i++) {
        saveIndex = index;
        for (j=0; j< maxNumConnections; j++) {
               // printf("index (create) = %d\n", index);
               args[index].port = ports[index];
               args[index].pmutex = &my_mutex;
               args[index].index = i;
               args[index].failuresTotal = -99;
               args[index].requestsTotal = -99;
               args[index].health = -99;
               args[index].server_sock_id = client_connect(ports[index]);
               // printf("port:%d args[%d].server_sock_id=%d\n", ports[index], index, args[index].server_sock_id);
               sprintf(args[index].message,"GET /healthcheck HTTP/1.1\r\n\r\n");
               strcpy(args[index].response,"");
               //printf("starting server_get_health\n");
               pthread_create(&threads_array[index], NULL, &server_get_health, &args[index]);
               index++; 
        }       

        
        for (j=0; j< maxNumConnections; j++) {
               // printf("saveIndex+j (join) = %d\n", saveIndex+j);
               pthread_join(threads_array[saveIndex+j], NULL);
        }

        for (j=0; j< maxNumConnections; j++) {
               // printf("saveIndex+j (close) = %d\n", saveIndex+j);
               close(args[saveIndex+j].server_sock_id);
        }

    }


    
    for (i=0; i<remain; i++) {
               // printf("index+i (create) = %d\n", index+i);
               args[index+i].port = ports[index+i];
               args[index+i].pmutex = &my_mutex;
               args[index+i].index = i;
               args[index+i].failuresTotal = -99;
               args[index+i].requestsTotal = -99;
               args[index+i].health = -99;
               args[index+i].server_sock_id = client_connect(ports[index+i]);
               // printf("port:%d args[%d].server_sock_id=%d\n",ports[index+i], index+i, args[index+i].server_sock_id);
               sprintf(args[index+i].message,"GET /healthcheck HTTP/1.1\r\n\r\n");
               strcpy(args[index+i].response,"");
               //printf("starting server_get_health\n");
               pthread_create(&threads_array[index+i], NULL, &server_get_health, &args[index+i]);
               // index++; 
    }
    for (i=0; i<remain; i++) {
               // printf("index+i (join) = %d\n", index+i);
               pthread_join(threads_array[index+i], NULL);
    }
    for (i=0; i<remain; i++) {
               // printf("index+i (close) = %d\n", index+i);
               close(args[index+i].server_sock_id);
    }


    // printf("--------threads------------ \n");
    for(i=0; i<numOfPorts; i++) {
        // printf("port = %d    response = %s \n", args[i].port, args[i].response);
    }
    // printf("-------------------- \n");

}

uint16_t findBestPort(ThreadArg args[], int numPorts) {
    int i;
    char buffer[500];
    char *token;
    char *saveptr;
    char *ptr;
    char *sptr;
    int failures, total;

    int port = -1, bestFails = -1, bestTotal = -1;


    // printf("--------findbest------------ \n");
    for(i=0; i<numPorts; i++) {
        // printf("port = %d    response = %s \n", args[i].port, args[i].response);
    }
    // printf("-------------------- \n");
    

    for (i=0; i<numPorts; i++) {

        strncpy(buffer, args[i].response, 500-1);

        // printf("<< buffer = %s>>\n", buffer);

        if (!strstr(buffer, "HTTP/1.1") && strlen(buffer)>0) {
            if (strstr(buffer,"\n")) {
                token = strtok_r(buffer, "\n", &saveptr);
                failures = strtol(token, &ptr, 10);
                // printf("check 1 token = <%s>\n", token);
                // printf("errno = %d\n", errno);
                // if (errno == 0) {
                args[i].failuresTotal = failures;
                // }
                token = strtok_r(NULL, "\n", &saveptr);
                total = strtol(token, &ptr, 10);
                // printf("check 2 token = <%s>\n", token);
                // printf("errno = %d\n", errno);
                // if (errno == 0) {
                    args[i].requestsTotal = total;
                // }
            }   
        } else if (strlen(buffer) >0 && strstr(buffer, "HTTP/1.1") && strstr(buffer, "OK")) {
            sptr = strstr(args[i].response,"\r\n\r\n");
            if (sptr != NULL) {
                sptr += 4;
                strncpy(buffer, sptr, 500-1);
                if (strstr(buffer,"\n")) {
                     token = strtok_r(buffer, "\n", &saveptr);
                     failures = strtol(token, &ptr, 10);
                     // printf("check 3 token = <%s>\n", token);
                     // printf("errno = %d\n", errno);
                     // if (errno == 0) {
                         args[i].failuresTotal = failures;
                     // }
                     token = strtok_r(NULL, "\n", &saveptr);
                     total = strtol(token, &ptr, 10);
                     // printf("check 4 token = <%s>\n", token);
                     // printf("errno = %d\n", errno);
                     // if (errno == 0) {
                     args[i].requestsTotal = total;
                     // }
                }   
            }
        }

        // printf("PORT = %d\n", args[i].port);
        // printf("health = %d\n", args[i].health);
        // printf("failures = %d   bestFails = %d\n", args[i].failuresTotal, bestFails);
        // printf("requests = %d   bestTotal = %d\n", args[i].requestsTotal, bestTotal);
        // printf("response = <<%s>>\n\n",args[i].response);
        // printf("------------------------------\n");

        if ((args[i].failuresTotal >= 0) && (args[i].requestsTotal >= 0)) {
            if (i==0) {
                port = args[i].port;
                bestFails = args[i].failuresTotal;
                bestTotal = args[i].requestsTotal;
            } else {
                if (port == -1) {
                      port = args[i].port;
                      bestFails = args[i].failuresTotal;
                      bestTotal = args[i].requestsTotal;
                }
                 else if (args[i].requestsTotal < bestTotal) {
                      port = args[i].port;
                      bestFails = args[i].failuresTotal;
                      bestTotal = args[i].requestsTotal;
                } else if (args[i].requestsTotal == bestTotal) {
                    if (args[i].failuresTotal < bestFails) {
                           port = args[i].port;
                           bestFails = args[i].failuresTotal;
                           bestTotal = args[i].requestsTotal;
                    } 
                }
            }
        } 
    }

    // printf("findBestPort() returns %d\n", port);
    return port;
}


void* server_get_health(void *obj) {

    int retVal;
    char buff[500];
    int  bytes;


    ThreadArg* argsp = (ThreadArg*) obj;


    // char message[500];
    // char buff[500];
    // int  retVal;
    // int  bytes;
    // int  server_sock_id = client_connect(8080);
    // sprintf(message,"GET /healthcheck HTTP/1.1\r\n\r\n");
    // printf("%s <<<<<<<<<<<<<<<<<",message);
    // retVal = send(server_sock_id, message, strlen(message), 0);
    // bytes = recv(server_sock_id, buff, 500 - 1, 0);
    // buff[bytes] = 0; // null terminate
    // printf("<<<<< server_get_health(): bytes=%d received this from server: <%s> >>>>>>>>\n", bytes,buff);
    // close(server_sock_id);
    // strcpy(argsp->response,"buff");
 


    pthread_mutex_lock(argsp->pmutex);
    retVal = send(argsp->server_sock_id, argsp->message, strlen(argsp->message), 0);

    bytes = recv(argsp->server_sock_id, buff, 500 - 1, 0);
    buff[bytes] = 0; // null terminate
    //printf("<<<<< server_get_health(): bytes=%d received this from server: <%s> >>>>>>>>\n", bytes,buff);

    // printf("server_get_health() argsp->index = %d\n",argsp->index);
    argsp->health = argsp->index;
    strcpy(argsp->response,buff);
    pthread_mutex_unlock(argsp->pmutex);

    return NULL;


}

/*
 * client_connect takes a port number and establishes a connection as a client.
 * connectport: port number of server to connect to
 * returns: valid socket if successful, -1 otherwise
 */
int client_connect(uint16_t connectport) {
    int connfd;
    struct sockaddr_in servaddr;

    connfd=socket(AF_INET,SOCK_STREAM,0);
    if (connfd < 0)
        return -1;
    memset(&servaddr, 0, sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(connectport);

    /* For this assignment the IP address can be fixed */
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

    if(connect(connfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
        return -1;
    return connfd;
}

/*
 * server_listen takes a port number and creates a socket to listen on 
 * that port.
 * port: the port number to receive connections
 * returns: valid socket if successful, -1 otherwise
 */
int server_listen(int port) {
    int listenfd;
    int enable = 1;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
        return -1;
    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
        return -1;
    if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof servaddr) < 0)
        return -1;
    if (listen(listenfd, 500) < 0)
        return -1;
    return listenfd;
}

/*
 * bridge_connections send up to 100 bytes from fromfd to tofd
 * fromfd, tofd: valid sockets
 * returns: number of bytes sent, 0 if connection closed, -1 on error
 */
int bridge_connections(int fromfd, int tofd) {
    char recvline[100];
    int n = recv(fromfd, recvline, 100, 0);
    if (n < 0) {
        // printf("connection error receiving\n");
        return -1;
    } else if (n == 0) {
        // printf("receiving connection ended\n");
        return 0;
    }
    recvline[n] = '\0';
    // printf("<<<%s>>>\n", recvline);
    // sleep(1);
    n = send(tofd, recvline, n, 0);
    if (n < 0) {
        // printf("connection error sending\n");
        return -1;
    } else if (n == 0) {
        // printf("sending connection ended\n");
        return 0;
    }
    return n;
}

/*
 * bridge_loop forwards all messages between both sockets until the connection
 * is interrupted. It also prints a message if both channels are idle.
 * sockfd1, sockfd2: valid sockets
 */
void bridge_loop(int sockfd1, int sockfd2) {
    fd_set set;
    struct timeval timeout;

    int fromfd, tofd;
    while(1) {
        // set for select usage must be initialized before each select call
        // set manages which file descriptors are being watched
        FD_ZERO (&set);
        FD_SET (sockfd1, &set);
        FD_SET (sockfd2, &set);

        // same for timeout
        // max time waiting, 5 seconds, 0 microseconds
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

// printf("tic\n");

        // select return the number of file descriptors ready for reading in set
        switch (select(FD_SETSIZE, &set, NULL, NULL, &timeout)) {
            case -1:
                // printf("error during select, exiting\n");
                return;
            case 0:
                // printf("both channels are idle, waiting again\n");
                continue;
            default:
                if (FD_ISSET(sockfd1, &set)) {
                    fromfd = sockfd1;
                    tofd = sockfd2;
                } else if (FD_ISSET(sockfd2, &set)) {
                    fromfd = sockfd2;
                    tofd = sockfd1;
                } else {
                    // printf("this should be unreachable\n");
                    return;
                }
        }
        if (bridge_connections(fromfd, tofd) <= 0)
            return;

        if (FD_ISSET(sockfd1, &set)) {
            // printf("\nfrom client is set\n");


            
        }
        if (FD_ISSET(sockfd2, &set)) {

            // printf("\nfrom server is set\n");
            // return;

            
        }
      


        // added this return to see if it interrupts the flow. It does return before the
        // server's response has been posted. So it has to be done AFTER FD_ISSET(sockfd2, &set)
        // SEE ABOVE.
        // HENCE we have a place to return fromm when X seconds or N requests have occurred
        // This gives us the opportunity to do a server_heath_check before calling this
        // bridge loop in the caller main() loop
        // return;
        // server_get_health(8080);
        // sockfd2 = client_connect(8080);
        
    }
}

int main(int argc,char **argv) {
    //for connections
    int connfd, listenfd, acceptfd;
    uint16_t connectport, listenport;

    // for getopt
    int opt;
    int portnum;
    int requestLimit = 5;
    int requestCounter;
    int connectionLimit = 4;
    int current;
    int duplicate = 0;

    int numOfPorts = 0;

    clock_t begin;
    clock_t end;
    double  interval;
    double  waitTime = 1.0;

    char    errorMessage[500];

    int i,j;


    if (argc < 3) {
        printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
        return 1;
    }

    // retrieve the -R and -N and port number parameters
    while(1) { 
        opt = getopt(argc, argv, "N:R:");
        if (opt == -1) {break;}
        if (opt == 'R') {
            // printf ("N = <%s>\n", optarg);
            requestLimit = atoi(optarg);
            if (requestLimit== 0) {
                printf("-N must be followed by a valid non-zero int\n");
                printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
                return(-1);
            }

        } else if (opt == 'N') {
            // printf ("logfile is = <%s>\n", optarg);
            connectionLimit = atoi(optarg);
            if (connectionLimit == 0) {
                printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
                return(-1);
            }
        } else {
            printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
            return(-1);
        }   
    }

    // We need to reduce the number of connections by 1 to account for the connection to the client
    connectionLimit--;

    // printf("++++ connectionLimit = %d\n", connectionLimit);
    // printf("++++++++++++ optind=%d argc=%d argv[optind]=%s\n", optind, argc, argv[optind]);

    uint16_t ports[argc - optind];

    // Save remaining parameters in ports[] but ignore duplicates
    // also if atoi retuens 0 on any of them return -1 and exit
   // for (i=0; i < argc-optind; i++) {
   //     current = atoi(argv[i+optind]);
   //     if (current == 0) {
   //         printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
   //         return(-1);
   //     }
   //     if (i>0) {
   //         for (j=0; j<i; j++) {
   //             if (ports[j] == current) {
   //                 duplicate = 1;
   //             }
   //         }
   //     }
   //     if (duplicate != 1) {
   //          ports[i] = atoi(argv[i+optind]);
   //          printf("%d  argv[%d]\n",ports[i],i);
   //          if (ports[i] == 0) {
   //              printf("port numbers must be valid non-zero integers\n");
   //              printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
   //              return(-1);
   //          }
   //          numOfPorts++;
   //     }
   //     duplicate = 0;
   //    
   // }


    listenport = atoi(argv[optind]);
    if (listenport == 0) {
        printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
        return(-1);
    }

    for (i=0; i < argc-optind-1; i++) {
        
        ports[i] = atoi(argv[i+optind+1]);
        // printf("ports[%d] = %d\n",i, ports[i]);
        if (ports[i] == 0) {
            printf("port numbers must be valid non-zero integers\n");
            printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
            return(-1);
        }
        numOfPorts++;

       
    }


    if (numOfPorts == 0) {
        printf("port numbers must be valid non-zero integers\n");
        printf("Usage: loadbalancer <port_number1, port_number2, ...> [-N <number of connections>] [-R <number of requests>]\n");
        return(-1);

    }

    // printf("<<<<<<<<<< number of ports = %d >>>>>>>\n", numOfPorts);
    for (i=0; i< numOfPorts; i++) {
        // printf("%d \n",ports[i]);
    }
    // printf("<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>\n");

    ThreadArg args[numOfPorts];
    
    // connectport = atoi(argv[1]);  // port where httpserver is running on
    // listenport = atoi(argv[2]);   // port that curl uses

    // connectport = ports[1];     // port where httpserver is running on
    // listenport  = ports[0];     // port that curl uses

    
    threadsOfHealthCheckers(args, ports, numOfPorts, connectionLimit);
    connectport = findBestPort(args, numOfPorts);
    // printf("========> connectionLimit = %d \n", connectionLimit);
    // printf("========>    requestLimit = %d \n", requestLimit);

    // printf("connectport = %d     listenport = %d \n",connectport, listenport);

    // this is not the place for this call - just checking feasability right now 
    // server_get_health(connectport);
    
    begin = clock();
    while (1) {


        //printf("top of loop:  begin = %lu    end=%lu\n", begin, end);

        
        if ((listenfd = server_listen(listenport)) < 0)
             err(1, "failed listening");
        if ((acceptfd = accept(listenfd, NULL, NULL)) < 0)
             err(1, "failed accepting");

        requestCounter++;
        end = clock();
        interval = (double)(end - begin)/CLOCKS_PER_SEC;

        // printf("interval = %f\n", interval);

        // if (interval >= .0004) {
        //     //printf("============ beep\n");
        //     begin = end;
        // }

        // if (interval >= 1) {
        //     printf("interval = %f", interval);
        // }

        // check for time and check for number of requests
        // if either one has expired refresh the best port
        // otherwise the port remains the same and 
        if ((requestCounter >= requestLimit) || (interval >= 0.0004)) {

               requestCounter = 0;
               begin = end;
               threadsOfHealthCheckers(args, ports, numOfPorts, connectionLimit);
               connectport = findBestPort(args, numOfPorts);

        }

        

        // -1 is 65535 in an unsigned integer
        if (connectport != 65535) {
        
             connfd = client_connect(connectport);

             // if port connect port is down in the interim, we have to 
             // find a good port
             if (connfd == -1) {
                threadsOfHealthCheckers(args, ports, numOfPorts, connectionLimit);
                connectport = findBestPort(args, numOfPorts);
                connfd = client_connect(connectport);
             }
     
             // This is a sample on how to bridge connections.
             // Modify as needed.
             if (connfd != -1) {
                  bridge_loop(acceptfd, connfd);
             } else {
                  // printf("no valid servers found. Sending error 500 to client\n");
                  sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
                  send(acceptfd, errorMessage, strlen(errorMessage), 0);
             }
        } else {
            // printf(" -- no valid servers found. Sending error 500 to client\n");
            sprintf(errorMessage, "\nHTTP/1.1 %d %s\r\nContent-Length: %d\r\n\r\n", 500, "Internal Server Error", 0);
            send(acceptfd, errorMessage, strlen(errorMessage), 0);
        }
       


         close(listenfd);
         close(acceptfd);
         close(connfd);
        
         // end = clock();

         // printf("bottom of loop \n");
         
         
    }
    
}
