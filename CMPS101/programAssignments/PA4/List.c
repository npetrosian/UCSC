/*
 * Author: Abhishek Alfred Singh
 * Email: abasingh@ucsc.edu
 * Modified by Natalie Petrosian
 * CMPS 101 - Doubly linked list implementation
 */

#include <stdlib.h>
#include "List.h"

// private QueueObj type
typedef struct QueueObj{
   Node front;
   Node back;
   int length;
} QueueObj;

// private StackObj type
typedef struct StackObj{
   Node top;
   int height;
} StackObj;

List newList(void) {
    List l = malloc(sizeof(ListObj));
    l->back = NULL;
    l->front = NULL;
    l->length = 0;
    return l;
}

Node newNode(int data) {
    Node node = malloc(sizeof(NodeObj));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void freeList(List *pL) {
    clear(*pL);
    free(*pL);
}

int length(List L) {
    return L->length;
}

int frontValue(List L) {
    return L->front->data;
}

int backValue(List L) {
    return L->back->data;
}

int getValue(Node N) {
    return N->data;
}

int equals(List A, List B) {
    Node b = B->front;
    Node a = A->front;
    for (; a != NULL && b != NULL; a = a->next, b = b->next) {
        if (a != b)
            break;
    }
    if (a != NULL || b != NULL)
        return 0;
    return 1;
}

void clear(List L) {
    if (L == NULL)
        return;
    if (L->front == NULL && L->back == NULL)
        return;
    while (getFront(L) != NULL) {
        deleteFront(L);
    }
}

Node getFront(List L) {
    return L->front;
}

Node getBack(List L) {
    return L->back;
}


void prepend(List L, int data) {
    if (L == NULL)
        return;
    insertBefore(L, getFront(L), data);
}

void append(List L, int data) {
    if (L == NULL)
        return;
    insertAfter(L, getBack(L), data);
}


void deleteFront(List L) {
    Node front = getFront(L);
    deleteNode(L, front);
}

void deleteBack(List L) {
    Node back = getBack(L);
    deleteNode(L, back);
}

void detachNode(List L, Node N) {
    if (N == NULL)
        return;
    Node n = NULL;
    for (n = L->front; n != NULL; n = n->next) {
        if (n == N)
            break;
    }
    if (n == NULL)
        return;
    n = N->next;
    Node p = N->prev;
    if (n != NULL) {
        n->prev = p;
    }
    if (p != NULL) {
        p->next = n;
    }
    if (L->front == N) {
        L->front = n;
    }
    if (L->back == N) {
        L->back = p;
    }
    L->length -= 1;
}

void printList(FILE *out, List L) {
    for (Node n = L->front; n != NULL; n = n->next) {
        fprintf(out, "%d ", n->data);
    }
    fprintf(out, "\n");
}

Node getPrevNode(Node N) {
    return N->prev;
}

Node getNextNode(Node N) {
    return N->next;
}

void insertBefore(List L, Node N, int data) {
    if (L == NULL)
        return;

    if (N == NULL && L->length != 0) {
        return;
    }
    Node node = newNode(data);
    if (N == NULL) {
        L->front = node;
        L->back = node;
        L->length = 0;
    } else {
        Node tmp = N->prev;
        N->prev = node;
        node->next = N;
        node->prev = tmp;
        if (L->front == N)
            L->front = node;
        if (tmp != NULL)
            tmp->next = node;
    }
    L->length += 1;
}

void insertAfter(List L, Node N, int data) {
    if (L == NULL)
        return;

    if (N == NULL && L->length != 0) {
        return;
    }
    Node node = newNode(data);
    if (N == NULL) {
        L->front = node;
        L->back = node;
        L->length = 0;
    } else {
        Node tmp = N->next;
        N->next = node;
        node->prev = N;
        node->next = tmp;
        if (L->back == N)
            L->back = node;
        if (tmp != NULL)
            tmp->prev = node;
    }
    L->length += 1;
}

void deleteNode(List L, Node N) {
    detachNode(L, N);
    free(N);
}

void attachNodeBetween(List L, Node N, Node N1, Node N2) {
    if (L == NULL || N == NULL || (N1 == NULL && N2 == NULL))
        return;
    if (N1 != NULL && N1->next != N2)
        return;
    if (N2 != NULL && N2->prev != N1)
        return;
    N1->next = N;
    N2->prev = N;
    N->prev = N1;
    N->next = N2;
    L->length += 1;
}

// Queue methods start here -------------------------------------------

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

// Queue methods end here ---------------------------------------------

// Stack methods start here --------------------------------------------

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newStack()
// Returns reference to new empty Stack object.
Stack newStack(void){
   Stack S;
   S = malloc(sizeof(StackObj));
   S->top = NULL;
   S->height = 0;
   return(S);
}

// freeStack()
// Frees all heap memory associated with Stack *pS, and sets *pS to NULL.
void freeStack(Stack* pS){
   if(pS!=NULL && *pS!=NULL){
      while( !isEmpty(*pS) ) { pop(*pS); }
      free(*pS);
      *pS = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getTop()
// Returns the value at the top of S.
// Pre: !isEmpty(S)
int getTop(Stack S){
   if( S==NULL ){
      printf("Stack Error: calling getTop() on NULL Stack reference\n");
      exit(1);
   }
   if( isEmpty(S) ){
      printf("Stack Error: calling getTop() on an empty Stack\n");
      exit(1);
   }
   return(S->top->data);
}

// getHeight()
// Returns the height of S
int getHeight(Stack S){
   if( S==NULL ){
      printf("Stack Error: calling getHeight() on NULL Stack reference\n");
      exit(1);
   }
   return(S->height);
}

// isEmpty()
// Returns true (1) if S is empty, otherwise returns false (0).
int isEmpty(Stack S){
   if( S==NULL ){
      printf("Stack Error: calling isEmpty() on NULL Stack reference\n");
      exit(1);
   }
   return(S->height==0);
}


// Manipulation procedures ----------------------------------------------------

// push()
// Places new data element on top of S
// Post: !isEmpty(S)
void push(Stack S, int data){
   Node N = newNode(data);

   if( S==NULL ){
      printf("Stack Error: calling push() on NULL Stack reference\n");
      exit(1);
   }

   if( isEmpty(S) ){ 
      S->top = N; 
   }else{ 
      N->next = S->top; 
      S->top = N; 
   }
   S->height++;
}

// pop()
// Deletes element on top of S
// Pre: !isEmpty(S)
void pop(Stack S){
   Node N = NULL;

   if( S==NULL ){
      printf("Stack Error: calling pop() on NULL Stack reference\n");
      exit(1);
   }
   if( isEmpty(S) ){
      printf("Stack Error: calling pop() on an empty Stack\n");
      exit(1);
   }

   N = S->top;
   if( getHeight(S)>1 ) { 
      S->top = S->top->next; 
   }else{ 
      S->top = NULL; 
   }
   S->height--;
   freeNode(&N);
}


// Other Functions ------------------------------------------------------------

// printStack()
// Prints data elements in S on a single line to stdout.
void printStack(FILE* out, Stack S){
   Node N = NULL;

   if( S==NULL ){
      printf("Stack Error: calling printStack() on NULL Stack reference\n");
      exit(1);
   }
   for(N = S->top; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
   fprintf(out, "\n");
}

// Stack methods end here ----------------------------------------------






