// List.java
// An integer List ADT
// elbharri
// pa1
// 1-16-15

class List{

   private class Node{
      // Fields
      int data;
      Node next;
      Node prev; 
      // Constructor
      Node(int data) { this.data = data; next = null; prev = null;}
      // toString:  Overides Object's toString method.
      public String toString() { return String.valueOf(data); }
   }

   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index = -1; 

   // Constructor
   List() { front = back = null; length = 0; }


   // Access Functions //////////////////////////////////////////////////////////////////

   // Returns number of elements in this list.
   int length(){
      return length;

   }
   // Returns the index of the cursor element in this list, or
   //returns -1 if the cursor element is undefined.
   int getIndex(){
      return index;

   }

   // isEmpty(): returns true if this is an empty List, false otherwise
   boolean isEmpty() { return length==0; }

   // Returns front element in this list. Pre: length()>0
   int front(){
       if( this.isEmpty() ){
         throw new RuntimeException("List Error: front() called on empty List");
      }
      return front.data;

   }
   // Returns back element in this list. Pre: length()>0
   int back(){
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: back() called on empty List");
      }
      return back.data;
   }

   // Returns cursor element in this list. Pre: getIndex () >=0
   int getElement(){
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: getElement called on empty List");
      }
      return cursor.data;
   }

   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L){
      boolean flag  = true;
      Node N = this.front;
      Node M = L.front;

      if( this.length==L.length ){
         while( flag && N!=null){
            flag = (N.data==M.data);
            N = N.next;
            M = M.next;
         }
         return flag;
      }else{
         return false;
      }
   }

   // Manipulation procedures-----------------------------------
   // Re-sets this List to the empty state.
   void clear(){
      front = back = null;
      cursor = null; 
      length = 0;
      index = -1;
   }

   // If 0<=i<=length()-1, moves the cursor to the element
   // at index i, otherwise the cursor becomes undefined.
   void moveTo(int i){
      int n;
      if(this.isEmpty() ){
         throw new RuntimeException("List Error: moveTo called on empty List");
      }else if(i <= length-1 && i >= 0){
         cursor = front;
         for(n = 1; n<=i; n++){
            cursor = cursor.next;
         }
         index = i; 
         
      }

   }
   
   // If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined.
   // If getIndex()==-1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   void movePrev(){
      if(index == 0 || index == -1 ){
         cursor = null;
         index = -1;
      }else if(index > 0 && index <= length-1){
         cursor = cursor.prev;
         index--;
      }

   }
   
   // If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If getIndex()==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   void moveNext(){
      if(index == length-1){
         cursor = null;
         index = -1;
      }
      else if(index == -1){
         cursor = null;
         index = -1;
      }
      else if(index >= 0 && index < length-1){
         cursor = cursor.next;
         index++;
      }

   }

   // Inserts new element before front element in this List.
   void prepend(int data){
      Node node = new Node(data);
      if( this.isEmpty() ){front = back = node; }
      else{
         front.prev = node;
         node.next = front;
         front = node; 
         index++;
      }
      length++;

   }

   // Inserts new element after back element in this List.
   void append(int data){
      Node node = new Node(data);
      if( this.isEmpty() ) { front = back = node; }
      else { 
         back.next = node; 
         node.prev = back;
         back = node; 
      }
      length++;
   }

   // Inserts new element before cursor element in this List. Pre: length()>0, getIndex()>=0
   void insertBefore(int data){
      Node node = new Node(data);
      if( this.isEmpty() ){front = back = node; }
      else{
         node.next = cursor;
         if(cursor.prev != null){
         node.prev = cursor.prev;
         (cursor.prev).next = node;
         }
         cursor.prev = node;
         if (node.prev == null)
      	    front = node;
      }
      index++;
      length++;
   }

   // Inserts new element after cursor element in this
   // List. Pre: length()>0, getIndex()>=0
   void insertAfter(int data){
      Node node = new Node(data);
      if(this.isEmpty() ){
         front = back = node;
      	 index++;
      }else{
         (cursor.next).prev = node;
      	 node.next = cursor.next;
      	 node.prev = cursor;
      	 cursor.next = node;
      	 if(node.next == null)
      	   back = node; 

      }
      length++;
   }
   
   // Deletes the front element in this List. Pre: length()>0
   void deleteFront(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: Delete front() called on empty List");
      }
      if(this.length>1) {
         front.next.prev = null;
      	 front = front.next;
      } else {
      front = back = null;
      }
      length--;
      index--;
   }

   // Deletes the back element in this List. Pre: length()>0
   void deleteBack(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: DeleteBack called on empty List");
      }
      if(this.length>1){
         back.prev.next = null;
      	 back = back.prev; 
         length--;     
      }
   }
   
   // Deletes cursor element in this List. Cursor is undefined after this
   // operation. Pre: length()>0, getIndex()>=0
   void delete(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: delete called on an empty list");
      }else if(index<0){
         throw new RuntimeException("List Error: delete called on a null cursor");
      }else if(index>=0){
         cursor.prev.next = cursor.next;
         cursor.next.prev = cursor.prev;
         cursor = null;
         length--;
         index = -1;
      }   
   }
   //Other methods------------------------------------------

   // Overides Object's toString method. Creates a string
   // consisting of a space separated sequence of integers 
   // with front on the left and back on the right. The
   // cursor is ignored.
   public String toString(){
      String str = "";
      for(Node N=front; N!=null; N=N.next){
         str += N.toString() + " ";
      }
      return str;
   }
   
   // copy(): returns a new List identical to this one.
   // Returns a new list representing the same integer sequence as this
   // list. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged.
   List copy(){
      List L = new List();
      Node N = this.front;
      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   }
 

}

