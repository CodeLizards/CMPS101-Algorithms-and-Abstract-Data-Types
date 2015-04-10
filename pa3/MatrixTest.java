// Matrix.java
// A test for the Matrix ADT
// elbharri
// pa3
// 2-10-15

public class MatrixTest {
   public static void main(String[] args){
      int i, j, n=100;
      Matrix A = new Matrix(n); 
      Matrix B = new Matrix(n);

      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,2,0); B.changeEntry(3,3,1);
      A.changeEntry(4,1,1); B.changeEntry(5,1,1);
      A.changeEntry(4,2,2); B.changeEntry(5,5,0);
      A.changeEntry(4,3,3); B.changeEntry(4,7,1);
      A.changeEntry(4,1,4); B.changeEntry(8,1,0);
      A.changeEntry(5,2,5); B.changeEntry(7,2,1);
      A.changeEntry(8,3,6); B.changeEntry(6,3,0);
      A.changeEntry(25,25, 25);B.changeEntry(6,1,1);
      A.changeEntry(3,10,8);B.changeEntry(6,2,1);
      A.changeEntry(10,5,9);B.changeEntry(8,1,1);

      System.out.println(A.getNNZ());
      System.out.println("A = ");
      System.out.println(A);

      System.out.println(B.getNNZ());
      System.out.println("B = ");
      System.out.println(B);

      System.out.println(A.equals(B));
      System.out.println(A.equals(A));


      Matrix C = A.scalarMult(10);
      System.out.println(C.getNNZ());
      System.out.println("A scalar 10 = ");
      System.out.println(C);

      Matrix D = A.add(B);
      System.out.println(D.getNNZ());
      System.out.println("A + B = ");
      System.out.println(D);

   
      Matrix E = B.add(A);
      System.out.println(E.getNNZ());
      System.out.println("B + A = ");
      System.out.println(E);


      Matrix F = A.add(A);
      System.out.println(F.getNNZ());
      System.out.println("A + A = ");
      System.out.println(F);

      Matrix G = B.add(A);
      System.out.println(G.getNNZ());
      System.out.println("B + A = ");
      System.out.println(G);

      Matrix H = A.transpose();
      System.out.println(H.getNNZ());
      System.out.println("A transpose = ");
      System.out.println(H);

      Matrix I = A.mult(B);
      System.out.println(I.getNNZ());
      System.out.println("A x B = ");
      System.out.println(I);

      Matrix J = A.mult(A);
      System.out.println(J.getNNZ());
      System.out.println("A x A = ");
      System.out.println(J);

      Matrix K = A.copy();
      System.out.println(K.getNNZ());
      System.out.println("A copy = ");
      System.out.println(K);

      System.out.println(A.equals(K));
      
     

      B.makeZero();
      System.out.println(B.getNNZ());
      System.out.println(B);
      
   }
}








