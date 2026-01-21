#include <stdio.h>

int myst(int a, int b) {
	for ( int i = 0; i < a ; i++) {
		if (*b > 0) {
			return 1;
		}
		*b = *b + 1;
	}
	return 0;
}
void main(void) {
	int a = 5;
	int c = -10;
	int * b = &c;
	myst(a, b);
}
