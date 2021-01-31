//-----------------------------------------------------------------------------
// Queue.c
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Queue.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct QueueObj{
   Node front;
   Node back;
   int length;
} QueueObj;


// Constructors-Destructors ---------------------------------------------------

// queueNewNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node queueNewNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   return(N);
}

// queueFreeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void queueFreeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newQueue()
// Returns reference to new empty Queue object.
Queue newQueue(void){
   Queue Q;
   Q = malloc(sizeof(QueueObj));
   Q->front = Q->back = NULL;
   Q->length = 0;
   return(Q);
}


// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeQueue(Queue* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      while( !queueIsEmpty(*pQ) ) { 
         Dequeue(*pQ); 
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------

// queueGetFront()
// Returns the value at the front of Q.
// Pre: !queueIsEmpty(Q)
int queueGetFront(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling queueGetFront() on NULL Queue reference\n");
      exit(1);
   }
   if( queueIsEmpty(Q) ){
      printf("Queue Error: calling queueGetFront() on an empty Queue\n");
      exit(1);
   }
   return(Q->front->data);
}

// getLength()
// Returns the length of Q.
int getLength(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getLength() on NULL Queue reference\n");
      exit(1);
   }
   return(Q->length);
}

// queueIsEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int queueIsEmpty(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling queueIsEmpty() on NULL Queue reference\n");
      exit(1);
   }
   return(Q->length==0);
}


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data element at the end of Q
void Enqueue(Queue Q, int data)
{
   Node N = queueNewNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(1);
   }
   if( queueIsEmpty(Q) ) { 
      Q->front = Q->back = N; 
   }else{ 
      Q->back->next = N; 
      Q->back = N; 
   }
   Q->length++;
}

// Dequeue()
// Deletes element at front of Q
// Pre: !queueIsEmpty(Q)
void Dequeue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
      exit(1);
   }
   if( queueIsEmpty(Q) ){
      printf("Queue Error: calling Dequeue on an empty Queue\n");
      exit(1);
   }
   N = Q->front;
   if( getLength(Q)>1 ) { 
      Q->front = Q->front->next; 
   }else{ 
      Q->front = Q->back = NULL; 
   }
   Q->length--;
   queueFreeNode(&N);
}


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints data elements in Q on a single line to stdout.
void printQueue(Queue Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }

   for(N = Q->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
/*
int equals(Queue A, Queue B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("Queue Error: calling equals() on NULL Queue reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}
*/




