
//-----------------------------------------------------------------------------
// List.h
// CMPS101
// Elizabeth Harris
// elbharri
// pa3
// 2-27-15
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of L.
int length(List L);

//getIndex()
//Returns the index of L cursor.
int getIndex(List L);


// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

//back()
//Returns the value at the back of L
int back(List L);

//getElement()
//Returns data at cursor of L
int getElement(List L);

//equals()
//checks if two lists are equal
int equals(List A, List B);



// Manipulation procedures ----------------------------------------------------

//clear()
//clears list L
void clear(List L);

//moveTo(List L, int i);
//moves cursor to index i of list l
void moveTo(List L, int i);

//movePrev(List L);
//moves cursor to previous index in list L
void movePrev(List L);

//moveNext(List L)
//moves cursor to previous index in list L
void moveNext(List L);


// append()
// Places new data element at the end of L
void append(List L, int data);

//prepend()
//Places new data element at the front of L
void prepend(List L, int data);

//insertBefore()
//Places new data element before cursor in list L
void insertBefore(List L, int data);

//insertAfter()
//Places new data element after cursor in list L
void insertAfter(List L, int data);


// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L);

//deleteBack()
//deletes element at the back of L
//Pre: !isEmpty(L);
void deleteBack(List L);

//delete()
//deletes element at cursor in list L
//Pre !isEmpty(L)
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

//copyList();
//returns a new List identical to this one.
List copyList(List L);
#endif
