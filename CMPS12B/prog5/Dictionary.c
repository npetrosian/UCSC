//-----------------------------------------------------------------------------
// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// Dictionary.c
// Hash Table implementation of the Dictionary ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

const int tableSize=101; // or some prime other than 101

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift);

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input);

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key);

// private types and functions ------------------------------------------------

// NodeObj
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor for private Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for private Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// DictionaryObj
typedef struct DictionaryObj{
   Node* table;
   int numPairs;
} DictionaryObj;


// findKey()
// returns the Node containing key k in the hash table, or returns
// NULL if no such Node exists
Node findKey(Dictionary D, char* k){
   int i;
   Node curr;
   for(i = 0; i < tableSize; i++){
      if(D->table[i] != NULL){
         curr = D->table[i];
         if( strcmp(curr->key, k) == 0){
            return (curr);
         }
      }
   }
   return (NULL);
}

// printInOrder()
// prints the (key, value) pairs belonging to the hash table to 
// file pointed to by out.
void printInOrder(FILE* out, Dictionary D){
   int i;
   Node curr;
   for(i = 0; i < tableSize; i++){
      if(D->table[i] != NULL){
         curr = D->table[i];
         while(curr != NULL){
            fprintf(out, "%s %s\n", curr->key, curr->value);
            curr = curr->next;
         }
      }
   }    
}

// deleteAll()
// deletes all Nodes in the hash table.
void deleteAll(Dictionary D){
   int i;
   Node curr;
   for(i = 0; i < tableSize; i++){
      while(D->table[i] != NULL){
         curr = D->table[i];
         D->table[i] = curr->next;
         freeNode(&curr);
         curr = NULL;
      }
   }

   D->numPairs = 0;
}




// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}

// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);

   D->table = calloc(tableSize, sizeof(Node));

   for(int i = 0; i < tableSize; i++){
      D->table[i] = NULL;
   }

   D->numPairs = 0;
   return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free((*pD)->table); // free the table that we allocated earlier
      free(*pD);
      *pD = NULL;
   }
}

// isEmpty()
// returns 1 (true) if D is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numPairs==0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numPairs);
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k){
   Node N;
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   int index = hash(k);

   N = D->table[index];

   for(Node curr = N; curr != NULL; curr = curr->next){
       if(curr->key == k){
           return curr->value; 
       }
   }

   return (NULL);

}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
   Node N;
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling insert() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   if( findKey(D, k)!=NULL ){
      fprintf(stderr, 
         "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
      exit(EXIT_FAILURE);
   }

   // creating a node given the key and value
   N = newNode(k, v);


   int index = hash(k);

   if(D->table[index] == NULL){
       D->table[index] = N; 
   }
   else{
      N->next = D->table[index];
      D->table[index] = N;
   }

   D->numPairs++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
   Node N;
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   N = findKey(D, k);

   if( N==NULL ){
      fprintf(stderr, 
         "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
      exit(EXIT_FAILURE);
   }

   int index = hash(k);

   if(N == D->table[index]){ // If N is the first Node at the index of the table
      if(N->next == NULL){
         D->table[index] = NULL;
         freeNode(&N);
      }
      else{
         D->table[index] = N->next;
         freeNode(&N);
      }
   }
   else{ // If N is NOT the first Node at the index of the table
      for(Node curr = D->table[index]; curr !=NULL; curr = curr->next){
          if(N == curr->next){
             curr->next = curr->next->next;
             freeNode(&N);
          }
      }
   }

   D->numPairs--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){
   deleteAll(D);
   D->numPairs = 0;
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling printDictionary() on NULL"
         " Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   printInOrder(out, D);
}


