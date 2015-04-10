//------------------------------------------------------
//FindPath.c
//CMPS101
//Main which makes a graph and finds the shortest paths between specified vertices 
//Client of Graph ADT and List ADT
//Elizabeth Harris
//elbharri
//pa4
//2-27-15
////----------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX 2000

int main(int argc, char * argv[]){
	int i;
	FILE *in, *out;
	char line[MAX];
	char* input;
        int vertex; //number of vertex in graph, given in first line
        int count = 0;
 	
// check command line for correct number of arguments
if( argc != 3 ){
   printf("Usage: %s <input file> <output file>\n", argv[0]);
   exit(1);
}

// open files for reading and writing 
in = fopen(argv[1], "r");
out = fopen(argv[2], "w");

//check that infile exists
if( in==NULL ){
   printf("Unable to open file %s for reading\n", argv[1]);
   exit(1);
}
if( out==NULL ){
   printf("Unable to open file %s for writing\n", argv[2]);
   exit(1);	
}

   //gets first line and put it in vertex variable 
   fgets (line, MAX, in);
   char one[10][MAX];
   strcpy(one[1], line);
   vertex = atoi(one[1]);   

   //allocate array of strings
   int From[MAX];
   int To[MAX];
   int PathTo[MAX];
   int PathFrom[MAX];
  
   i=0;
   //read in input file until reaches 0,0 and puts int forms into 2 arrays
   //two arrays are for where it goes and where it comes from when adding edges
   while( fgets(line, MAX, in) != NULL){
      count++;     
      input = strtok(line, " ");
      //convert input as string to number and run loop until lines token == "0"
      if(atoi(input) != 0){
         while( input!=NULL ){
            //if in first column of input file(even), put in from array;
            if(i%2 == 0){
               From[i/2] = atoi(input);
            }
            // if in second column(odd), put into TO array so that it can be added later   
            else
               To[i/2] = atoi(input);
            i++;
            input = strtok(NULL, " \n");
         }
      }else 
         break;
   }
   int path = 0;
   i = 0;
   //reads input file after 0,0 and puts ints into array for get Path 
   while( fgets(line, MAX, in) != NULL){
      path++;
      input = strtok(line, " ");
      while(input != NULL){
         if(i%2 == 0)
            PathFrom[i/2] = atoi(input);
         else
            PathTo[i/2] = atoi(input);
         i++;
         input = strtok(NULL, " \n");
      }
   }

   fclose(in);

Graph G = newGraph(vertex);
int u = 0;
int v = 0;
//append edges onto graph from instructions in array
for( i = 0; i<count-1; i++){
   u = From[i];
   v = To[i];
   addEdge(G, u, v);
   
}
printGraph(out, G);
fprintf(out, "\n");
//make List for findPath
List L = newList();
//loop through array containing containing second half of input file
//get values to on which to run getPath
//Run BFS and getPath on graph with inputs from array

for(i = 0; i < path-1; i++){
   clear(L);
   u = PathFrom[i];
   v = PathTo[i];
   BFS(G, u);
   getPath(L, G, v);
   if(!isEmpty(L)){
      moveTo(L, 0);
   }
   //if no path, print distance = infinity and no path exists
   if(getElement(L) == -1){
      fprintf(out, "The distance from %d to %d is infinity\n", u, v);
      fprintf(out, "No %d-%d path exists\n\n", u, v);
   //if source equals destination, print distance = 0 and path source-source
   }else if(u == v){
      fprintf(out, "The distance from %d to %d is 0\n", u, v);
      fprintf(out, "A shortest %d-%d path is: %d\n", u, v, u); 
   //else print distance and path
   }else if(getElement(L) > -1){
      fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
      fprintf(out, "A shortest %d-%d path is: ", u, v);
      printList(out, L);
      fprintf(out, "\n");
   }  
 }
//Close outfile and free allocated graph and list
fclose(out);
freeGraph(&G);
freeList(&L);

   
}
