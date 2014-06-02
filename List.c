//Linked list ADT implementation
//Implements List.h
//Created by Jake Bloom 15/5/2014

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "List.h"

//A pointer to a node, required for the second part of a node struct
typedef struct _node *nodePointer;


//The node struct, that forms each element of the list
typedef struct _node {
	int value;
	nodePointer next;
} node;

//The list concrete type, that contains a pointer to the first element of the list
typedef struct _list {
	nodePointer first;
} list;

//Create a new list by just creating a new pointer to a list struct,
//with the first element being NULL
List newList(void){
	List l = malloc(sizeof(list));
	assert(l != NULL);
	l->first = NULL;
	return l;
}

//Add an element at the end of a list
void append(List l, int value){
	addElement(l, value, listLength(l));
}

//Get an element from the list at any position
//The first element is zero
int getElement(List l, int position){
	//Protect from a segfault, ensure that the user wants an element in the list
	assert(position >= 0);
	assert(position < listLength(l));

	nodePointer current = l->first;
	int count = 0;
	
	//get the next element, until we reach the desired element
	while (count < position){;
		current = current->next;
		count++;
		assert(current != NULL);//double protection
	}
	return current->value;
}

//Delete an element from the list at any position
void deleteElement(List l, int position){
	
	//get pointers to the previous element, the next element (to join them)
	//and the element to be deleted (so that we can free() it)
	nodePointer delete;
	nodePointer previous;
	nodePointer nextNode;
	int count = 0;
	
	delete = l->first;

	//get delete to point to the node to be deleted, and previous
	//to point to the node before it
	while (count < position){
		previous = delete;
		delete = delete->next;
		count++;
		assert(delete != NULL);
	}
	//if delete is the last element in the list, then delete->next = NULL,
	//this way, nextNode is set to NULL. Then the previous node's pointer is set to NULL,
	//making it the final node.
	nextNode = delete->next;
	free(delete);
	delete = NULL;

	//If we deleted the first element, then we need to set the pointer to the first node to the new
	//first node, otherwise we join the previous and next nodes.	
	if (count == 0){
		l->first = nextNode; 
	} else {
		previous->next = nextNode;
	}
}

//Add an item from the list at any position
void addElement(List l, int value, int position){

	//make sure the user wants to insert in the values between 0 and the length of the list
	assert(position >= 0);
	assert(position <= listLength(l));//We can insert an element after the end of a list

	nodePointer previous;
	nodePointer nextNode;
	int count = 0;

	//create the new node
	previous = l->first;
	nodePointer new = malloc(sizeof(node));
	assert(new != NULL);
	new->value = value;

	//If we want to insert a new node (for example) at position 2, we need to set it's
	//pointer to the node that was previously at position 2
	while (count < position - 1){
		previous = previous->next;
		assert(previous != NULL);	
		count++;		
	}

	//If we add a node at the beginning of the list, we need to change the pointer to the
	//first node
	if (position == 0){
		new->next = l->first;
		l->first = new;
	} else {
		nextNode = previous->next;
		new->next = nextNode;
		previous->next = new;
	}
}

//Get the length of the list
int listLength(List l){
	nodePointer current = l->first;
	int counter = 0;
	while (current != NULL){
		counter++;
		current = current->next;
	}
	return counter;
}

//Print out the list
void printList(List l){
	nodePointer current = l->first;
	while (current != NULL){
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

//Get rid of the list
void disposeList(List l){
	
	//delete the last element of the list until the list is empty
	while (listLength(l) > 0){
		deleteElement(l, listLength(l) - 1);
	}

	l->first = NULL;
	free(l);
	l = NULL;
}

//Reverse the list
//This is achieved by creating a new list, and appending the last element of the old
//list until the old list is empty. Then we set the pointer to the first node of the
//old list to equal the first node of the new list, then dispose the new list, reversing
//the old list in-place.
void reverseList(List l){

	List new = newList();

	while(listLength(l) > 0){
		append(new, getElement(l, listLength(l) - 1));
		deleteElement(l, listLength(l) - 1);
	}
	l->first = new->first;

	//new is stored in the stack, so the pointer will be lost when the function
	//terminates, but just to be sure, we do a bit of garbage collection
	new->first = NULL;
	free(new);
	new = NULL;
}

//Put two lists together alternating, with the first element from the first list,
//then the first first element from the second list, then the second element from
//the first list, then the second element from the second list......
List zipList(List l, List i){

	List new = newList();
	int count = 0;

	while((count < listLength(l)) || (count < listLength(i))) {
		if (count < listLength(l)){
			append(new, getElement(l,count));
		}
		if (count < listLength(i)){
			append(new, getElement(i,count));
		}
		count++;
	}

	return new;
}
