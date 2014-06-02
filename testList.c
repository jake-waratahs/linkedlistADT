//tests for the List ADT
//created by Jake Bloom
//on 15/5/2014

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"

#define DEFAULT_VALUE {1,8,7,4}
#define START_LENGTH 4

List setUpList(void);
void testAdd(void);
void testDelete(void);
void testAppend(void);
void testReverse(void);
void testZip(void);

int main (int argc, char *argv[]){

	testAdd();
	testDelete();
	testAppend();
	testReverse();
	testZip();

	printf("All tests passed! You are awesome!\n");

	return EXIT_SUCCESS;
}


List setUpList (void){
	List l = newList();
	assert(l != NULL);
	append(l, 1);
	append(l, 8);
	append(l, 7);
	append(l, 4);
//	printList(l);
	return l;
}

void testAdd (void){

	printf("Testing add!\n");

	List l = setUpList();
	assert(listLength(l) == START_LENGTH);

	//Add one element to the beginning of the list
	addElement(l, 5, 0);
	assert(getElement(l,0) == 5);
	assert(listLength(l) == START_LENGTH + 1);

	//Add one element in the middle of the list
	addElement(l, 42, 3);
//	printList(l);
	assert(getElement(l,3) == 42);
	assert(listLength(l) == START_LENGTH + 2);


	//Add one element to the end of the list
	addElement(l, 99, listLength(l));
//	printList(l);
	assert(getElement(l,listLength(l) - 1) == 99);
	assert(listLength(l) == START_LENGTH + 3);

	disposeList(l);

	printf("Adding tests passed!\n");
}

void testDelete (void){

	printf("Testing delete!\n");

	List l = setUpList();
	assert(listLength(l) == START_LENGTH);

	//Delete the first element of the list
	deleteElement(l, 0);
	assert(getElement(l, 0) == 8);
	assert(listLength(l) == START_LENGTH - 1);

	//Delete an element from the middle of the list
	deleteElement(l, 1);
	assert(getElement(l, 1) == 4);
	assert(listLength(l) == START_LENGTH - 2);


	//Delete an element from the end of the list
	deleteElement(l, listLength(l) - 1);
	assert(getElement(l, 0) == 8);
	assert(listLength(l) == START_LENGTH - 3);

	disposeList(l);

	printf("Deleting tests passed!\n");
}

void testAppend (void){

	printf("Testing Append!\n");

	List l = setUpList();
	assert(listLength(l) == START_LENGTH);

	//Append a couple of times, testing length and last
	//element each time

	append(l, 77);
	assert(getElement(l, listLength(l) - 1) == 77);
	assert(listLength(l) == START_LENGTH + 1);

	append(l, 88);
	assert(getElement(l, listLength(l) - 1) == 88);
	assert(listLength(l) == START_LENGTH + 2);

	append(l, 99);
	assert(getElement(l, listLength(l) - 1) == 99);
	assert(listLength(l) == START_LENGTH + 3);	

//	printList(l);

	printf("Appending tests passed!\n");
}

void testReverse(void){

	printf("Testing reverse!\n");

	//reverse the list once...
	List l = setUpList();
	printList(l);
	reverseList(l);
	printList(l);


	assert(getElement(l, 0) == 4);
	assert(getElement(l, 1) == 7);
	assert(getElement(l, 2) == 8);
	assert(getElement(l, 3) == 1);
	assert(listLength(l) == START_LENGTH);

	//reverse it again!
	reverseList(l);
	printList(l);
	assert(getElement(l, 0) == 1);
	assert(getElement(l, 1) == 8);
	assert(getElement(l, 2) == 7);
	assert(getElement(l, 3) == 4);
	assert(listLength(l) == START_LENGTH);

	//testing that appended items are reversed as well
	append(l, 32);
	reverseList(l);
	assert(getElement(l, 0) == 32);
	assert(listLength(l) == START_LENGTH + 1);

	printf("Reversing passed!\n");
}

void testZip (void){
	printf("Testing Zip!\n");

	List l = setUpList();
	List i = setUpList();

	assert(listLength(l) == START_LENGTH);
	assert(listLength(i) == START_LENGTH);

	List zipped = zipList(l,i);

	assert(listLength(zipped) == START_LENGTH * 2);
	assert(getElement(zipped, 1) == 1);
	assert(getElement(zipped, 3) == 8);
	assert(getElement(zipped, 5) == 7);
	assert(getElement(zipped, 7) == 4);
	printList(zipped);

	append(l,5);
	append(l,6);

	zipped = zipList(l, i);
	assert(listLength(zipped) == 10);
	assert(getElement(zipped, listLength(zipped) - 2) == 5);
	assert(getElement(zipped, listLength(zipped) - 1) == 6);
	printList(zipped);

	append(i,5);
	append(i,6);
	append(i,7);
	append(i,8);	

	zipped = zipList(l, i);
	assert(listLength(zipped) == 14);
	assert(getElement(zipped, listLength(zipped) - 2) == 7);
	assert(getElement(zipped, listLength(zipped) - 1) == 8);
	printList(zipped);

	printf("Zipping passed!\n");
}