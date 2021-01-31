//-----------------------------------------------------------------------------
// Name: Natalie Petrosian
// Class: 12M
// CruzID: npetrosi
// File name: List.java
// Linked List implementation of the List ADT
//-----------------------------------------------------------------------------

@SuppressWarnings ("overrides")
public class List<T> implements ListInterface<T> {

   // private inner Node class
   private class Node {
      T item;
      Node next;

      Node(T x){
         item = x;
         next = null;
      }
   }

   // Fields for the List class
   private Node head;     // reference to first Node in List
   private int numItems;  // number of items in this List

   // List()
   // constructor for the List class
   public List(){
      head = null;
      numItems = 0;
   }


   // private helper function -------------------------------------------------

   // find()
   // returns a reference to the Node at position index in this List
   private Node find(int index){
      Node N = head;
      for(int i=1; i<index; i++){
         N = N.next;
      }
      return N;
   }


   // ADT operations ----------------------------------------------------------

   // isEmpty()
   // pre: none
   // post: returns true if this IntgerList is empty, false otherwise
   public boolean isEmpty(){
      return(numItems == 0);
   }

   // size()
   // pre: none
   // post: returns the number of elements in this List
   public int size() {
      return numItems;
   }

   // get()
   // pre: 1 <= index <= size()
   // post: returns item at position index in this List
   public T get(int index) throws ListIndexOutOfBoundsException {
      
      if( index<1 || index>numItems ){
         throw new ListIndexOutOfBoundsException(
            "get(): invalid index: " + index);
      }
      Node N = find(index);
      return N.item;
   }

   // add()
   // inserts newItem into this List at position index
   // pre: 1 <= index <= size()+1
   // post: !isEmpty(), items to the right of newItem are renumbered
   public void add(int index, T newItem) 
      throws ListIndexOutOfBoundsException{
      
      if( index<1 || index>(numItems+1) ){
         throw new ListIndexOutOfBoundsException(
            "add(): invalid index: " + index);
      }
      if(index==1){
         Node N = new Node(newItem);
         N.next = head;
         head = N;
      }else{
         Node P = find(index-1); // at this point index >= 2
         Node C = P.next;
         P.next = new Node(newItem);
         P = P.next;
         P.next = C;
      }
      numItems++;
   }

   // remove()
   // deletes item at position index from this List
   // pre: 1 <= index <= size()
   // post: items to the right of deleted item are renumbered
   public void remove(int index)
      throws ListIndexOutOfBoundsException{
      if( index<1 || index>numItems ){
         throw new ListIndexOutOfBoundsException(
            "remove(): invalid index: " + index);
      }
      if(index==1){
         Node N = head;
         head = head.next;
         N.next = null;
      }else{
         Node P = find(index-1);
         Node N = P.next;
         P.next = N.next;
         N.next = null;
      }
      numItems--;
   }

   // removeAll()
   // pre: none
   // post: isEmpty()
   public void removeAll(){
      head = null;
      numItems = 0;
   }

   // toString()
   // pre: none
   // post:  prints current state to stdout
   // Overrides Object's toString() method
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = head;

      for( ; N!=null; N=N.next){
         sb.append(N.item).append(" ");
      }
      return new String(sb);
   }

   /*--------------------------------------------------------------------------
   // This is a another version of toString() that uses recursion.  A private
   // recursive function called myString() does the real work, then is called
   // by toString()

   private String myString(Node H){
      if( H==null ){
         return "";
      }else{
         return (H.item + " " + myString(H.next));
      }
   }
   
   public String toString(){
      return myString(head);
   }
   //------------------------------------------------------------------------*/
   
   // equals()
   // pre: none
   // post: returns true if this List matches rhs, false otherwise
   // Overrides Object's equals() method
   @SuppressWarnings("unchecked")
   public boolean equals(Object rhs){
      boolean eq = false;
      List<T> R = null;
      Node N = null;
      Node M = null;

      if(rhs instanceof List){
         R = (List<T>)rhs;
         eq = ( this.numItems == R.numItems );

         N = this.head;
         M = R.head;
         while(eq && N!=null){
            eq = (N.item == M.item);
            N = N.next;
            M = M.next;
         }
      }
      return eq;
   }

}