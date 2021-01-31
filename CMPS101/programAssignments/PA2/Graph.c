//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA2
//---------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "Graph.h"
#include "List.h"

// Constructors-Destructors-------------------------------------------------------------------------

// returns a Graph that points to a newly created GraphObj representing a graph which has 
// n vertices and no edges. 
Graph newGraph(int numVertices) {
	int i;

	Graph G = (Graph)malloc(sizeof(GraphObj));
    G->numVertices = numVertices;
	G->numEdges = 0;
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->adjacencyList[i] = NULL;
		G->visitStatus[i] = UNVISITED;
	}
	return(G);
}

// frees all dynamic memory associated with its Graph* argument, and sets *pG to NULL. 
void freeGraph(Graph* pG) {

	Node curr;
	Node tmp;
	int  i;
	int  numberOfVertices;

	if (pG == NULL) {
		return;
	}

	numberOfVertices = (*pG)->numVertices;

	for(i = 1; i <= numberOfVertices; i++) {

		// let curr be the first node at index i of the AdjacencyList array
		curr = (*pG)->adjacencyList[i] ;

		while (curr != NULL) {
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}

    }

	free(*pG);
}

void myFreeList(List *pL) {
	free(*pL);
}

// Access functions---------------------------------------------------------------------------------

// returns the order of G, the number of vertices in G. 
int getOrder(Graph G) {
	return(G->numVertices);
}

// returns the size of G, the number of edges in G. 
int getSize(Graph G) {
	return(G->numEdges);
}

// returns the number of neighbors that vertex v has in G. 
// Returns -1 if v is not a legal vertex.
int getNeighborCount(Graph G, int v) {
	int count = 0;
	Node curr; 
	if(v > getOrder(G)){
		return (-1);
	}
	else{
		curr = G->adjacencyList[v]; 
		while(curr != NULL){
			curr = curr->next;
			count++;
		}
		return(count);
	}
}

// returns a list that has all the vertices that are neighbors of v. 
// There is no input operation that corresponds to getNeighbors. 
List getNeighbors(Graph G, int v) {
	List myList = newList();
	Node curr = G->adjacencyList[v];
	myList->front = G->adjacencyList[v];

	while (curr != NULL){
		if(curr->next == NULL){
			myList->back = curr;
		}
		myList->length++;
		curr = curr->next; 
	}
	return (myList);
}

// Manipulation procedures-------------------------------------------------------------------------

// adds v to the adjancency list of u and u to the adjacency list of v, if that edge doesn't 
// already exist. If the edge does already exist, does nothing. Used when edges are entered. 
// returns 0 if u and v are legal vertices, otherwise returns -1. 
int addEdge(Graph G, int u, int v) {


   int foundDublicate = 0;

	// create a new node with the v value
	Node N = newNode(v);

	// have curr point to the u'th element of the adjacency array
	Node curr = G->adjacencyList[u];

	//printf("\naddEdge()  u=%d  v=%d  \n",u,v);
	// if it's an empty cell in the array, have it point to the new node
	if(curr == NULL){
		//printf("inserting v=%d into empty spot at index u=%d\n",v,u);
		G->adjacencyList[u] = N;
		G->numEdges++;
	}
	else{ // otherwise, find the last node and set its next to the new node

		while(curr->next != NULL){
			//printf("xxx attempting to add v=%d into index u=%d where curr->data=%d \n",v,u, curr->data);
			if (v == curr->data) {
				//printf("duplicate detected!\n");
				foundDublicate = 1;
			}
			curr = curr->next;
		}

		if (v == curr->data) {
	        //printf("duplicate detected!\n");
		    foundDublicate = 1;
		}

		if (foundDublicate == 1) {
			return(0);
		}

		//printf("inserting v=%d into xTAIL spot at index u=%d\n",v,u);
		// G->adjacencyList[u] = N;
		curr->next = N;
		G->numEdges++;
		// debugging
		//curr=G->adjacencyList[u];
		//printf("all the nodes at index u: ");
		//while (curr != NULL) {
		//	printf(" %d ",curr->data);
		//	curr = curr->next;
		//}
		//printf("\n");
		///////////////
	}

    if(u == v){
    	return(0);
    }

    //printf("SWITCH \n");
	// NOW SWITCH between u and v
	
    N = newNode(u);

    // have curr point to the v'th element of the adjacency array
	curr = G->adjacencyList[v];

	// if it's an empty cell in the array, have it point to the new node
	if(curr == NULL){
		//printf("inserting u=%d into empty spot at index v=%d\n",u,v);
		G->adjacencyList[v] = N;
		return (0);
	}
	else{ // otherwise, find the last node and set its next to the new node
		while(curr->next != NULL){
			//printf("v=%d  u=%d curr->data=%d \n",v,u,curr->data);
			curr = curr->next;
		}
		//printf("inserting u=%d into (TAIL) spot at index v=%d\n",u,v);
		curr->next = N;

		// debugging
		//curr=G->adjacencyList[v];
		//printf("all the nodes at index v: ");
		//while (curr != NULL) {
		//	printf(" %d ",curr->data);
		//	curr = curr->next;
		//}
		//printf("\n");
		///////////////

		return(0);
	}

	// If we are still here, return failure. 
	return(-1);
}

