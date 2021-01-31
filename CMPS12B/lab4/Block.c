//-----------------------------------------------------------------------------
// File name: Block.c
// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// This file contains the private data definitions for a Block object and the 
// definitions of the public methods that access the private data.
// A brief description precedes each method in this file.
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Block.h"

// private types-----------------------------------
// BlockObj
typedef struct BlockObj{
   char* data;
   int id;
   long hash;
} BlockObj;


// Public methods

// newBlock()
// constructor of the Block Type
Block newBlock(char* data, int id, long hash){
   Block B = malloc(sizeof(BlockObj));
   assert(B!=NULL);
   B->data = data;
   B->id = id;
   B->hash = hash;
   return(B);

}

// freeBlock()
// destructor for the Block type
void freeBlock(Block* pB){
   if( pB!=NULL && *pB!=NULL ){
      free(*pB);
      *pB = NULL;
   }
}

// return a pointer to this block's data.
// It would probably be better to return a copy to avoid, easy erroneous manipulation of blocks,
// but for demonstration purposes we are going to expose the actual block data.
char* data(Block B){
   return B->data;
}

// return the stored previousHash from this block
long previousHash(Block B){
   return B->hash;
}

// recompute the hash value for this block
long hash(Block B){
   long hashValue=0;
   int i;

   for(i = 0; i < strlen(B->data); i++){
        hashValue += B->data[i];
   }
   hashValue += B->id;
   hashValue += B->hash;
   return(hashValue);
}

// print the block id and data
// (NOTE: for debugging purposes you may want to have it also print the hash and previousHash values during development.)
void printBlock(FILE* out, Block B){
   if (B == NULL) {
       fprintf(stderr, "Block Error: printBlock() called on NULL Block reference\n");
       exit(EXIT_FAILURE);
   }
   fprintf(out, "%d:%s\n", B->id, B->data);
}
















