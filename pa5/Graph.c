//--------------------------------------------------------------
//Graph.c
//CMPS101
//Implementation of a Graph ADT
//Elizabeth Harris
//elbharri
//pa5
//3-13-15
//---------------------------------------------------------------

#define INF -10000000 
#define NIL 0
#define black -200
#define gray -300
#define white -400

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
//#include "List.h"
//Exported type
typedef struct GraphObj{
	List* adjList; 
	int* parent;
	int* discover;
        int* finish;
	int* color;
        int time;
	int size; //edges
	int order; //vertices

}GraphObj; 

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n){
        if(n == 0){
           printf("Graph Error: calling newGtaph() with an invalid number of vertices\n");
           exit(1);
        }
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = calloc(n+1, sizeof(List));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
        G->color = calloc(n+1, sizeof(int));
	G->order = n;
        G->time = 0;
	G->size = 0;
	for(int i = 1; i < n+1; i++){
		G->adjList[i] = newList();
		G->color[i] = white;
                G->finish[i] = INF;
		G->discover[i] = INF;
		G->parent[i] = NIL;
	}return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
   if(pG == NULL){
      printf("Graph Error: calling freeGraph on a null graphReference\n");
      exit(1);
   }
   int i = 0;
   for(i=1; i<=(*pG)->order; i++){
      freeList(&((*pG)->adjList[i]));
   }
      free((*pG)->adjList);
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      free((*pG)->color);
      free(*pG);
}

// Access functions -----------------------------------------------------------

//getOrder()
//Returns the number of vertices of graph G.
int getOrder(Graph G){
   if(G == NULL){
      printf("Graph Error: calling freeGraph on a null graphReference\n");
      exit(1);
   }
   return G->order;
}

// getSize()
//returns the number of edges of graph G
int getSize(Graph G){
   if(G == NULL){
      printf("Graph Error: calling getSize on a null graphReference\n");
      exit(1);
   }
   return G->size;
}

//getParent()
//returns the parent of u in graph G
int getParent(Graph G, int u){
   if(G == NULL){
      printf("Graph Error: calling getParent on a null graphReference\n");
      exit(1);
   }
   if(u < 1 && u > getOrder(G)){
      printf("Graph Error: calling getParent() with a non-existent vertex reference\n");
      exit(1);
   }
   return G->parent[u]; 

}

//getDiscover()
//returns the distance from source to u in graph G
int getDiscover(Graph G, int u){
   if(G == NULL){
      printf("Graph Error: calling getDiscover on a null graphReference\n");
      exit(1);
   }
   if(u < 1 && u > getOrder(G)){
      printf("Graph Error: calling getDiscover() with a non-existent vertex reference\n");
      exit(1);
   }
   return G->discover[u]; 
}

//getFinsih()
//returns the distance from source to u in graph G
int getFinish(Graph G, int u){
  if(G == NULL){
      printf("Graph Error: calling getFinish on a null graphReference\n");
      exit(1);
  }
  if(u < 1 && u > getOrder(G)){
     printf("Graph Error: calling getDist() with a non-existent vertex reference\n");
       exit(1);
  }
        return G->finish[u]; 
}

// ManipuGation procedures ----------------------------------------------------

//void addArc()
//adds arc to joing u to v, one way edge;
//adds v to adjList of u ;
void addArc(Graph G, int u, int v){
  if(G == NULL){
      printf("Graph Error: calling addArc on a null graphReference\n");
      exit(1);
   }
	
  if(u <  1 && u > getOrder(G)){
     printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
       exit(1);
  }
  if(v < 1 && v > getOrder(G)){
     printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
       exit(1);
  }
       //if empty, just put on end of adjList
       if(isEmpty(G->adjList[u])){
          append(G->adjList[u], v);
          G->size++;
       }
       //if not empty, check if v is less than, equal to or greater than 
       //whats already in the adjList of u
       else if(!isEmpty(G->adjList[u])){
          moveTo(G->adjList[u], 0);
          while(getIndex(G->adjList[u]) != -1){
             if((getElement(G->adjList[u]) == v)){
                insertAfter(G->adjList[u], v);
                G->size++;
                break;
             }
             else if((getElement(G->adjList[u])) < v){
                moveNext(G->adjList[u]);
             
             }
             else if((getElement(G->adjList[u])) > v){
                insertBefore(G->adjList[u], v);
                G->size++;
                break;
            }
         }if(getIndex(G->adjList[u]) == -1)
            append(G->adjList[u], v);      
      }
  }

