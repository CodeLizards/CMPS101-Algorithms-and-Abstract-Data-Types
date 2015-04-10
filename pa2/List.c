//-----------------------------------------------------------------------------
// List.c
//CMPS101
//Elizabeth Harris
//elbharri
//pa2
//1-23-15
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev=NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while( !isEmpty(*pL) ) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------


// getLength()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}

//getIndex(List L)
//returns index
int getIndex(List L){
   if( L==NULL ){
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }return(L->index);

}

// front()
// Returns the value at the front of L.
// // Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

//int back(List L)
//returns back element in list
int back(List L){
    if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);

}

//getElement()
//returns element at cursor
int getElement(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int flag = 1;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}
// Manipulation procedures ----------------------------------------------------

//clear()
//clears list to null state
void clear(List L){
   int i;
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
  // for(i = 0; i<L->length-1;)
}

//moveto()
//moves cursor to index specified
void moveTo(List L, int i){
   int n;
   if( L==NULL ){
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveTo() on an empty List\n");
      exit(1);
   }else if(i <= L->length-1 && i >= 0){
      L->cursor = L->front;
      for(n = 1; n <= i; n++){
         L->cursor = L->cursor->next;
      }
      L->index = i;
   }

}

//moves cursor to previous node
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveTo() on an empty List\n");
      exit(1);
   }else if(L->index == -1 || L->index == 0){
         L->cursor = NULL;
         L->index = -1;
      }
      else if(L->index > 0 && L->index <= L->length-1){
         L->cursor = L->cursor->prev;
         L->index--;
      }

}

//moveNext(List L)
//moves cursor to next node
void moveNext(List L){
   if( L==NULL ){
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveTo() on an empty List\n");
      exit(1);
   }else if(L->index == -1 || L->index == (L->length)-1){
         L->cursor = NULL;
         L->index = -1;
   }
   else if(L->index >= 0 && L->index <= (L->length)-1){
         L->cursor = L->cursor->next;
         L->index++;
      }

}

//prepend(List L, int data)
//inserts new data element at the front of List L
void prepend(List L, int data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling EnList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { L->front = L->back = N; }
   else { 
      L->front->prev = N;
      N->next = L->front; 
      L->front = N;
      L->index++;
   }
   L->length++;
}

// EnList()
// Places new data element at the end of L
void append(List L, int data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling EnList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { L->front = L->back = N; }
   else {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

//insertBefore(List L, int data);
//Places new data element before cursor
void insertBefore(List L, int data){
   Node N = newNode(data);
   if( L==NULL ){
      printf("List Error: calling EnList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { L->front = L->back = N; }
   else{
      N->next = L->cursor;
      if(L->cursor->prev != NULL){
         N->prev = L->cursor->prev;
         (L->cursor->prev->next) = N;
      }
      L->cursor->prev = N;
      if(N->prev == NULL)
         L->front = N;
   }
   L->index++;
   L->length++;
}

//insertAfter(List L, int data);
//places new data element after cursor
void insertAfter(List L, int data){
   Node N = newNode(data);
   if( L==NULL ){
      printf("List Error: calling EnList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      L->front = L->back = N;
      L->index++;
   }else{
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next = N;
      if(N->next == NULL)
         L->back = N;
   }
   L->length++;
}

// DeleteFront()
// Deletes element at front of L
// Pre: !isEmpty(Q)
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling Delete front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling Delete front on an empty List\n");
      exit(1);
   }
   if(L->index == 0){
      L->index = -1;
      L->cursor = NULL;
   }
   N = L->front;
   if( length(L) > 1 ) { L->front = L->front->next; }
   
   L->length--;
   //N = NULL;
   freeNode(&N);
}

//DeleteBack
//deletes element at the back of the list
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( L->length > 1 ) {L->back = L->back->prev; }
   else {
      L->front = L->back = NULL;
      //freeNode(L->front);
   }
   L->length--;
   N = NULL;
   freeNode(&N);
}

//delete
//delete element at cursor
void delete(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }else if(getIndex(L) == -1){
      printf("List Error: calling delete on a null cursor");
      exit(1);
   }else if(getIndex(L) >= 0){
      if(L->cursor->prev == NULL){
         L->front = L->cursor->next;
      }
      else if(L->cursor->next == NULL){
         L->back = L->cursor->prev;
      }
      N = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor = NULL;
      L->length--;
      L->index = -1;
      freeNode(&N);
   }


}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}

   // copy(): returns a new List identical to this one.
   List copyList(List L){
      List A = newList();
      Node N = L->front;

      while( N!=NULL ){
         append(A, N->data);
         N = N->next;
      }
      return A;
   }

 
