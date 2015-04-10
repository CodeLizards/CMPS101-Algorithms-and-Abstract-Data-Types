//Sparse.java
// Main function, a client of 
// elbharri
// pa3
// 2-10-15

import java.io.*;
import java.util.Scanner;
import java.lang.Integer;
import java.lang.Double;
public class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String input[] = null;
      int row = 0, col = 0, n = 0, a = 0, b = 0, i;
      double val = 0;

      //check for input and output and print error message before quiting

      if(args.length < 2){
         System.out.println("FileIO Error: Sparse infile outfile");
	       System.exit(1);
      }
      
      //open scanner and printwriter to read and write to files
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      //read in first line to get the size, 
      //and # of entries for each matrix
      //tokenize the array and put into variables
      line = in.nextLine()+" ";
      input = line.split("\\s+");
      n = Integer.parseInt(input[0]);
      a = Integer.parseInt(input[1]);
      b = Integer.parseInt(input[2]);
       
      //make new matrices 
      Matrix M1 = new Matrix(n*n);
      Matrix M2 = new Matrix(n*n);
      
      //read in the blank line so it doesn't try and parse an empty line
      line = in.nextLine() + " ";
      
      //read in lines a amount of times for # of entries in A
      //get row column and value from each line
      for(i = 0; i < a; i++){
         line = in.nextLine()+" ";
         input = line.split("\\s+");
         row = Integer.parseInt(input[0]);
         col = Integer.parseInt(input[1]);
         val = Double.parseDouble(input[2]);
         M1.changeEntry(row, col, val);
      }
      
      //read in blank line so it doesn't try and parse empty line
      line = in.nextLine() + " ";

      //read in lines b amount of times for # of entries in Matrix1
      //get row column and value from each line and put into Matrix1
      for(i = 0; i < b; i++){
         line = in.nextLine()+"";
         input = line.split("\\s+");
         row = Integer.parseInt(input[0]);
         col = Integer.parseInt(input[1]);
         val = Double.parseDouble(input[2]);
         M2.changeEntry(row, col, val);
      }
      
        //close the infile
        in.close();

        //Print Matrix1 and Number of Non-zero entries to outfile
        out.println("A has " + M1.getNNZ() +" non-zero entries: ");
        out.println(M1);

        //Print Matrix2 and Number of Non-zero entries to outfile
        out.println("B has " + M2.getNNZ() +" non-zero entries: ");
        out.println(M2);

        //Multiply Matrix1 by scalar 1.5
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("(1.5)*A = ");
        Matrix A = M1.scalarMult(1.5);
        out.println(A);

        //Add Matrix1 and Matrix 2
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("A+B = ");
        Matrix B = M1.add(M2);
        out.println(B);

        //Add Matrix1 to itself
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("A+A = ");
        Matrix C = M1.add(M1);
        out.println(C);

        //Subtract Matrix2 from Matrix 1
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("B-A = ");
        Matrix D = M2.sub(M1);
        out.println(D);
        
        //Subtract Matrix 1 from itself
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("A-A = ");
        Matrix E = M1.sub(M1);
        out.println(E);

        //Transpose Matrix 1
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("Transpose(A) = ");
        Matrix F = M1.transpose();
        out.println(F);
        
        //Multiply Matrix1 and Matrix 2
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("A*B = ");
        Matrix G = M1.mult(M2);
        out.println(G);
        
        //Multiply Matrix 2 to itself
        //Print new Matrix and Number of Non-zero entries to outfile
        out.println("B*B = ");
        Matrix H = M2.mult(M2);
        out.println(H);
       
        //close outfile
        out.close();
   }
} 
