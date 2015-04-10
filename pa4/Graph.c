//--------------------------------------------------------------
//Graph.c
//CMPS101
//Implementation of a Graph ADT
//Elizabeth Harris
//elbharri
//pa4
//2-27-15
//---------------------------------------------------------------

#define INF -10000000 
#define NIL -1
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
	int* distance;
	int* color;
	int size; //edges
	int order; //vertices
	int source;

}GraphObj; 

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = calloc(n+1, sizeof(List));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i = 1; i < n+1; i++){
		G->adjList[i] = newList();
		G->color[i] = white;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
   int i = 0;
   for(i=1; i<=(*pG)->order; i++){
      freeList(&((*pG)->adjList[i]));
   }
      free((*pG)->adjList);
      free((*pG)->parent);
      free((*pG)->distance);
      free((*pG)->color);
      free(*pG);
}

// Access functions -----------------------------------------------------------

//getOrder()
//Returns the number of vertices of graph G.
int getOrder(Graph G){
   return G->order;
}

// getSize()
//returns the number of edges of graph G
int getSize(Graph G){
	return G->size;
}

//getSource()
//returns the source of BFS on graph G
int getSource(Graph G){
	return G->source;
}

//getParent()
//returns the parent of u in graph G
int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
	   printf("Graph Error: calling getParent() with a non-existent vertex reference\n");
       exit(1);
	}
	return G->parent[u]; 

}

//getDistance()
//returns the distance from source to u in graph G
int getDist(Graph G, int u){
	if(!(u <= 1 || u<= getOrder(G))){
	   printf("Graph Error: calling getDist() with a non-existent vertex reference\n");
       exit(1);
	}
        return G->distance[u]; 
}


//getPath()
//returns the path from u to source down from its adjs in G
void getPath(List L, Graph G, int u){
	if(u < 1 || u > getOrder(G)){
	  printf("Graph Error: calling getParent() with a non-existent vertex reference\n");
          exit(1);
	}
        //if u = source add u to shortest path list
        if(u == getSource(G) ){     
           append(L, u);
        }
        //else if destinaion has no parent and is not connected, add NIL to path
        else if(getParent(G,u) == NIL)
           append(L , NIL);
        //else put destination at beggining of path
        //then while its parent hasn't reached the source or become NIL,
        //put the parent at the beggining then loop through all parents 
        else{
           prepend(L, u);
           int parent = 0;
           parent = getParent(G, u);
           while(parent != getSource(G) && parent != NIL){
              prepend(L, parent);
              parent = getParent(G, parent);
           }
           //breaks because of no parent, put -1 to signify to connection to source
           //otherwise, put its parent at the beginning(should be source if connected);
           if(parent == NIL)
              prepend(L, NIL);
           else
              prepend(L, parent);
        }
}
  

// ManipuGation procedures ----------------------------------------------------

//makeNull(Graph G)
//clears graph G
void makeNull(Graph G){
   int i = 0;
   for(i =1; i <= getOrder(G); i++){
      clear(G->adjList[i]);
   }
}
//void addArc()
//adds arc to joing u to v, one way edge;
//adds v to adjList of u ;
void addArc(Graph G, int u, int v){	
       if(u < 1 || u > getOrder(G)){
	   printf("Graph Error: calling addEdge() with a non-existent vertex reference\n on u");
       exit(1);
	}
	if(v < 1 || v > getOrder(G)){
	   printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
       exit(1);
	}
	append(G->adjList[u], v);
	G->size++;

}

//addEdge()
//adds edge to connect u to v
//adds v to adjList of u
//adds u to adjList of v
void addEdge(Graph G, int u, int v){
	if(u <  1 || u > getOrder(G)){
	   printf("Graph Error: calling addEdge() with a non-existent vertex reference\n");
       exit(1);
	}
	if(v < 1 || v > getOrder(G)){
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



//BFS()
//runs BFS on graph G from source s
//modeled after psuedo code provided in lecture notes 2-11-15
void BFS(Graph G, int s){
    int order = getOrder(G);
    int i = 0;
    int onQ = 0;
    int currentAdj = 0;
    G->source = s;
    //loop through all adjLists(number of vertices)
    if(G == NULL){
       printf("Graph Error: calling BFS() on NULL Graph\n");
       exit(1);
    }
    if(s < 1 || s > getOrder(G)){
       printf("Graph Error: calling BFS() on graph with no source");
       exit(1);
    }
   //initialize all vertex in adjList to blank graph state
   //initialize source to gray and its dist to 0
   for(i = 1; i<=order;i++){
      G->color[i] = white;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s] = gray;
   G->distance[s] = 0;
   G->parent[s] = NIL;

   //make new list to run getpath and put source in the queue
   List Queue = newList();
   append(Queue, s);
   //while queue isn't empty
   //dequeue the front element on it
   while(length(Queue) != 0){
      onQ = front(Queue);
      deleteFront(Queue);
     
     //if the adjList to the dequeue-ed element isn't zero
     //walk down the list and set the color, distance, 
     //and parent of each vertex in its adjList if undiscovered(white)
     //finally, first element in adjList on Queue 
     //and color current dequeue-ed element black
     if( !(isEmpty(G->adjList[onQ])))
         moveTo(G->adjList[onQ], 0);
     while(getIndex(G->adjList[onQ]) != -1){
        currentAdj = getElement(G->adjList[onQ]);
     	if(G->color[currentAdj] == white){
           G->color[currentAdj] = gray;
           G->distance[currentAdj] = (getDist(G, onQ) + 1 );
           G->parent[currentAdj] = onQ;
           append(Queue, currentAdj);
        }moveNext(G->adjList[onQ]);
     } 
     G->color[onQ] = black;
  }
  freeList(&Queue);

}

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G){
   int order = getOrder(G);
   int i = 0;
   for(i = 1; i <=order; i++){
      fprintf(out, "%d: ", i);
      printList(out, G->adjList[i]);
   }
}


