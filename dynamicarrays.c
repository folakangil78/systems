#include <stdio.h>
#include <stdlib.h>

int * add_one(int * ptr, size) {
	int * ptr_2 = (int *) malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		*(ptr_2+i) = *(ptr+i) + 1; // points to an array where element is incremented by one
	}
	return ptr_2;

}

int main(int argc, char * argv[]) {
	int * ptr = (int *) malloc((argc-1)*sizeof(int));
	for (int i = 0; i < (argc-1); i++) {
		*(ptr+i) = argv[i];
	}
	
	int * ptr_1 = add_one(ptr,argc-1);
	free(ptr_1);
	free(ptr);
	return 0;
}
