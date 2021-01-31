//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA4
//---------------------------

#include "List.h"

#define UNVISITED   0
#define INPROGRESS  1
#define ALLDONE     2
#define FOUND       3
#define NOTFOUND    4

#define BLACK       0
#define GRAY        1
#define WHITE       2

#define MAX_ARRAY_SIZE 20000

typedef struct DigraphObj {
      int numVertices;
      int numEdges;
      int SCCIndex;
      Node adjacencyList[MAX_ARRAY_SIZE];
      Node reverseAdjacencyList[MAX_ARRAY_SIZE];
      Node SCCArray[MAX_ARRAY_SIZE];
      int visitStatus[MAX_ARRAY_SIZE];
      int entryTime[MAX_ARRAY_SIZE];
      int finishTime[MAX_ARRAY_SIZE];
      int SCCFlag;
} DigraphObj;

// DigraphObj
typedef struct DigraphObj* Digraph;

Digraph newDigraph(int numVertices);

void freeDigraph(Digraph* pG);

void freeSCC(Digraph G);

int getOrder(Digraph G);

int getSize(Digraph G);

int getOutDegree(Digraph G, int u);

int getNeighborCount(Digraph G, int v);

List getNeighbors(Digraph G, int v);

int addEdge(Digraph G, int u, int v);

int reverseAddEdge(Digraph G, int v, int u);

int deleteEdge(Digraph G, int u, int v);

int reverseDeleteEdge(Digraph G, int u, int v);

void unvisitAll(Digraph G);

int getMark(Digraph G, int u);

void setMark(Digraph G, int u, int theMark);

int PathExistsRecursive(Digraph G, int w, int v);

void PathExists(FILE* out, Digraph G, int u, int v);

void printDigraph(FILE* out, Digraph G);

void reversePrintDigraph(FILE* out, Digraph G);

int DepthFirstSearch(Digraph G, Stack S, int w, int currentTime);  

void ReverseDepthFirstSearch(Digraph G, Stack S, int w); 

bool DFSTestAcyclic(Digraph G, int w);

int getNextVertexWithLargestFinishTime(int myArray[], int numVertices);

void distance(FILE* out, Digraph G, int w, int u);

void acyclic(FILE* out, Digraph G);

void topoSort(FILE* out, Digraph G);

void insertNodeSCCArray(Digraph G, int w);

int getCountSCC(Digraph G);

int getNumSCCVertices(Digraph G, int u);

int inSameSCC(Digraph G, int u, int v);

void setupSCC(Digraph G);



