//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA2
//---------------------------

#include "List.h"

#define UNVISITED   0
#define INPROGRESS  1
#define ALLDONE     2
#define FOUND       3
#define NOTFOUND    4

#define MAX_ARRAY_SIZE 256

typedef struct GraphObj {
      int numVertices;
      int numEdges;
      Node adjacencyList[MAX_ARRAY_SIZE];
      int visitStatus[MAX_ARRAY_SIZE];
} GraphObj;

// GraphObj
typedef struct GraphObj* Graph;

Graph newGraph(int numVertices);

void freeGraph(Graph* pG);

int getOrder(Graph G);

int getSize(Graph G);

int getNeighborCount(Graph G, int v);

List getNeighbors(Graph G, int v);

int addEdge(Graph G, int u, int v);

void unvisitAll(Graph G);

int getMark(Graph G, int u);

void setMark(Graph G, int u, int theMark);

int PathExistsRecursive(Graph G, int w, int v);

void printGraph(FILE* out, Graph G);

