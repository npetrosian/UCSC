//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA3
//---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Digraph.h"
#include "List.h"
#include "Stack.h"

#define MAX_LEN 512

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   int numVertices;
   char vA[10]; 
   char vB[10];
   Digraph myDigraph = NULL;
   int returnVal;
   char *param1;
   char *param2;
   int w;

   // DEBUG
   // Node curr;

   bool DFSTestAcyclic(Digraph G, int w);

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   while( fgets(line, MAX_LEN, in) != NULL)  {

      // no legitimate input line should be less than 2 characeters
      // if we encounter one, skip the line and go to the top of the while and read another line
      if (strlen(line)< 2) {
         continue;
      }

      // Get the first token in the line read from the input file
      // This would either be one of the commands or the first line of
      // the input file with vertices and edges.
      // strtok() is being used with space, carriage return, linefeed
      // and tab as separators.
      token = strtok(line, " ,\n\r\t");

      // Now determine what the first token from the input file is
      // and proceed accordingly
      
      if(!strcmp(token, "PrintDigraph")){
         //printf("do a printDigraph!\n");

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         printDigraph(out, myDigraph);
      }
      else if(!strcmp(token, "TopoSort")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         unvisitAll(myDigraph);

         // Grab a vertex from the adjacency array
         for(w = 1; w <= myDigraph->numVertices; w++){
            if(myDigraph->adjacencyList[w] != NULL){
                break;
            }
         }

         if(DFSTestAcyclic(myDigraph, w) == true){
            // printf("DFSTestAcyclic returned true!\n");
            fprintf(out, "TopoSort\n");
            fprintf(out, "IMPOSSIBLE\n");

         }
         else{
            // printf("DFSTestAcyclic returned false!\n");
            topoSort(out, myDigraph);
         }
      }
      else if(!strcmp(token, "GetSize")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         fprintf(out, "GetSize\n%d\n", getSize(myDigraph));
      }
      else if(!strcmp(token, "GetOutDegree")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         param1 = strtok(NULL, " ,\n\r\t");
         if (param1 == NULL) {
            fprintf(out, "GetOutDegree\n");
         }
         else{
            fprintf(out, "GetOutDegree %s\n", param1);

            returnVal = getOutDegree(myDigraph, atoi(param1));
            if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", returnVal);
            }
         }
      }
      else if(!strcmp(token, "PathExists")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }
         
         // Write token which is PathExists to the output file
         fprintf(out, "%s", token);

         // make two calls to strtok expecting two more parameters
         param1 = strtok(NULL, " ,\n\r\t");
         param2 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to PathExists so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the PathExists method
            PathExists(out, myDigraph, atoi(param1), atoi(param2));
         }

   
      }

      else if(!strcmp(token, "AddEdge")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }
         
         // Write token which is AddEdge to the output file
         fprintf(out, "%s", token);

         // make two calls to strtok expecting two more parameters
         param1 = strtok(NULL, " ,\n\r\t");
         param2 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to AddEdge so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the AddEdge method
            returnVal = addEdge(myDigraph, atoi(param1), atoi(param2));
            fprintf(out, "%d\n", returnVal);
         }


   
      }

      else if(!strcmp(token, "DeleteEdge")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }
         
         // Write token which is DeleteEdge to the output file
         fprintf(out, "%s", token);

         // make two calls to strtok expecting two more parameters
         param1 = strtok(NULL, " ,\n\r\t");
         param2 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to DeleteEdge so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the DeleteEdge method
            returnVal = deleteEdge(myDigraph, atoi(param1), atoi(param2));
            fprintf(out, "%d\n", returnVal);
         }

   
      }
      else if(!strcmp(token, "GetNeighborCount")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         token = strtok(NULL, ",\n,\t,\r");
         fprintf(out, "GetNeighborCount %s\n", token);
         if(token == NULL){
            fprintf(out, "ERROR\n");
         }
         else{
            returnVal = getNeighborCount(myDigraph, atoi(token));
            if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", getNeighborCount(myDigraph, atoi(token)));
            }
         }
      }
      else if(!strcmp(token, "GetOrder")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         fprintf(out, "GetOrder\n%d\n", getOrder(myDigraph));
      }
      else if(!strcmp(token, "Acyclic")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         fprintf(out, "Acyclic\n");
         acyclic(out, myDigraph);
      }
      else if(!strcmp(token, "Distance")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         // Write token which is Distance to the output file
         fprintf(out, "%s", token);

         param1 = strtok(NULL, " ,\n\r\t");
         param2 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to Distance so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the Distance method
            distance(out, myDigraph, atoi(param1), atoi(param2));
         }
      }
      else if ((token != NULL)  &&  strspn(token,"0123456789, ")) {
            numVertices = atoi(token);

            // if number of vertices is less than 1, print the line followed by "ERROR"
            if(numVertices < 1){
               
               fprintf(out, "%s,", token);
               token = strtok(NULL, "\n,\t,\r");
               while (token != NULL) {
                  fprintf(out, "%s", token);
                  token = strtok(NULL, "\n,\t,\r");
                  if (token != NULL) {
                     fprintf(out, ",");
                  }
               }

               fprintf(out, "\nERROR\n");
               fclose(in);
               fclose(out);
               exit(1);
            }

            // Create a new graph
            myDigraph = newDigraph(numVertices);
            
            while( token!=NULL ){

               token = strtok(NULL, ",\n,\t,\r");
               if(token != NULL){
                  sscanf(token, "%s %s", vA, vB);

                  if(atoi(vA) > myDigraph->numVertices || atoi(vB) > myDigraph->numVertices || atoi(vA) < 1 || atoi(vB) < 1){
                     fprintf(out, "%d,%s\n",myDigraph->numVertices, token);
                     fprintf(out, "ERROR\n");
                     /* close files */
                     fclose(in);
                     fclose(out);
                     // free the graph
                     freeDigraph(&myDigraph);
                     exit(1);
                  }

                  addEdge(myDigraph, atoi(vA), atoi(vB));

                  
                  // DEBUG
                  // Print the adjacency array from front to
                  // back and back to front to make sure that
                  // the prev and next pointers have been set
                  // properly
                  // printf("1111111111111111111111111111\n");
                  // curr = myDigraph->adjacencyList[atoi(vA)];
                  // while (curr->next != NULL) {
                  //      printf("curr-data = %d\n", curr->data);
                  //      curr = curr->next;
                  // }
                  // printf("curr->data = %d\n", curr->data);
                  // printf("22222222222222222222222222222\n");
                  // while (curr != NULL) {
                  //     printf("curr-data = %d\n", curr->data);
                  //     curr = curr->prev;
                  // }
                  // DEBUG
                  

               }
            }

            

      } else {
         // printf("GARBAGE detected in input file - <%s> \n", token);
         fprintf(out,"%s\n",line);
         fprintf(out,"ERROR\n");
      }

      
   }

   // free the graph
   freeDigraph(&myDigraph);

   /* close files */
   fclose(in);
   fclose(out);

   // need to free that last newList() before the big while loop ended 
   //freeDigraph(&myDigraph);

   return(0);
}

int DepthFirstSearch(Digraph G, Stack S, int w, int currentTime){

   int currTime = currentTime;
   Node curr;

   G->entryTime[w] = currentTime;
   currTime++; 
   G->visitStatus[w] = INPROGRESS;

   for(curr = G->adjacencyList[w]; curr != NULL; curr = curr->next){
      if(G->visitStatus[curr->data] == UNVISITED){
         currTime = DepthFirstSearch(G, S, curr->data, currTime);
         currTime++;
      }
   }
   
   G->finishTime[w] = currTime;
   G->visitStatus[w] = ALLDONE;
   push(S,w);
   // printf("w = %d G->entryTime[w] = %d G->finishTime[w] = %d\n", w, G->entryTime[w], G->finishTime[w]);

   return (currTime);
}

bool DFSTestAcyclic(Digraph G, int w){
   Node curr;

   G->visitStatus[w] = INPROGRESS;
   for(curr = G->adjacencyList[w]; curr != NULL; curr = curr->next){ //getNextNode(curr)
      if(getMark(G, curr->data) == INPROGRESS){
         return(true);
      }
      if (DFSTestAcyclic(G, curr->data)){
         return(true);
      }
   }
   setMark(G, w, ALLDONE);
   return(false);
}
