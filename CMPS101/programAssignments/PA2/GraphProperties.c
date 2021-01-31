//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA2
//---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 512

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   int numVertices;
   char vA[10]; 
   char vB[10];
   Graph myGraph;
   int returnVal;
   char *param1;
   char *param2;

   void PathExists(FILE* out, Graph G, int u, int v);

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

      if(!strcmp(token, "PrintGraph")){
         //printf("do a printGraph!\n");
         printGraph(out, myGraph);
      }
      else if(!strcmp(token, "GetSize")){
         fprintf(out, "GetSize\n%d\n", getSize(myGraph));
      }
      else if(!strcmp(token, "PathExists")){
         
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
            PathExists(out, myGraph, atoi(param1), atoi(param2));
         }

   
      }
      else if(!strcmp(token, "GetNeighborCount")){
         token = strtok(NULL, ",\n,\t,\r");
         fprintf(out, "GetNeighborCount %s\n", token);
         if(token == NULL){
            fprintf(out, "ERROR\n");
         }
         else{
            returnVal = getNeighborCount(myGraph, atoi(token));
            if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", getNeighborCount(myGraph, atoi(token)));
            }
         }
      }
      else if(!strcmp(token, "GetOrder")){
         fprintf(out, "GetOrder\n%d\n", getOrder(myGraph));
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
            myGraph = newGraph(numVertices);
            
            while( token!=NULL ){

               token = strtok(NULL, ",\n,\t,\r");
               if(token != NULL){
                  sscanf(token, "%s %s", vA, vB);

                  addEdge(myGraph, atoi(vA), atoi(vB));

               }
            }

            

      } else {
         // printf("GARBAGE detected in input file - <%s> \n", token);
         fprintf(out,"%s\n",token);
         fprintf(out,"ERROR\n");
      }

      
   }

   // free the graph
   freeGraph(&myGraph);

   /* close files */
   fclose(in);
   fclose(out);

   // need to free that last newList() before the big while loop ended 
   //freeGraph(&myGraph);

   return(0);
}

void PathExists(FILE* out, Graph G, int u, int v){

   int theFoundValue;

   unvisitAll(G); // No vertices have been visited yet
   theFoundValue = PathExistsRecursive(G, u, v);
   if(theFoundValue == FOUND){
      fprintf(out, "YES\n");
   }
   else{
      fprintf(out, "NO\n");
   }
}


