 //Lex.java
 //Elizabeth Harris
 //elbharri
 //pa1
 //1-16-15

import java.io.*;
import java.util.Scanner;
public class Lex{
 public static void main(String [] args) throws IOException {
      int i, output;
      //Check for enough input from user and prints out message if they don't give a file and target
      Scanner in = null;
      PrintWriter out = null;
      if(args.length < 2){
         System.out.println("Usage: FileIO infile target [target2...]");
         System.exit(1);
      }
      //Scans the file from the user and counts the lines in it
      in = new Scanner(new File(args[0]));
      int lineCount = 0;
      while( in.hasNextLine () ){
         in.nextLine();
         lineCount++;
      }
      in.close();

      //Creates String array the same size as the number of files counted; Creates int array to keep t
      //rack of line nummbers;
      //Fills the arrays with the contents of the file   
      String[] token = new String[lineCount];
      Scanner get = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      for(i = 0; i < token.length; i++){
         token[i] = get.nextLine();
      }
      get.close();
      out.close();
      i = 0;

      //make List and put in zero as first element;
      List L = new List();
      L.append(0);
      
      //Insertion sort;
      //Use array length for loop control initialized to 1 because zero is already in the list;
      //Start Cursor at index 0 in the list;
      for(i = 1; i < token.length; i++){
         L.moveTo(0);
         //While there is at least one element in the list{
         //Compare the first array element to the array element with the index stored in the list;       
         //if less; insert before and break; else move cursor to next and compare again;
         //else put on the end. 
         while(L.getIndex()>=0){
            if(token[i].compareTo(token[L.getElement()]) < 0){
               L.insertBefore(i);
               break;
            }
         L.moveNext();
         }
         if(L.getIndex() < 0){
            L.append(i);
         }
      }
      
      //Print to outfile
      //Open outfile, move cursor to index 0, prints array in order of elemements in the list.
      //Incraments cursor and array length control.
      //close outfile.
      out = new PrintWriter(new FileWriter(args[1]));
      L.moveTo(0);
      i = 0;
      while(i< lineCount){
         out.println(token[L.getElement()]);
         L.moveNext();
         i++;
      }
      out.close();    
   }
 }


