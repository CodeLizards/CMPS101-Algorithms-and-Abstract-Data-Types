//------------------------------------------------------
//GraphTest.c
//CMPS101
//A simple test file for Graph ADT
//Elizabeth Harris
//elbharri
//pa4
//2-27-15
//----------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(11);

//int i = 0; 

addEdge(G, 1, 4);
addEdge(G, 1, 6);
addEdge(G, 3, 4);
addEdge(G, 4, 7);
addEdge(G, 2, 1);
addEdge(G, 2, 4);
addEdge(G, 5, 6);
addEdge(G, 6, 2);
addEdge(G, 8, 9);
addEdge(G, 8, 1);
addEdge(G, 6, 3);
addEdge(G, 5, 7);
addEdge(G, 9, 10);
addEdge(G, 10, 3);


printGraph(stdout, G);
//output
//4 6 2 8
//1 4 6 
//4 6 10 
//1 3 7 2 
//6 7 
//1 5 2 3 
//4 5 
//9 1 
//8 10 
//9 3

//Run BFS
BFS(G, 4);
//New List to check getPath
List L = newList();
getPath(L, G, 9);
//clear and run BFS on source
clear(L);
BFS(G, 4);
//get path on BFS
getPath(L, G, 4);
clear(L);
getPath(L, G, 11);

//Test if BFS ran correctly
//get Vertices
fprintf(stdout, "%d\n", getOrder(G));
//get Size
fprintf(stdout, "%d\n", getSize(G));
//get Source
fprintf(stdout, "%d\n", getSource(G));
//get Parent of 10
fprintf(stdout, "%d\n", getParent(G, 10));
//getParent of 4
fprintf(stdout, "%d\n", getParent(G, 4));
//get Distance from 10 to source(4);
fprintf(stdout, "%d\n", getDist(G, 10));
//get Distance from 4 to source(itself);
fprintf(stdout, "%d\n", getDist(G, 4));

makeNull(G);
freeList(&L);
freeGraph(&G); 
}
