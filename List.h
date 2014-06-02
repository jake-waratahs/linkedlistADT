// Linked list ADT header file
// Includes interface functions for the list type.
//Created by Jake Bloom on 15/5/2014

//type definition of a List
typedef struct _list *List;

//Create a new list
List newList(void);

//Add an element at the end of a list
void append(List l, int value);

//Get an element from the list at any position - the first element is position 0
int getElement(List l, int position);

//Delete an element from the list at any position
void deleteElement(List l, int position);

//Add an item from the list at any position - we can add elements at the end of the list, even
//though we also have the append() function
void addElement(List l, int value, int position);

//Get the length of the list
int listLength(List l);

//Print out the list
void printList(List l);

//Get rid of the list
void disposeList(List l);

//Reverse the list (in place)
void reverseList(List l);

//Put two lists together alternating, with the first element from the first list,
//then the first first element from the second list, then the second element from
//the first list, then the second element from the second list......
//Just like a metal zipper on a backpack or jeans
List zipList(List l, List i);