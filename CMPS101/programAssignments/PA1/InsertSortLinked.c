//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA1
//---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 512

void insertionSort(List L);

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   List myList;

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

   // Create a new empty list
   myList = newList();  

   while( fgets(line, MAX_LEN, in) != NULL)  {

      token = strtok(line, " ,\n,\t,\r");
      
      while( token!=NULL ){
                
         append(myList, atoi(token));
         token = strtok(NULL, " ,\n,\t,\r");
      }

      insertionSort(myList);
      printList(out, myList);
      fprintf(out, "\n");

      // Completed for one line from the input file.
      // Free the list and start all prepare for next line
      freeList(&myList);
      myList = newList();
     
      
   }

   /* close files */
   fclose(in);
   fclose(out);

   // need to free that last newList() before the big while loop ended 
   freeList(&myList);

   return(0);
}

void insertionSort(List L){
    Node keyNode;
    Node checkNode;
    int keyVal; 
    int checkVal;
    // If head and tail are both NULL (empty list), 
    // or if they are both pointing to the same Node (one item list)
    // return, because there is nothing to sort. 
    if(L->head == L->tail){
        return;
    }

    // Initialize keyNode to the second Node, and checkNode to the first
    keyNode = L->head->next;

    while(keyNode != NULL){

        keyVal = getValue(keyNode);
        checkNode = keyNode->prev;
        checkVal = getValue(checkNode);

        while(checkNode != NULL && checkVal > keyVal){
            
            // printf("checkNode = %p \n", checkNode);
            checkNode = checkNode->prev;

            // we might reach the head of the list for some 
            // cases so we need to check for NULL
            if(checkNode != NULL){
                checkVal = getValue(checkNode);
            }

        }

        // checkNode at this point is either a NULL or pointing to a node 
        // that we need to insert keyNode after. 
        if (checkNode != NULL) {
            // we found a node with a checkval smaller than or equal to keyVal
            // dance
            deleteNode(L, keyNode);
            insertAfter(L, checkNode, keyVal);
        }
        if (checkNode == NULL) {
            // we found nothing smaller than or equal to keyVal
            // so insert keyVal BEFORE the head 
            deleteNode(L, keyNode);
            insertBefore(L, L->head, keyVal);
        }           
        

        keyNode = keyNode->next;
    }
    return;
}

