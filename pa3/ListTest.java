// ListTest.java
// A test for the List ADT
// elbharri
// pa3
// 2-10-15

public class ListTest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();
      
      A.append("a");
      A.append("b");
      A.append("see");
      A.append(1);
      A.append(2);
      A.append(3);
      A.append(" this will work");
      A.append("I promise");
      A.append(4);
      A.append(5);
      A.append(6);
      B.prepend("2");
      B.prepend("word");
      B.prepend("funny");
      B.prepend("a");
      B.prepend("is");
      B.prepend("surprise");
      B.prepend(A);
      
      System.out.println(A);
      System.out.println(B);
      
      for(A.moveTo(0); A.getIndex()>=0; A.moveNext()){
         System.out.print(A.getElement()+" ");
      }
      System.out.println();
      for(B.moveTo(B.length()-1); B.getIndex()>=0; B.movePrev()){
         System.out.print(B.getElement()+" ");
      }
      System.out.println();
      
      List C = A.copy();
      System.out.println(A.equals(B));
      System.out.println(B.equals(C));
      System.out.println(C.equals(A));
      
      A.moveTo(1);
      A.insertBefore("cats");
      A.moveTo(3);
      A.insertAfter("cats");
      A.moveTo(1);
      A.delete();
      System.out.println(A);
      A.clear();
      System.out.println(A.length());

      B.moveTo(0);
      B.insertBefore("this");
      B.moveTo(0);
      B.insertAfter("this");
      B.moveTo(1);
      B.delete();
      System.out.println(B);
   }
}
