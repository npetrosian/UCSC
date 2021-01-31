//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA1
//---------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"

// Constructors-Destructors-------------------------------------------------------------------------

// returns a List which points to a new empty list object
List newList(void) {                  
    List L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->tail = NULL;
    L->numItems = 0;
    return(L);
}

// frees all heap memory associated with its List* argument, and sets *pL to NULL
void freeList(List* pL) {  
    Node curr;
    Node temp;
    curr = (*pL)->head; 
    while(curr != NULL){
    	temp = curr->next;
    	free(curr);
    	curr = temp;

    }          
    if(pL!=NULL && *pL!=NULL){       
    	free(*pL);
    	*pL = NULL;
    }
}                                 

// Access functions---------------------------------------------------------------------------------

// Returns the number of nodes in this list
int length(List L) {                  
    if(L == NULL){
    	return (0);
    }
    return(L->numItems);
}

// Returns the integer in the front Node
// Precondition: L has at least one Node in it
int frontValue(List L) {
    assert(L != NULL && L->numItems > 0);
    Node N = L->head;
    return(N->data);
}            

// Returns the integer in the back Node
// Precondition: L has at least one Node in it
int backValue(List L) {
    assert(L != NULL && L->numItems > 0);
    Node N = L->tail;
    return(N->data);
}               

// Returns the integer in Node N
// Precondition: N is not NULL
int getValue(Node N){
    assert(N != NULL);
	return(N->data);
}                

// Returns 1 if List A and List B are the same integer sequence, otherwise returns 0
int equals(List A, List B) {
	Node currA = A->head;
	Node currB = B->head;
	while(currA != NULL){
		if(currA->data != currB->data){
			return (0);
		}
		currA = currA->next;
		currB = currB->next;
	}
	if(currB != NULL){
		return (0);
	}
	return (1);
}         

// Manipulation procedures-------------------------------------------------------------------------

// Resets this List to the empty state
void clear(List L) {
    L->head = NULL;
    L->tail = NULL;
	L->numItems = 0;
}               

// If List is non-empty, returns the front Node, without changing the List. Otherwise, does nothing. 
Node getFront(List L) {
	if(L == NULL){
    	return (NULL);
    }
    return(L->head);
}              

// If List is non-empty, returns the back Node, without changing the List. Otherwise, does nothing. 
Node getBack(List L) {
	if(L == NULL){
    	return (NULL);
    }
    return(L->tail);
}             

// Without changing the List that N is on, returns the Node that is previous to Node N on its List. If 
// there is no previous Node, returns NULL. 
Node getPrevNode(Node N) {
    return(N->prev);
}    

// Without changing the List that N is on, returns the Node that is next after Node N on its List. If  
// there is no next Node, returns NULL.
Node getNextNode(Node N) {
    return(N->next);
}             

// Inserts a new Node into List L before the front Node that has data as its value. If List is empty,
// makes that new Node the only Node in the list. 
void prepend(List L, int data) {

	Node prependNode = malloc(sizeof(NodeObj));
	prependNode->data = data;
    prependNode->prev = NULL;

    if(L->head == NULL && L->tail == NULL && L->numItems == 0){
    	L->head = prependNode;
    	L->tail = prependNode;
    	prependNode->next = NULL;
    	L->numItems++;
    }
    else{
    	L->head->prev = prependNode;
    	prependNode->next = L->head;
    	L->head = prependNode;
    	L->numItems++;
    }
}      

// Inserts a new Node into List L after the back Node that has data as its value. If List is empty,
// makes that new Node the only Node on the list.
void append(List L, int data) {

	Node appendNode = malloc(sizeof(NodeObj));
	appendNode->data = data;
	appendNode->next = NULL;

	if(L->head == NULL && L->tail == NULL && L->numItems == 0){
		L->head = appendNode;
		L->tail = appendNode;
	    appendNode->prev = NULL;
		L->numItems++;
	}
	else{
		L->tail->next = appendNode;
		appendNode->prev = L->tail;
		L->tail = appendNode;
		L->numItems++;

	}

}

// Insert a new Node into Node N's list before Node N that has data as its value. 
// Precondition: Node N is not NULL
void insertBefore(List L, Node N, int data) {
    assert(N != NULL);
	Node newNode = malloc(sizeof(NodeObj));
	newNode->data = data;
	newNode->next = N;
    newNode->prev = N->prev;
    
    if(L->head != N){
    	N->prev->next = newNode;
    }

    N->prev = newNode;

    if(L->head == N){
    	L->head = newNode;
    }
    L->numItems++;
}

// Insert a new Node into Node N's list after Node N that has data as its value. 
// Precondition: Node N is not NULL
void insertAfter(List L, Node N, int data) {
    assert(N != NULL);
	Node newNode = malloc(sizeof(NodeObj));
	newNode->data = data;
    newNode->prev = N;
    newNode->next = N->next;
    
    if(L->tail != N){
    	N->next->prev = newNode;
    }

    N->next = newNode;

    if(L->tail == N){
    	L->tail = newNode;
    }
    L->numItems++;
}  

// Deletes the front Node in List L
// Precondition: L has at least one Node in it
void deleteFront(List L) {
    assert(L != NULL && L->numItems > 0);
	Node newFront = L->head->next;
	free(L->head);
	L->head = newFront;
    L->numItems--;
}            

// Deletes the back Node in List L
// Precondition: L has at least one Node in it
void deleteBack(List L) {
    assert(L != NULL && L->numItems > 0);
	Node newBack = L->tail->prev;
	free(L->tail);
	L->tail = newBack;
    L->numItems--;
}  

// Deletes Node N from List L. Removes N from List L by making the Node before Node N link to
// the Node that's after Node N as its next Node, and making the Node after Node N link to the 
// Node that's before Node N as its previous Node. 
// Precondition: N is not NULL and N is a Node on List L
void deleteNode(List L, Node N){
    assert(N != NULL);
    assert(L != NULL);
    if(L->numItems == 0){
        return;
    }
    if(N == L->head){
        if(N->next != NULL){
            N->next->prev = NULL;
            L->head = N->next;
        }
    }
    else if (N == L->tail){
        if(N->prev != NULL){
            N->prev->next = NULL;
            L->tail = N->prev;
        }
    }
    else{
        if(N->prev != NULL && N->next != NULL){
            N->prev->next = N->next;
            N->next->prev = N->prev;
        }
    }
    L->numItems--;
    free(N);
}              

// Other operations------------------------------------------------------------------------------

// Prints the values in List L from front to back to the file pointed to by out, formatted as a 
// space-separated string. This is similar to toString() in Java.
void printList(FILE* out, List L) {
	Node curr = L->head;
	while(curr != NULL){
		fprintf(out, "%d ", curr->data);
		curr = curr->next;
	}
}    

