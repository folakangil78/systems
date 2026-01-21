#include <stdio.h>
#include <stdlib.h>

int * double(int * ptr, int size) {
	ptr = realloc(ptr, 2*size * sizeof(int)) //realloc uses same ptr and increases memory of it
	// do double code here, return ptr


}
