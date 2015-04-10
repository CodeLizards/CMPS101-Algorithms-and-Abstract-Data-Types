//------------------------------------------------------
////GraphTest.c
////CMPS101
////A simple test file for Graph ADT
////Elizabeth Harris
////elbharri
////pa5
////3-9-15
////----------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(11);
addArc(G, 1, 4);
addArc(G, 1, 6);
addArc(G, 3, 4);
addArc(G, 4, 7);
addArc(G, 2, 1);
addArc(G, 2, 4);
addArc(G, 5, 6);
addArc(G, 6, 2);
addArc(G, 8, 9);
addArc(G, 8, 1);
addArc(G, 6, 3);
addArc(G, 5, 7);
addArc(G, 9, 10);
addArc(G, 10, 3);

List S = newList();
int i = 1;
while(i <= getOrder(G)){
   append(S, i);
   i++;
}
DFS(G, S);
printGraph(stdout, G);
Graph T = transpose(G);
printGraph(stdout, T);
DFS(T,S);
Graph C = copyGraph(T);
printGraph(stdout, C);

for(i =1; i<= getOrder(T); i++){
   fprintf(stdout, "p %d\n", getParent(G, i));
   fprintf(stdout, "d %d\n", getDist(G, i));
   fprintf(stdout, "f %d\n", getFinish(G, i));
}
freeList(&S);
freeGraph(&G);
freeGraph(&T);
freeGraph(&C);
}
