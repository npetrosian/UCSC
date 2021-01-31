//-----------------------------------------------------------------------------
// Blockchain.h
// Header file for the Blockchain ADT
//-----------------------------------------------------------------------------

#ifndef _BLOCKCHAIN_H_INCLUDE_
#define _BLOCKCHAIN_H_INCLUDE_

#include "Block.h"

// Exported reference type
typedef struct BlockchainObj* Blockchain;

// constructor for the Blockchain type
Blockchain newBlockchain();

// destructor for the Blockchain type
void freeBlockchain(Blockchain* pB);

// append a new block to the chain with the data specified in the new block
// return the size of the block chain if successful and 0 otherwise
int append(Blockchain B, char* data);

// return the number of blocks in this chain
int size(Blockchain B);

// return the block at index idx in the chain
Block get(Blockchain B, int idx);

// check if this is a valid chain by checking the stored previousHash values in each block
// return 1 if valid, 0 otherwise
int valid(Blockchain B);

// shorten the chain by revmoing the last block
// do nothing if the chain is already empty
void removeLast(Blockchain B);

// print the chain
void printBlockchain(FILE* out, Blockchain B);

#endif