// marks all vertices of the graph as UNVISITED. 
void unvisitAll(Graph G) {
	int i; 
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->visitStatus[i] = UNVISITED;
	}
}

// returns the mark for vertex u, which will be UNVISITED, INPROGRESS, or ALLDONE. 
int getMark(Graph G, int u) {
	return(G->visitStatus[u]);
}

// sets the mark for vertex u to be theMark. 
// theMark must be UNVISITED, INPROGRESS, or ALLDONE. 
void setMark(Graph G, int u, int theMark) {
	G->visitStatus[u] = theMark;
}

// determines whether there is a path from w to v, taking advantage of "marks" that
// indicated which vertices are UNVISITED, so that we don't repeat work or get stuck in cycles.
// returns FOUND or NOTFOUND. 
int PathExistsRecursive(Graph G, int w, int v) {

    List L;
    Node curr; 
    int theMark;
    int theFoundValue;


	if(w == v){
		return(FOUND);
	}

	setMark(G, w, INPROGRESS);

	L = getNeighbors(G, w);

	
	for(curr = L->front; curr != NULL; curr = curr->next){
		theMark = getMark(G, curr->data);
		if(theMark == UNVISITED){
			theFoundValue = PathExistsRecursive(G, curr->data, v);
		}
		if(theFoundValue == FOUND){
			// free here
            myFreeList(&L);
			return(FOUND);
		} // found a path to w, so no need to continue
	}
	// finished processing all of w's neighbors without finding v
	setMark(G, w, ALLDONE);

    // free here
    myFreeList(&L);

	return(NOTFOUND);
}

// Other operations------------------------------------------------------------------------------

// prints the Graph G in the same format as an input line, so all that a client needs to do is a
// single call to PrintGraph(). But it should not print out an edge twice. Achieve this by only 
// printing the edge for {j, k} when j < k. 
void printGraph(FILE* out, Graph G) {
	int numVertices = getOrder(G);
	int i;
	Node curr;
	List myList;

	fprintf(out, "%d", numVertices);
	for(i = 0; i <= numVertices; i++){
		if(G->adjacencyList[i] != NULL){
			//printf("xxxxxx %d\n", i);
            
            myList = getNeighbors(G, i);
            curr = myList->front;
            while(curr != NULL){
            	if(i <= curr->data){
            		fprintf(out, ", %d %d", i, curr->data);
            	}
            	curr = curr->next;
            	
            }

		}

	}
	fprintf(out, "\n");
	// free here
    myFreeList(&myList);

}
