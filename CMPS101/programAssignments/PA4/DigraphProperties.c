//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA4
//---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Digraph.h"
#include "List.h"

#define MAX_LEN 20000

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
   char *param3;
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

         param1 = strtok(NULL, " ,\n\r\t");
         if(param1 != NULL){
            fprintf(out, "PrintDigraph %s\n", param1);
            fprintf(out, "ERROR\n");
         }
         else{
            printDigraph(out, myDigraph);
         }
      }
      else if(!strcmp(token, "ReversePrintDigraph")){
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

         reversePrintDigraph(out, myDigraph);
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

         param1 = strtok(NULL, " ,\n\r\t");
         if(param1 != NULL){
            fprintf(out, "GetSize %s\n", param1);
            fprintf(out, "ERROR\n");
         }
         else{
            fprintf(out, "GetSize\n%d\n", getSize(myDigraph));
         }  
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
         // check for extra parameters
         param2 = strtok(NULL, " ,\n\r\t");
         if (param1 == NULL) {
            fprintf(out, "GetOutDegree\n");
            fprintf(out, "ERROR\n");
         }
         else if(param2 != NULL){
            fprintf(out, "GetOutDegree %s %s\n", param1, param2);
            fprintf(out, "ERROR\n");
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
         // checking for extra parameter
         param3 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }
         if (param3 != NULL) {
            fprintf(out, " %s", param3);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to AddEdge so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL || param3 != NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the AddEdge method
            returnVal = addEdge(myDigraph, atoi(param1), atoi(param2));
            if(returnVal == 0){
               reverseAddEdge(myDigraph, atoi(param2), atoi(param1));
               // if the SCC data structure has been allocated, free it
               // because we just changed the digraph
               if(myDigraph->SCCFlag == 1){
                  freeSCC(myDigraph);
               }
               
               fprintf(out, "%d\n", returnVal);
            }
            else if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", returnVal);
            }
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
         // checking for extra parameter
         param3 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }
         if (param3 != NULL) {
            fprintf(out, " %s", param3);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to DeleteEdge so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL || param3 != NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the DeleteEdge method
            returnVal = deleteEdge(myDigraph, atoi(param1), atoi(param2));
            if(returnVal == 0){
               reverseDeleteEdge(myDigraph, atoi(param2), atoi(param1));
               // if the SCC data structure has been allocated, free it
               // because we just changed the digraph
               if(myDigraph->SCCFlag == 1){
                  freeSCC(myDigraph);
               }
               
               fprintf(out, "%d\n", returnVal);
            }
            else if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", returnVal);
            }
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
         
         // check for extra parameter
         param1 = strtok(NULL, " ,\n\r\t");

         if (param1 != NULL) {
            fprintf(out, "GetOrder %s\n", param1);
            fprintf(out, "ERROR\n");
         }
         else{
            fprintf(out, "GetOrder\n%d\n", getOrder(myDigraph));
         }
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
         // checking for extra parameter
         param3 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }
         if (param3 != NULL) {
            fprintf(out, " %s", param3);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to Distance so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL || param3 != NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the Distance method
            distance(out, myDigraph, atoi(param1), atoi(param2));
         }
      }
      else if(!strcmp(token, "GetCountSCC")){

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

         if (param1 != NULL) {
            fprintf(out, "GetCountSCC %s\n", param1);
            fprintf(out, "ERROR\n");
         }
         else{
            fprintf(out, "GetCountSCC\n%d\n", getCountSCC(myDigraph));
         }
      }
      else if(!strcmp(token, "GetNumSCCVertices")){

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
         // check for extra parameter
         param2 = strtok(NULL, " ,\n\r\t");

         if (param1 == NULL) {
            fprintf(out, "GetNumSCCVertices\n");
            fprintf(out, "ERROR\n");
         }
         else if(param2 != NULL){
            fprintf(out, "GetNumSCCVertices %s %s\n", param1, param2);
            fprintf(out, "ERROR\n");
         }
         else{
            fprintf(out, "GetNumSCCVertices %s\n", param1);

            returnVal = getNumSCCVertices(myDigraph, atoi(param1));
            if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
            else{
               fprintf(out, "%d\n", returnVal);
            }
         }
      }
      else if(!strcmp(token, "InSameSCC")){

         if(myDigraph == NULL){
            //printf("ERROR: Commands should not proceed the description of the Digraph\n");
            fprintf(out, "%s\n", token);
            fprintf(out, "ERROR\n");
            /* close files */
            fclose(in);
            fclose(out);
            exit(1);
         }

         // Write token which is inSameSCC to the output file
         fprintf(out, "%s", token);

         param1 = strtok(NULL, " ,\n\r\t");
         param2 = strtok(NULL, " ,\n\r\t");
         // checking for extra parameter
         param3 = strtok(NULL, " ,\n\r\t");

         // Write the parameters, if not null, to the output file
         if (param1 != NULL) {
            fprintf(out, " %s", param1);
         }
         if (param2 != NULL) {
            fprintf(out, " %s", param2);
         }
         if (param3 != NULL) {
            fprintf(out, " %s", param3);
         }

         // write a carriage return to the output file
         fprintf(out,"\n");

         // Ok, now let's do some error checking.
         // We expect two parameters to inSameSCC so let's make sure
         // they were provided in the input file

         if (param1 == NULL ||  param2 == NULL || param3 != NULL) {
            fprintf(out, "ERROR\n");
         } else {
            // seems like 2 parameters were provided in the input file
            // we are ready to call the inSameSCC method
            returnVal = inSameSCC(myDigraph, atoi(param1), atoi(param2));
            if(returnVal == 1){
               fprintf(out, "YES\n");
            }
            else if(returnVal == 0){
               fprintf(out, "NO\n");
            }
            else if(returnVal == -1){
               fprintf(out, "ERROR\n");
            }
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
                  reverseAddEdge(myDigraph, atoi(vB), atoi(vA));

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

// REMEMBER TO UNVISIT ALL BEFORE CALLING THIS
void ReverseDepthFirstSearch(Digraph G, Stack S, int w){

   Node curr;

   G->visitStatus[w] = INPROGRESS;

   for(curr = G->reverseAdjacencyList[w]; curr != NULL; curr = curr->next){
      //printf("Vertex %d visit status %d\n", curr->data, G->visitStatus[curr->data]);
      if(G->visitStatus[curr->data] == UNVISITED){
         //printf("Vertex %d index %d.\n", curr->data, G->SCCIndex);
         ReverseDepthFirstSearch(G, S, curr->data);
      }
   }
   
   G->visitStatus[w] = ALLDONE;

   //printf("Vertex %d index %d\n", w, G->SCCIndex);
   insertNodeSCCArray(G, w);
   push(S,w);

   return;
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

int getNextVertexWithLargestFinishTime(int myArray[], int numVertices){
   int i;
   int max = 0;
   int maxIndex;
    for(i = 1; i <= numVertices; i++){
      if(myArray[i] > max){
         max = myArray[i];
         maxIndex = i;
      }
      //printf("%d\n", myArray[i]);
    }
    //printf("Max = %d at index %d\n", max, maxIndex);
    return(maxIndex);
}

void setupSCC(Digraph G){

   int i;
   int myCurrTime;
   int myArray[MAX_LEN];
   int vertexWithLargestFinishTime;
           
            // set the SCCFlag to 1
            G->SCCFlag = 1;
  
            // reset SCCIndex and NULL out the SCCArray
            G->SCCIndex = 0;
            for(i = 0; i < MAX_ARRAY_SIZE; i++){   
               G->SCCArray[i] = NULL;
            }


            // CALL REVERSE DFS TO SET UP THE SCC ARRAY? 
            // BUT DO WE CALL REVERSE DFS WITH THE VERTEX WITH THE BIGGEST 
            // FINISH TIME? OR THE VERTEX WITH THE BIGGEST FINISH TIME 
            // WHO IS ALSO UNVISITED? 

            Stack SCCStack = newStack();
            unvisitAll(G);
            
            // Call the first DFS with all univisited vertices
            // This should generate a finish time array that we can use later
            myCurrTime = 0;
            for(i = 1; i <= G->numVertices; i++){
               if(G->visitStatus[i] == UNVISITED){
                  myCurrTime = DepthFirstSearch(G, SCCStack, i, myCurrTime);
               }
            }
            
            // Initialze myArray to all zeros
            for(i = 0; i < G->numVertices; i++){
                myArray[i] = 0;
            }

            // Copy finishTime to myArray
            // Making a copy of the finish time array because we do not want to mess
            // with the original
            for(i = 1; i <= G->numVertices; i++){
                myArray[i] = G->finishTime[i];
                //printf("myArray[%d] = %d\n", i, myArray[i]);
            }

            unvisitAll(G);

            G->SCCIndex = 0;
            for(i = 1; i <= G->numVertices; i++){
               vertexWithLargestFinishTime = getNextVertexWithLargestFinishTime(myArray, G->numVertices);
               //printf("Vertex with largest finish time is %d\n", vertexWithLargestFinishTime);
               if(G->visitStatus[vertexWithLargestFinishTime] == UNVISITED){
                  ReverseDepthFirstSearch(G, SCCStack, vertexWithLargestFinishTime);
                  G->SCCIndex++;
               }
               myArray[vertexWithLargestFinishTime] = 0;

               
            }
            freeStack(&SCCStack);
}
