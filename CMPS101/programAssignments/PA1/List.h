//---------------------------
// Name: Natalie Petrosian
// UserID: npetrosi
// Assignment: PA1
//---------------------------

typedef struct NodeObj {
      int data;
      struct NodeObj* next;
      struct NodeObj* prev;
} NodeObj;

// NodeObj
typedef NodeObj* Node;

typedef struct ListObj {
    Node head;
    Node tail;
    int numItems;
} ListObj;

// ListObj
typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// returns a List which points to a new empty list object
List newList(void);  

// frees all heap memory associated with its List* argument,  
// and sets *pL to NULL        
void freeList(List* pL);       
                               
// Access functions -----------------------------------------------------------

// Returns the number of nodes in this List.
int length(List L);            

// Returns the integer in the front Node.
// Precondition: L has at least one Node on it.
int frontValue(List L);        

// Returns the integer in the back Node.   
// Precondition: L has at least one Node on it.                      
int backValue(List L); 

// Returns the integer in Node N. 
// Precondition: N is not NULL
int getValue(Node N); 

// Returns 1 if if List A and List B are the same integer
// sequence, otherwise returns 0.
int equals(List A, List B); 
                       
// Manipulation procedures ----------------------------------------------------

// Resets this List to the empty state.
void clear(List L);

// If List is non-empty, returns the front Node, without
// changing the List.  Otherwise, does nothing.
Node getFront(List L);

// If List is non-empty, returns the back Node, without
// changing the List.  Otherwise, does nothing.
Node getBack(List L);

// Without changing the List that N is on, returns the
// Node that is previous to Node N on its List.  If
// there is no previous Node, returns NULL.
Node getPrevNode(Node N);

// Without changing the List that N is on, returns the
// Node that is next after Node N on its List.  If
// there is no next Node, returns NULL.
Node getNextNode(Node N);

// Inserts a new Node into List L before the front
// Node that has data as its value. If List is empty,
// makes that new Node the only Node on the list.
void prepend(List L, int data);  

// Inserts a new Node into List L after the back
// Node that has data as its value. If List is empty,
// makes that new Node the only Node on the list.                             
void append(List L, int data);  

// Insert a new Node into Node N’s list // before Node N that has data as its value.
// Assume that Node N is on List L.  If Node N is
// the front of List L, then N becomes the new front.
// Precondition:  Node N is not NULL
void insertBefore(List L, Node N, int data); 

// Insert a new Node into Node N’s list 
// after Node N that has data as its value.
// Assume that Node N is on List L.  If Node N is
// the back of List L, then N becomes the new back.
// Precondition:  Node N is not NULL
void insertAfter(List L, Node N, int data); 

// Deletes the front Node in List L.
// Precondition:  L has at least one Node on it.
void deleteFront(List L);

// Deletes the back Node in List L.
// Precondition:  L has at least one Node on it.
void deleteBack(List L);

// Removes N from List L by making the Node before 
// Node N link to the Node that’s after Node N as its
// next Node, and making the Node after Node N link to 
// the Node that’s before Node N as its previous Node. 
// After detachNode, Node N should have NULL as both its
// next and previous Nodes.
// Special cases:
// If Node N is the front the List L, then the Node after 
// Node N becomes the front of List L, which should have 
// a NULL previous Node.
// If Node N is the back of List L, then the Node before 
// Node N becomes the back of List L, which should have 
// a NULL next Node.
// Precondition: N is a Node that’s on List L.
void deleteNode(List L, Node N);


// Other operations -----------------------------------------------------------

// Prints the values in List L from front to back
// to the file pointed to by out, formatted as a
// space-separated string.
// For those familiar with Java, this is similar
// to toString()in Java.
 void printList(FILE* out, List L); 

