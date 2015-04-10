//--------------------------------------------------------------
////FindComponents.c
////CMPS101
////main functions that finds all the strongly connected components and prints to outfile
////Elizabeth Harris
////elbharri
////pa5
////3-13-15
////---------------------------------------------------------------
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX 2000

int main(int argc, char * argv[]){
   FILE *in, *out;
   char line[MAX];
   char* input;
   int vertex; 
   int count = 0; int i = 0; int u = 0; int v = 0;

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
  
   //initialize Graph and Stack of vertices for DFS
   Graph G = newGraph(vertex);
   List S = newList();
   for(i=1; i<=vertex; i++)
      append(S, i);
   
   //initialize i so vertices will be processed correctly
   i = 1; 
   //read in lines and get the to and from numbers
   //change them from char to ints into v and u
   //construct graph by 
   //adding arc from u to v to graph G   
   while( fgets(line, MAX, in) != NULL){
      count++;     
      input = strtok(line, " ");
      while(input != NULL){
         i++;
         if(i%2 == 0) 
            u = atoi(input);
         else
            v = atoi(input);
         
         input = strtok(NULL, " \n");
      }
      if(v > 0 && u > 0)
         addArc(G, u, v);
}

   //Print Graph and Run DFS on original graph
   fprintf(out, "Adjacency list representation of G: \n");
   printGraph(out, G);
   fprintf(out, " \n");
   DFS(G, S);

   //Transpose the Graph and Run DFS with stack from original DFS
   //to get the stack that represents the strongly connected components
   Graph T = transpose(G);
   DFS(T, S);


   //Find the number of Strongly connected components
   //By walking down the List and separating by those with nil parents
   int SCC = 0;
   moveTo(S, getOrder(G)-1);
   while(getIndex(S) != -1){
      int item = getElement(S);
      if((getParent(T, item)) == 0)
         SCC++;
      movePrev(S);
   }
   //Print number of strongly connect components
   fprintf(out, "G contains %d strongly connected components: \n", SCC);
   
 
   //create array of Lists to hold each Strongly connected component 
   List* C= calloc(count+1, sizeof(List));
   for(int i = 1; i <= SCC; i++){
      C[i] = newList();
   }
   //for each connected component, put each vertex in the list
   //put first element of new connected component(with a null parent)
   //and each following vertex in list i in the array 
   //until next component(next null  parent);
   //Walk down list forward and run for loop on array of list backward 
   //to insert the stack in the correct order in the connected components array
   moveTo(S, 0);
   for(int i = SCC; i > 0; i--){
      if(getParent(T, getElement(S)) == 0){
         append(C[i], getElement(S));
         moveNext(S);
         if(getIndex(S) != -1){
            while(getParent(T, getElement(S)) != 0){
               append(C[i], getElement(S));
               moveNext(S);
                  if(getIndex(S) == -1)
                     break;
            }
         }
      }
   }
   //print out list
   for(i = 1; i <= SCC; i++){   
      fprintf(out, "Component %d: ", i);
      printList(out, C[i]);
   }
   fclose(in);
   fclose(out);
   for(i = 1; i <= SCC; i++){
      freeList(&(C[i]));
   }
   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   free(&(*C));
   return(0); 
}

