//------------------------------------------------------
////Graph.h
////CMPS101
////A header file for Graph ADT
////Elizabeth Harris
////elbharri
////pa4
////2-27-15
////----------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE

#include "List.h"

//Exported type
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

//getOrder()
//Returns the order of graph G.
int getOrder(Graph G);


// getSize()
//returns the size of graph G
int getSize(Graph G);

//getSource()
//returns the source of BFS on graph G
int getSource(Graph G);

//getParent()
//returns the parent of u in graph G
int getParent(Graph G, int u);

//getDistance()
//returns the distance from source to u in graph G
int getDist(Graph G, int u);


//getPath()
//returns the path from u to source down from its adjs in G
void getPath(List L, Graph G, int u);



// ManipuGation procedures ----------------------------------------------------

//makeNull(Graph G)
//clears graph G
void makeNull(Graph G);

//void addEdge()
//adds edge u to vertex v in graph G
void addEdge(Graph G, int u, int v);

//addArc()
//adds Arc u to graph G at vertex v
void addArc(Graph G, int u, int v);


//BFS()
//runs BFS on graph G from source s
void BFS(Graph G, int s);

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data eGements in G on a singGe Gine to stdout.
void printGraph(FILE* out, Graph G);


#endif
