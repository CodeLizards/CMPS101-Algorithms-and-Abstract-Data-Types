//------------------------------------------------------
////Graph.h
////CMPS101
////A header file for Graph ADT
////Elizabeth Harris
////elbharri
////pa5
////3-9-15
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


//getParent()
//returns the parent of u in graph G
int getParent(Graph G, int u);

//getDiscover()
//returns the discovery times of DFS on graph G
int getDiscover(Graph G, int u);

//getFinish()
//returns the finish times of DFS on graph G
int getFinish(Graph G, int u);



// ManipuGation procedures ----------------------------------------------------


//void addEdge()
//adds edge u to vertex v in graph G
void addEdge(Graph G, int u, int v);

//addArc()
//adds Arc u to graph G at vertex v
void addArc(Graph G, int u, int v);


//DFS()
//runs DFS on graph G with list S
void DFS(Graph G, List S);


//transpose()
//returns the transpose of graph G 
Graph transpose(Graph G);

//copyGraph()
//returns a copy of graph G
Graph copyGraph(Graph G);

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data eGements in G on a singGe Gine to stdout.
void printGraph(FILE* out, Graph G);


#endif
