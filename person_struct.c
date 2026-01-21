#include <stdio.h>
#include <stdlib.h>

void intializePerson (Person * person, const char * fn, const char* ln, const char * title, uint age) {
	person->firstName = (char *)malloc(strlen(fn) + 1);
	person->lastName = (char *)malloc(strlen(ln) + 1);
	person->title = (char *)malloc(strlen(title) + 1);

	strcpy(person->firstName, fn);
	person->age = age;
	strcpy(person->lastName, ln);
	strcpy(person->title, title;

}

void deallocatePerson(Person * person) {
	// individually free all attributes of person struct

}

// btw strlen fxn can take in ptrs to strings and actual string quantities, in first fxn we passing in a string ptr to it

//printing out content of a linkedlist

void printList(LinkedList * list) {
	Node * temp = list->head;
	int SIZE = size(list);
	
	for (int i = 0; i < SIZE; i++) {
		printf("%i \n", temp->data);
		temp = temp->next;
	}
}
