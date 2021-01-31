//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA3
//---------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>
#include "Digraph.h"
#include "List.h"

// Constructors-Destructors-------------------------------------------------------------------------

// returns a Digraph that points to a newly created DigraphObj representing a graph which has 
// n vertices and no edges. 
Digraph newDigraph(int numVertices) {
	int i;

	Digraph G = (Digraph)malloc(sizeof(DigraphObj));
    G->numVertices = numVertices;
	G->numEdges = 0;
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->adjacencyList[i] = NULL;
		G->visitStatus[i] = UNVISITED;
	}
	return(G);
}

// frees all dynamic memory associated with its Digraph* argument, and sets *pG to NULL. 
void freeDigraph(Digraph* pG) {

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
int getOrder(Digraph G) {
	return(G->numVertices);
}

// returns the size of G, the number of edges in G. 
int getSize(Digraph G) {
	return(G->numEdges);
}

// returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
// that (u,v) is an edge in G. Returns -1 if v is not a legal vertex.
int getOutDegree(Digraph G, int u){
    Node curr = G->adjacencyList[u];
    int count = 0;

    if(u > getOrder(G) || u < 1){
        return (-1);
    }
    while(curr != NULL){
        count++;
        curr = curr->next;
    }
    return(count);

}

// returns the number of neighbors that vertex v has in G. 
// Returns -1 if v is not a legal vertex.
int getNeighborCount(Digraph G, int v) {
	int count = 0;
	Node curr; 
	if(v > getOrder(G) || v < 1){
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
List getNeighbors(Digraph G, int v) {
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

// adds v to the adjancency list of u, if that edge doesn't 
// already exist. If the edge does already exist, does nothing. Used when edges are entered or added. 
// returns 0 if (u,v) is a legal edge, and the edge didn't already exist. 
// returns 1 if (u,v) is a legal edge and the edge did already exist.
// returns -1 if (u,v) is not a legal edge.
int addEdge(Digraph G, int u, int v) {

    // We will allocate a node only when needed later in this subroutine.
	Node N;

    // have curr point to the u'th element of the adjacency array
    Node curr = G->adjacencyList[u];

	// printf("\naddEdge with u = %d v = %d\n", u, v);


	if(u < 1 || v < 1 || u > G->numVertices || v > G->numVertices){
		return(-1);
	}

	
    // Case 1: Index u is empty! 
    curr = G->adjacencyList[u];
    if(curr == NULL){
    	N = newNode(v);
        N->next = NULL;
        N->prev = NULL;
    	G->adjacencyList[u] = N;
    	G->numEdges++;
        // printf("case 1:\n");
    	return(0);
    }
    
    // Case 2: there's a duplicate of v in linked list at u.
    // Traverse the linked list in index u searching for 
    // current's data that may be equal to v 
    curr = G->adjacencyList[u];
    while (curr != NULL) {
        if (curr->data == v) {
            // printf("case 2:\n");
            return (1);
        }
        curr = curr->next;	
    }
    
    
    // Case 3: Let's find data that is greater than v
    curr = G->adjacencyList[u];
    while (curr != NULL) {

           if(curr->data > v) {
           	
               N = newNode(v);
       
           	   // if we are inserting at the front
               if (curr->prev == NULL) {
                   // printf("case 3.1:\n");
                   N->prev = NULL;
                   N->next = curr;
                   curr->prev = N;
                   G->adjacencyList[u] = N;
               } 
               // if inserting at end of the linked list
               else if (curr->next == NULL) {
                   // printf("case 3.2:\n");
                   curr->prev->next = N;  // fixes it?
                   N->prev = curr->prev;
                   N->next = curr;
                   curr->prev = N;
               } 
               // inserting between two nodes
               else {
                    // printf("case 3.3:\n");
                    N->prev = curr->prev;
                    N->next = curr;
                    curr->prev->next = N;
                    curr->prev = N;
       
               }
               G->numEdges++;
               // printf("case 3:\n");
           	   return(0);
           }
           curr = curr->next;
    }


    // Case 4: If we're still here we have a list at index u of the
    // adjacency array that is not empty and there's nothing greater than
    // v in it.
    // So let's insert the new node at the end of the linked list.
    curr = G->adjacencyList[u];
    while (curr->next != NULL) {
        curr = curr->next;
    }
    if(curr->next == NULL){
    	N = newNode(v);
    	N->next = NULL;
    	N->prev = curr;
    	curr->next = N;
    	G->numEdges++;
        // printf("case 4:\n");
    	return(0);
    }
    // printf("case 5:\n");
    return(-1);	
}

// deletes v from the adjacency list of u, if that edge exists.
// if the edge doesn't exist, does nothing. Used when edges are deleted.
// returns 0 if (u,v) is a legal edge, and the edge did already exist.
// returns 1 if (u,v) is a legal edge, and the edge didn't already exist.
// returns -1 if (u,v) is not a legal edge.
int deleteEdge(Digraph G, int u, int v){
	Node curr;
    Node nodeToBeFreed;


    // DEBUG
    // printf("*************************** \n");
    // curr = G->adjacencyList[u];
    // while (curr->next != NULL) {
    //     printf("curr-data = %d\n", curr->data);
    //     curr = curr->next;
    // }
    // printf("curr-data = %d\n", curr->data);
    // printf("*************************** \n");
    // while (curr != NULL) {
    //     printf("curr-data = %d\n", curr->data);
    //     curr = curr->prev;
    // }
    // DEBUG
 
    // Node tmp;
	int numberOfVertices = getOrder(G);

    // printf("deleteEdge() u=%d v=%d \n", u, v);
    

	if(u < 1 || u > numberOfVertices || v < 1 || v > numberOfVertices){ // if not a legal edge
		return (-1);
	}
	
	curr = G->adjacencyList[u];

    while (curr!= NULL && curr->data != v) {
        curr=curr->next;
    }
    

    if (curr==NULL) {
        return (1);
    }


    // if still here we found v
    nodeToBeFreed = curr;

    // if v is the first node in the adjacency array
    if (curr->prev == NULL) {
        G->adjacencyList[u] = curr->next;
        if (curr->next != NULL) {
            curr->next->prev = NULL;
        }
        free(nodeToBeFreed);
        return(0);
    }

    // if v is the last node in the adjacency array
    if (curr->next == NULL) {
        if (curr->prev != NULL) {
            curr = curr->prev;
            curr->next = NULL;
        }
        free(nodeToBeFreed);
        return (0);
    }


    // if still here, v is neither first nor last in the list
    curr = G->adjacencyList[u];
    while (curr->next->data != v) {
        curr = curr->next;
    }
    curr->next = curr->next->next;
    curr->next->prev = curr;
    

    free(nodeToBeFreed);
    return 0;

}

// marks all vertices of the graph as UNVISITED. 
void unvisitAll(Digraph G) {
	int i; 
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->visitStatus[i] = UNVISITED;
	}
}

void clearEntryTimes(Digraph G) {
	int i; 
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->entryTime[i] = 0;
	}
}

void clearFinishTimes(Digraph G) {
	int i; 
	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		G->finishTime[i] = 0;
	}
}

// returns the mark for vertex u, which will be UNVISITED, INPROGRESS, or ALLDONE. 
int getMark(Digraph G, int u) {
	return(G->visitStatus[u]);
}

// sets the mark for vertex u to be theMark. 
// theMark must be UNVISITED, INPROGRESS, or ALLDONE. 
void setMark(Digraph G, int u, int theMark) {
	G->visitStatus[u] = theMark;
}

// determines whether there is a path from w to v, taking advantage of "marks" that
// indicated which vertices are UNVISITED, so that we don't repeat work or get stuck in cycles.
// returns FOUND or NOTFOUND. 
int PathExistsRecursive(Digraph G, int w, int v) {

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

void PathExists(FILE* out, Digraph G, int u, int v){

   int theFoundValue;

   unvisitAll(G); // No vertices have been visited yet
   theFoundValue = PathExistsRecursive(G, u, v);
   if(theFoundValue == FOUND){
      fprintf(out, "YES\n");
   }
   else{
      fprintf(out, "NO\n");
   }
}

// Other operations------------------------------------------------------------------------------

// prints the Digraph G in the same format as an input line, so all that a client needs to do is a
// single call to PrintDigraph(). But it should not print out an edge twice. Achieve this by only 
// printing the edge for {j, k} when j < k. 
void printDigraph(FILE* out, Digraph G) {
	int numVertices = getOrder(G);
	int i;
	Node curr;
	List myList;

    fprintf(out, "PrintDigraph\n");
	fprintf(out, "%d", numVertices);
	for(i = 0; i <= numVertices; i++){
		if(G->adjacencyList[i] != NULL){
			//printf("xxxxxx %d\n", i);
            
            //myList = getNeighbors(G, i);
            curr = G->adjacencyList[i];
            while(curr != NULL){
            	
                fprintf(out, ", %d %d", i, curr->data);
            	curr = curr->next;
            	
            }

		}

	}
	fprintf(out, "\n");
	// free here
    myFreeList(&myList);

}

// outputs the distance between vertices w and u if there is a directed path between them in the 
// digraph. Otherwise, outputs INF. 
void distance(FILE* out, Digraph G, int s, int w){
    Queue Q = newQueue();
    int i;
    int v;
    int u;
    Node curr;

    int color[MAX_ARRAY_SIZE];
    int dist[MAX_ARRAY_SIZE];
    //int parent[MAX_ARRAY_SIZE];
    int numberOfVertices = getOrder(G);

    // make sure the vertices are legal! 
    if(s < 1 || s > numberOfVertices || w < 1 || w > numberOfVertices){ // if not a legal edge
        fprintf(out, "ERROR\n");
        return;
    }

    for(i = 0; i < MAX_ARRAY_SIZE; i++){
        color[i] = WHITE;
        dist[i] = -1;
        //parent[i] = -1;
    }
    color[s] = GRAY;
    dist[s] = 0;
    //parent[s] = -1;

    Enqueue(Q, s);

    while (!queueIsEmpty(Q)) {

        u = queueGetFront(Q);
        Dequeue(Q);

        curr = G->adjacencyList[u];
        while(curr != NULL){

            v = curr->data;
            if(color[v] == WHITE){
                color[v] = GRAY;
                dist[v] = dist[u] + 1;
                //parent[v] = u;
                Enqueue(Q, v);
            }
            curr = curr->next;
        }
        color[u] = BLACK;
    }

    if(dist[w] == -1){
        fprintf(out, "INF\n");
    }
    else{
        fprintf(out, "%d\n", dist[w]);
    }

    freeQueue(&Q);

} // end of distance method

// outputs YES if the digraph is acyclic. Otherwise, outputs NO.
void acyclic(FILE* out, Digraph G){
    int w;
    unvisitAll(G);

    // Grab a vertex from the adjacency array
    for(w = 1; w <= G->numVertices; w++){
        if(G->adjacencyList[w] != NULL){
            break;
        }
    }

    if(DFSTestAcyclic(G, w) == false){
        fprintf(out, "YES\n");
    }
    else{
        fprintf(out, "NO\n");
    }
}

// outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.
void topoSort(FILE* out, Digraph G){
   int w;
   Stack S = newStack();

   unvisitAll(G);
   
   // Grab a vertex from the adjacency array
    for(w = 1; w <= G->numVertices; w++){
        if(G->adjacencyList[w] != NULL){
            break;
        }
    }

   DepthFirstSearch(G, S, w, 0);
   fprintf(out, "TopoSort\n");
   printStack(out, S);
   freeStack(&S);
}



















