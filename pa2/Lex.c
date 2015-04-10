 //Lex.java
 //Elizabeth Harris
 //elbharri
 //pa2
 //1-23-15
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){
 int i, ret, count=0;
   FILE *in, *out;
   char line[MAX_LEN];

    // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   //count the lines
   while(fgets(line, MAX_LEN, in) !=NULL){
      count++;
   }
   //allocate array of strings
   char array[count][MAX_LEN];
   //go back up to top of file
   rewind(in);
   //loop control set to zero 
   i = 0;
   //read in line and put in array using strcopy
   while(fgets(line, MAX_LEN, in) != NULL){
      //printf("while loop\n");
      strcpy(array[i], line);
      i++;
   }
   //close the infile
   fclose(in);
   //check if file is in array
   //for(i=0;i<count; i++)
   //   printf(" %s", array[i] );
   
   //make List and put in zero as first element;
   List L = newList();
  // printf("%d" ,i );

   append(L, 0);

   //Insertion sort;
      //Use array length for loop control initialized to 1 because zero is already in the list;
      //Start Cursor at index 0 in the list;
      for(i = 1; i < count; i++){
         moveTo(L,0);
        // printf("%d" ,i );
      
         //While there is at least one element in the list{
         //Compare the first array element to the array element with the index stored in the list;       
         //if less; insert before and break; else move cursor to next and compare again;
         //else put on the end. 
         while(getIndex(L)>=0){
            char *word1 = array[i];
            char *word2 = array[getElement(L)];
            ret = strncmp(word2, word1, MAX_LEN);
            if(ret > 0){
               insertBefore(L, i);
               break;
            }
            moveNext(L);
         }
         if(getIndex(L) < 0){
            append(L, i);
         }
      }

   //Print to outfile
   //Open outfile, move cursor to index 0, prints array in order of elemements in the list.
   //Incraments cursor and array length control.
   //close outfile.
   moveTo(L, 0);
   i = 0;
   while(i<count){
      fprintf(out, "%s\n", array[getElement(L)]);
      moveNext(L);
      i++;

   }
   fclose(out);
   //freeList(L); 
}


