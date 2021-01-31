//-----------------------------------------------------------------------------
// Name: Natalie Petrosian
// CruzID: npetrosi
// Class: 12B
// This program contains five recursive methods. Comments preceding each method
// briefly describe the method. 
// File name: Recursion.java
// 
//-----------------------------------------------------------------------------

class Recursion {

   // saves the reversal of the leftmost n elements in X, into array Y
   static void reverseArray1(int[] X, int n, int[] Y) {
      // if n==0 do nothing
      if(n > 0) { 
         Y[Y.length-n] = X[n-1]; // saves nth element from left
         reverseArray1(X, n-1, Y);          // saves leftmost n-1 elements, reversed
      }
   }
   
   // saves the reversal of the rightmost n elements in X, into array Y
   static void reverseArray2(int[] X, int n, int[] Y) {
      // if n==0 do nothing
      if( n>0 ){
         Y[n-1] = X[X.length-n];
         reverseArray2(X, n-1, Y);       //saves the rightmost n-1 elements, reversed
      }
   }

   // swaps the elements at positions i and j recursively
   static void reverseArray3(int[] X, int i, int j){
      int temp;
      if(j >= i){
         temp = X[j];
         X[j] = X[i];
         X[i] = temp;
         reverseArray3(X, i+1, j-1);
      }
   }

   // returns the index of the largest element in the array
   static int maxArrayIndex(int[] X, int p, int r){
      int q;
      int leftHalfMaxIndex;
      int rightHalfMaxIndex;

      if(p < r){
         q = (p+r)/2;
         leftHalfMaxIndex = maxArrayIndex(X, p, q);
         rightHalfMaxIndex = maxArrayIndex(X, q+1, r);

         if(X[leftHalfMaxIndex] < X[rightHalfMaxIndex]){
            return rightHalfMaxIndex;
         }
         else{
            return leftHalfMaxIndex;
         }
      }
      else{
         return p;
      }
   }

   // returns the index of the smallest element in the array
   static int minArrayIndex(int[] X, int p, int r){
      int q;
      int leftHalfMaxIndex;
      int rightHalfMaxIndex;

      if(p < r){
         q = (p+r)/2;
         leftHalfMaxIndex = minArrayIndex(X, p, q);
         rightHalfMaxIndex = minArrayIndex(X, q+1, r);

         if(X[leftHalfMaxIndex] < X[rightHalfMaxIndex]){
            return leftHalfMaxIndex;
         }
         else{
            return rightHalfMaxIndex;
         }
      }
      else{
         return p;
      }
   }


   // This is the main routine of Recursion.java
   // It calls the other methods in this class as described 
   // in the rubric for Programming Assignment 1

   public static void main(String[] args) {
      int[] A = {-1, 2, 6, 12, 9, 2, -5, -2, 8, 5, 7};
      int[] B = new int[A.length];
      int[] C = new int[A.length];
      int minIndex = minArrayIndex(A, 0, A.length-1);
      int maxIndex = maxArrayIndex(A, 0, A.length-1);

      for(int x: A) System.out.print(x+" ");
      System.out.println();

      System.out.println("minIndex = " + minIndex);
      System.out.println("maxIndex = " + maxIndex);
      
      reverseArray1(A, A.length, B);  // print all elements in reverse order
      for(int x: B) System.out.print(x+" ");
      System.out.println();

      reverseArray2(A, A.length, C);  // do it again, differently
      for(int x: C) System.out.print(x+" ");
      System.out.println();

      reverseArray3(A, 0, A.length-1);
      for(int x: A) System.out.print(x+" ");
      System.out.println();

   }
 }
