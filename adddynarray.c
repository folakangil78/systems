#include <stdio.h>
#include <stdlib.h>

int * add_one(int * ptr, int size) {
	int * ptr_2 = (int *)malloc(size * sizeof(int))
	for (int i = 0; i < size; i++) {
		*(ptr_2 + i) = *ptr + 1; //accessing value at ptr 2 iteratively through the array, accesses value at ptr2 through the array cuz ptr2 itself points at first value
		ptr++;
	}
	return ptr_2;
}

// main method here where passing in array
// in main method or whatever method is using fxn, make sure to free() memory

//int * ptr_2 = add_one(ptr, size);
//free(ptr_2);
//good practice to also set ptr_2 = NULL;

// dynamically allocating ptr_2 allows us to use the array result in different instances outside of the function itself

