//-----------------------------------------------------------------------------
// File name: Blockchain.c
// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// This file contains the private data definitions for a Blockchain object and the 
//  definitions of the public methods that access the private data.
// A brief description precedes each method in this file.
//-----------------------------------------------------------------------------



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Blockchain.h"
#include"Block.h"

// private types-----------------------------------
// BlockchainObj

#define FIXED_ARRAY_SIZE 100

typedef struct BlockchainObj{
   Block chain[FIXED_ARRAY_SIZE];
   int size;
} BlockchainObj;

// constructor for the Blockchain type
Blockchain newBlockchain(){
	Blockchain BC = malloc(sizeof(BlockchainObj));
	assert(BC!=NULL);
	BC->size = 0;
        return(BC);
}

// destructor for the Blockchain type
void freeBlockchain(Blockchain* pBC){
   if( pBC!=NULL && *pBC!=NULL ){
      int  i;
      int numBlocksToFree = (*pBC)->size;
      // printf("Size: %d\n",(*pBC)->size);
      for (i=0; i<numBlocksToFree; i++) {
          free ((*pBC)->chain[i]);
      }
      free(*pBC);
      *pBC = NULL;
   }
}

// append a new block to the chain with the data specified in the new block
// return the size of the block chain if successful and 0 otherwise
int append(Blockchain BC, char* data){

     if (BC == NULL || data == NULL) {
        return (0);
     }

     // Don't append to an invalid chain
     // If BC isn't valid return a fail
     if (valid(BC) == 0) {
        return(0);
     }

     long previousHash;
     int id;
     Block b;
     if(BC->size == 0){
         previousHash = 0;
     }
     else{
         previousHash = hash(BC->chain[BC->size-1]);
     }
     id = BC->size;
     b = newBlock(data, id, previousHash);
     BC->chain[BC->size] = b;
     BC->size = BC->size+1;
     return(BC->size);

}

// return the number of blocks in this chain
int size(Blockchain BC){
	return(BC->size);
}

// return the block at index idx in the chain
Block get(Blockchain BC, int idx){
    return (BC->chain[idx]);
}

// check if this is a valid chain by checking the stored previousHash values in each block
// return 1 if valid, 0 otherwise
int valid(Blockchain BC){
       int index;
       long hash1;
       long hash2;
       Block b;

       if (BC == NULL) {
          return(0);
       }


      // this for loop stops one short of the last entry 
      // chain so there will always be room to refer to
      // index+1
      //
      // Go through all of the Blocks in the chain and
      // see if their previously stored hash value is 
      // different from the new computation of their
      // hash. If not the same, we've been hacked

      for (index=0; index < size(BC)-1; index++) {

            // get the Blocks at current index
            b = get(BC, index);
            // recompute the Block's hash
            hash1 = hash(b);

            // get the next block's previously stored hash
            b = get(BC, index+1);
            hash2 = previousHash(b);
            // printf("hash1=%ld  hash2=%ld\n",hash1, hash2);
            // the two hash values should match
            // or else we've been hacked
            if (hash1 != hash2) {
                return(0);
            }
       }
       // if still here all went well
       return(1);
}

// shorten the chain by removing the last block
// do nothing if the chain is already empty
void removeLast(Blockchain BC){
    free(BC->chain[BC->size - 1]);
    BC->size = BC->size -1;
}

// print the chain
void printBlockchain(FILE* out, Blockchain BC){
   int index;
   if (BC == NULL) {
       fprintf(stderr, "Blockchain Error: printBlockchain() called on NULL Block reference\n");
       exit(EXIT_FAILURE);
   }
   // fprintf(out, "%d\n", BC->size);
   for (index = 0; index < BC->size; index++) {
        printBlock(out, BC->chain[index]);
   }
    
}



