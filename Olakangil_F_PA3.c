/*I Francis Olakangil certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _sampleNode {
	int ID;
	double value;
	struct _sampleNode * next;
} SampleNode;

typedef struct _dataSet {
	SampleNode * samples;
	int nSamples;
	double minSample;
	double maxSample;
} DataSet;

void updateMax(DataSet * set) {
	double max_val = set -> samples -> value; // accesses first value of given node in list of samples (samplenodes)
	
	SampleNode * currentNode = set -> samples; // ptr to first sample node in l.list

	while (currentNode != NULL) {
		if (currentNode -> value > max_val) { // accesses value of current node and compares to max which was initialized to value of first node in list
			max_val = currentNode -> value;
		}
		currentNode = currentNode -> next; // iterates current to next node
	}
	
	set -> maxSample = max_val;
}

void updateMin(DataSet * set) {
	double min_val = set -> samples -> value;

	SampleNode * currentNode = set -> samples;

	while (currentNode != NULL) { // iterates as long as value within next node
		if (currentNode -> value < min_val) {
			min_val = currentNode -> value;
		}
		currentNode = currentNode -> next;
	}

	set -> minSample = min_val;
}

int addSample(DataSet * set, int SampleID, double value) {
	SampleNode * currentNode = set -> samples;

	while (currentNode != NULL) {
		if (currentNode -> ID == SampleID) { // compares id attribute of node struct to id param of func
			return -1;
		}
		currentNode = currentNode -> next;
	}

	SampleNode * addedNode = (SampleNode *)malloc(sizeof(SampleNode)); // allocate memory for node insertion
	
	set -> nSamples++; // increments total number of nodes in list	

	addedNode -> value = value; // sets value attrib to value of value param
	addedNode -> ID = SampleID;
	addedNode -> next = set -> samples; // sets ptr of new node to current head of list

	set -> samples = addedNode; // actually inserts node at beginning of set

	updateMin(set);
	updateMax(set);

	return 0;
}

SampleNode * findSample(DataSet set, int sampleID, int * location) {
	SampleNode * currentNode = set.samples; // need to use . operator rather than arrow bc set param is value of struct, not ptr to dataset struc
	// . operator accesses samples head attribute directly, arrow would be for * set (5.4. Structures And Pointers Weber State University)
	
	int index_loc = 0; // need tracker of indices for list iteration

	while (currentNode != NULL) {
		if (currentNode -> ID == sampleID) {
			*location = index_loc; // derefernces loc ptr to initialize value it pts to as index of matching node
			return currentNode;
		}
		index_loc++;
		currentNode = currentNode -> next;
	}
	*location = -1;
	return NULL; // indicates no node with matching id found
}

int size(DataSet set) {
	SampleNode * currentNode = set.samples; // again impt note to use . operator for plain struct value set as param rather than ptr to dataset struct
	int size = 0;

	while (currentNode != NULL) {
		size++; // increments counter of nodes
		currentNode = currentNode -> next;
	}
	return size;
}

int isEmpty(DataSet set) {
	SampleNode * currentNode = set.samples;
	if (currentNode == NULL) {
		return 1;
	}
	return 0;
}

int removeSample(DataSet * set) {
	SampleNode * initial_headNode = set -> samples;
	// caches current node at head of list to be free later
	
	set -> samples = set -> samples -> next;
	// moves head ptr of samples list to next node

	set -> nSamples--;
	// decrements total number of nodes in list being tracked

	free(initial_headNode);
	
	updateMin(set);
	updateMax(set);
	
	return 0;
}

void deleteSet(DataSet * set) {
	SampleNode * currentNode = set -> samples;

	SampleNode * subsequent_Node; // used to cache following node before freeing current

	while (currentNode != NULL) {
		subsequent_Node = currentNode -> next;
		free(currentNode);
		currentNode = subsequent_Node;
		// need to initialize subsequent with .next of current before freeing bc current=null after freeing
	}

	// freeing other dataset attributes below to make sure attribs don't pt to freed memory of SampleNode
	set -> maxSample = 0.0;
	set -> minSample = 0.0;
	set -> nSamples = 0;

	set -> samples = NULL; // ensures that any nodes (or ptrs to nodes in this case) that weren't freed in while loop are dealt with
}

void printSamples(DataSet * set) {
	SampleNode * currentNode = set -> samples;

	while (currentNode != NULL) {
		printf("Node memory address: %p\n", currentNode);
		printf("Given node's ID: %d\n", currentNode -> ID);
		printf("Given node's actual sample value: %f\n", currentNode -> value);
		
		currentNode = currentNode -> next;
	} // applies specific format specifiers for different types of quantites being printed as per declarations in SampleNode struct

	// impt note: could have considered printing all elements of samplenode struct in one shot (excluding address of struct) by just dereferencing the currentNode pointer
	// however, printf fxn doesn't support printing all contents of struct with one singular format specifier and one variable (the deref ptr in this case) bc struct doesn't contain singular double/int/quantity
	// only case where you could pass in a dereferenced ptr as the variable for printf is if there's one struct attribute and you're sure you're using correct format specifier
}

int main(int argc, char * argv[]) {
	return 0;
}





