// Matrix.java
// A Matrix ADT, which is a Client of the List ADT 
// elbharri
// pa3
// 2-10-15



class Matrix{
   
   private class Entry{
      //Fields
      private int column;
      private double value;
      
      //Constructor
      //makes new entry
      Entry(int c, double v){
         column = c;
         value = v;
      }
   //toString function for Entry
   public String toString(){
      String a = "(";
      a += String.valueOf(this.column) + ",";
      a += String.valueOf(this.value) + ")";
      return a;
   }
      
   }

   //Fields
   //non-zero entries in matrix
   private int NNZ = 0;
   //size of matrix 
   private int size;
   //array of rows(lists)
   List row[];

   // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int i){
        if( i < 1){
         throw new RuntimeException("Matrix error: Matrix size is too small");
      }
      //make array of lists
      size = i;
      row = new List[i];
      for (i = 0; i < size; i++)
         row[i] = new List();
  
   }
 //toString method that overrides Lists to string
 public String toString(){
      String a = "";
      int i;
      for(i = 0; i < row.length; i++){
         if(!row[i].isEmpty()){
            a += i+ ":"; 
            a += String.valueOf(row[i]) + "\n" ;
         }
      }
      return a;
  
}
   ////Access functions-------------------------------

   //getSize() 
   // Returns n, the number of rows and columns of this Matrix
   int getSize(){
      return size;
   }

   //getNNZ() 
   //Returns the number of non-zero entries in this Matrix
   int getNNZ(){
   	  return NNZ; 
   }

   //equals()
   //overrides Object's equal() method
   public boolean equals(Object x){
         boolean equal = false;
         int i = 0;
         if(getSize() == ((Matrix) x).getSize()){
            equal = true;
            while(i < this.getSize() && equal ){
               equal = row[i].equals(((Matrix)x).row[i]);
               i++;
            }
         }
           return equal;
   }

   ////Manipulation procedures
   
   //makeZero()
   //sets this Matrix to the zero state
   void makeZero(){
      for(int i = 0; i < size; i++)
         row[i].clear();
          NNZ = 0;

   }

   //copy()
   //returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
      Matrix M = new Matrix(size);
      for(int i = 0; i < size; i++){
         M.row[i] = row[i].copy();
      }
      M.NNZ = NNZ;
      return M;

   }


   //changeEntry()
   //changes ith row, jth column of the matrix to x
   //pre: 1 <= i <= getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      Entry E = new Entry(j,x);
    
    //if inserting a non-zero value into a non-zero space 	
	 if(x !=0 && row[i].isEmpty() == false){
         row[i].moveTo(0);
         //while havent walked of the end of the list
         while(row[i].getIndex() != -1){
            //if the column of new entry == column of old
            //insert before and delete old entry to replace it
            if(((Entry)row[i].getElement()).column == j){
                row[i].insertBefore(E);
                row[i].delete();
            	break;
            //if entry column at cursor is less than new entry column
            //move cursor to next
            }else if(((Entry)row[i].getElement()).column < j){
            	row[i].moveNext();
            //if entry column at cursor is greater than new entry column
            //insert and add to non zero elements
            }else if(((Entry)row[i].getElement()).column > j){
            	row[i].insertBefore(E);
                NNZ++;
                break; 
            }
         }
         //if broke out of while loop because walked of end, append at end
         if(row[i].getIndex() == -1){
         	row[i].append(E);
         	NNZ++;
         }
      //else if inserting a non-zero entry into an empty row, append at end
      }else if(x != 0 && row[i].isEmpty() == true){ 
        row[i].append(E);
         NNZ++;
      //else if inserting a zero into a non-zero row
      }else if( x == 0 && row[i].isEmpty() == false){
         row[i].moveTo(0);
         //while we haven't walked off end of list
         while(row[i].getIndex() != -1){
            //if inserting zero where existing entry is, 
            //just delete existing entry
            if(((Entry)row[i].getElement()).column == j){
            	row[i].delete();
            	NNZ--;
            	break;
            //else if the new entry column is less than cursor, move next
            }else if(((Entry)row[i].getElement()).column < j)
               row[i].moveNext();
         }
      }      
   }
   
   //dot()
   //gets dot product of rows in matrix
   //takes in two lists
   private static double dot(List L, List Z){
      double sum = 0;
      double i = 0;
      if(L.isEmpty() == true || Z.isEmpty() == true){
         sum = 0;
      }else{
         L.moveTo(0);
         Z.moveTo(0);
      }
      //if both not off end, since if one is 0, dot product is zero
      //if one is less than the other move next until they are equal
      //then add product of entries with matching columns
      //add that number to sum and continue down list
      while(L.getIndex() != -1 && Z.getIndex() != -1){
         if((((Entry)L.getElement()).value) == 0)
            L.moveNext();        
         else if((((Entry)Z.getElement()).value) == 0)
            Z.moveNext();
         else if((((Entry)L.getElement()).column) < (((Entry)Z.getElement()).column))
        	L.moveNext();
         else if((((Entry)L.getElement()).column) > (((Entry)Z.getElement()).column))
            Z.moveNext();
         else if((((Entry)L.getElement()).column) == (((Entry)Z.getElement()).column)){
                i =( (((Entry)L.getElement()).value) * (((Entry)Z.getElement()).value));
                sum += i;
                L.moveNext();
                Z.moveNext();
         }         
      }
      
      return sum;
   }
   
   //scalarMult
   //returns a new Matrix that is the scalar product of this Matrix with x
   //pre: none; 
   Matrix scalarMult(double x){
      int i, b = 0;
      double a = 0, c = 0;
      Entry E;
      Matrix M = new Matrix(size);
      M.NNZ = NNZ;
      //iterate through array rows
      for(i = 0; i < row.length; i++){
         if(row[i].isEmpty() == false){
            row[i].moveTo(0);
            //iterate through each row
            //insert 1.5 times each entry into new Matrix
            while(row[i].getIndex() != -1){
               a =(((Entry)row[i].getElement()).value); 
               b =(((Entry)row[i].getElement()).column);
               c = a*x;
               E = new Entry(b, c); 
               M.row[i].append(E);
               row[i].moveNext();
            }            
         }
      }return M;
   }
 

   //add
   //returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize() 
   Matrix add(Matrix M){
      if(getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: Matrices must be the same size");
      }
      int i, c = 0, e2 = 0;
      double v1 = 0, v2 = 0;
      List M1, M2, M3;
      Matrix A = new Matrix(size);
      //iterate through array of rows
      for(i = 0; i < row.length; i++){
         M1 = M.row[i];
         M2 = this.row[i];
         //if Matrix 1 is empty and this.matrix is not empty
         //put entries of row of matrix 1 into new matrix
         if(M1.isEmpty() && !M2.isEmpty()){
            M2.moveTo(0);
            while(M2.getIndex() != -1){
               A.changeEntry(i, ((Entry)M2.getElement()).column, ((Entry)M2.getElement()).value);
               M2.moveNext();
               A.NNZ++; 
            }
         //do the same for vice versa
         }else if(!M1.isEmpty() && M2.isEmpty()){
            M1.moveTo(0);
            while(M1.getIndex() != -1){
               A.changeEntry(i, ((Entry)M1.getElement()).column, ((Entry)M1.getElement()).value);
               M1.moveNext();
               A.NNZ++; 
            }
         //else if both rows are not empty
         }else if(!M1.isEmpty() && !M2.isEmpty()){
            M2.moveTo(0);
            M1.moveTo(0);
            //while both havent walked off the end of the list
            //if equal change entry in new matrix to either value
            while(M1.getIndex() != -1 && M2.getIndex() != -1){
                  if(((Entry)M1.getElement()).column == ((Entry)M2.getElement()).column){
                     v1 = ((Entry)M1.getElement()).value;
                     v2 = ((Entry)M2.getElement()).value;
                     c = ((Entry)M2.getElement()).column;
                     A.changeEntry(i, c, (v1+v2));
                     M1.moveNext();
                     //if matrix are equal do not move next twice 
                     if(!this.equals(M))
                        M2.moveNext();
                  //else if matrix 1 is less, insert matrix 1 and move next
                  }else if(((Entry)M1.getElement()).column < ((Entry)M2.getElement()).column){
                     v1 = ((Entry)M1.getElement()).value;
                     c = ((Entry)M1.getElement()).column;
                     A.changeEntry(i, c, v1);
                     M1.moveNext();
                     A.NNZ++;
                  //else if matrix 2 is less, insert matrix 2 entry and move next
                  }else if(((Entry)M1.getElement()).column > ((Entry)M2.getElement()).column){
                     v2 = ((Entry)M2.getElement()).value;
                     c = ((Entry)M2.getElement()).column;
                     A.changeEntry(i, c, v2);
                     M2.moveNext();
                     A.NNZ++;
                  }
            }
            //if out of the while loop because walked off the list 1
            //change entry to list 1 entry
            while(M1.getIndex() != -1){
               A.changeEntry( i, ((Entry)M1.getElement()).column, ((Entry)M1.getElement()).value);
               M1.moveNext();
               A.NNZ++;
            }
            //if out of the while loop because walked off the list 2
            //change entry to list 2 entry
            while(M2.getIndex() != -1){
               A.changeEntry(i , ((Entry)M2.getElement()).column, ((Entry)M2.getElement()).value);
               M2.moveNext();
               A.NNZ++;  
            }
         }         
      }
      return A;        
   }

   //sub
   //Returns a new matrix that is the difference of this Matrix with M;
   //// pre: getSize()==M.getSize()
   Matrix sub(Matrix M){
      if(getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: Matrices must be the same size");
      }
      //add the negative
      Matrix A = new Matrix(size);
      M = (M.scalarMult(-1)); 
      A = (this.add(M));
      return A;
   }
  
   //transpose
   //returns a new Matrix that is the transpose of this Matrix
   //pre: none
   Matrix transpose(){
      Matrix M = new Matrix(size);
      Entry E = new Entry(0,0);
      //iterate through rows
      //while row is not null
      //change entry in new matrix which the columns and rows switched
      for(int i = 0; i < size; i++){
         if(!row[i].isEmpty()){
            row[i].moveTo(0);
            while(this.row[i].nullCursor() == false){
               E = (Entry)this.row[i].getElement();
               M.changeEntry(E.column, i , E.value);//column-1, i+1
               this.row[i].moveNext();
            }
         }
      }return M;
   }
 
   //mult
   //returns a new Matrix that is the product of this Matrix with M
   //pre: getSize() == M.getSize()
   Matrix mult(Matrix M){
      Matrix MUL = new Matrix(size);
      if (this.getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: Matrices must be the same size");
      } 
      //transpose matrix
      Matrix TM = M.transpose();
      int i, j;
      double x=0;
      //iterate through array of rows of matrix 1
      for(i = 0; i < row.length; i++){
         //if the row isnt empty
         //iterate through rows of matrix 2
         //get the dot product of each row
         //insert into new matrix at row of matrix 1 and column of matrix 2
         if(!this.row[i].isEmpty()){
            for(j = 0; j < TM.row.length; j++){
               x = dot(this.row[i], TM.row[j]);
                  MUL.changeEntry(i, j, x);
            }
         }
      }
      return MUL; 
   }
}