//addEdge()
//adds edge to connect u to v
//adds v to adjList of u
//adds u to adjList of v
void addEdge(Graph G, int u, int v){
        if(G == NULL){
            printf("Graph Error: calling addEdge on a null graphReference\n");
            exit(1);
        }

	if(u <  1 && u > getOrder(G)){
	   printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
          exit(1);
	}
	if(v < 1 && v > getOrder(G)){
	   printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
       exit(1);
	}
       int i = 0;
       //add u to edge list v, then swap values to add v to adjlist u
       //put in numerical order
       for(i = 0; i<2; i++){
       //if empty, just put on end of adjList
       if(isEmpty(G->adjList[u])){
	  append(G->adjList[u], v);
	  G->size++;
       }
       //if not empty, check if v is less than, equal to or greater than 
       //whats already in the adjList of u
       else if(!isEmpty(G->adjList[u])){
          moveTo(G->adjList[u], 0);
          while(getIndex(G->adjList[u]) != -1){
             if((getElement(G->adjList[u]) == v)){
                insertAfter(G->adjList[u], v);
                G->size++;
                break;
             }
             else if((getElement(G->adjList[u])) < v){
                moveNext(G->adjList[u]);
             
             }
             else if((getElement(G->adjList[u])) > v){
                insertBefore(G->adjList[u], v);
                G->size++;
                break;
            }
         }if(getIndex(G->adjList[u]) == -1)
            append(G->adjList[u], v);      
      }
      //swap u and v to run the whole thing again vice versa
      int swp = 0;
       swp = v;
       v = u;
       u = swp;
   }
}

void visit(int x, Graph G, List S);

//DFS
//runs DFS on Graph G 
//Pre: getLength(S) == n
//S contained some amount of ints == getOrder(G)
void DFS(Graph G, List S){
  if(length(S) != getOrder(G)){
      printf("Graph Error: calling DFS with a list of the wrong length\n");
      exit(1);
   }
  if(G == NULL){
      printf("Graph Error: calling DFS on a null graphReference\n");
      exit(1);
  }
  if(S == NULL){
      printf("Graph Error: calling DFS on a null ListReference\n");
      exit(1);
   }
  int i = 0;
  int x = 0;
  int order = getOrder(G);
   for(i = 1; i<=order;i++){
      G->color[i] = white;
      G->parent[i] = NIL;
   }
   G->time = 0;
   moveTo(S, length(S)-1);
   for(i = 1; i <= length(S); i++){
      x = front(S);
      if(G->color[x] == white)
         visit(x, G, S);
         deleteFront(S);
   }
   
}

//Visit()
//Helper function to DFS
//sets color, parent, finish and distance
void visit(int x, Graph G, List S){
   G->color[x] = gray;
   G->time++;
   G->discover[x] = G->time;
   if(!(isEmpty(G->adjList[x])))
      moveTo(G->adjList[x], 0); 
   while(getIndex(G->adjList[x]) != -1){
      int y = getElement(G->adjList[x]);
      if(G->color[y] == white){
         G->parent[y] = x;
         visit(y, G, S);
      }
      moveNext(G->adjList[x]);
   }
   G->color[x] = black;
   insertAfter(S, x);
   G->time++;
   G->finish[x] = G->time;
}

//transpose()
//returns transpose of graph G
Graph transpose(Graph G){
   if(G == NULL){
      printf("Graph Error: calling transpose on a null graphReference\n");
      exit(1);
   }
   int order = getOrder(G);
   Graph T = newGraph(order);

   for(int i = 1; i <=order; i++){
      if(!(isEmpty(G->adjList[i]))){
         moveTo(G->adjList[i], 0);
         while(getIndex(G->adjList[i]) != -1){
            addArc(T, getElement(G->adjList[i]), i);
            moveNext(G->adjList[i]);
         }
      }
   }return T;
}
   
//copy()
//Returns a copy of Graph G
Graph copyGraph(Graph G){
   if(G == NULL){
      printf("Graph Error: calling copyGraph on a null graphReference\n");
      exit(1);
   }
   int order = getOrder(G);
   Graph C = newGraph(order);
   for(int i = 1; i <= order; i++){
      freeList(&(C->adjList[i]));
      C->adjList[i] = copyList(G->adjList[i]);
   }
   return C;
}
   

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G){
   if(G == NULL){
      printf("Graph Error: calling printGraph on a null graphReference\n");
      exit(1);
   }
   int order = getOrder(G);
   int i = 0;
   for(i = 1; i <=order; i++){
      fprintf(out, "%d: ", i);
      printList(out, G->adjList[i]);
   }
}


