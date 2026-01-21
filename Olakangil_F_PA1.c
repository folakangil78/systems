

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float mean(float arr[], int size) {
	float total_sum = 0.0;

	int index = 0;
	for (index = 0; index < size; index++) {
		total_sum += arr[index];
	}
	float avg = total_sum / size; // sums all elements in arr and divides by size (n) to find avg
	return avg;
} // iterates for number of times that is size and adds each element to sum, divides by size

float median(float arr[], int size) {
	if (size % 2 == 1) { // checks if arr is odd num of elements and takes element at /2
		float median = arr[size / 2];
		return median;
	} else {
		float two_middle_avg = (arr[size / 2] + arr[(size/2) - 1]); // takes avg of two middle if even size; 0-based = element at /2 and element one before it
		return two_middle_avg;
	}
} // returns element at index half of size if odd size, otherwise takes avg of two middle elements

float mode(float arr[], int size) {
	int i  = 0;
	int j = 0;
	float count = 0;
	int index_of_mode = 0;
	float ultimate_mode_count = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) { // nested for loop to iterate thru array counting how many times ith element appears
			if (arr[i] == arr[j]) {
				count++; // increments count for that specific element appearing
			}
		}
		if (count >= ultimate_mode_count) { // compares to either tally of prev element's appearance or highest tally so far
			ultimate_mode_count = count;
			index_of_mode = i; // caches index of element if appearing most so far
		}
		count = 0;
	}
	if (ultimate_mode_count != 1){
		printf("Mode of array: %.3f\n", arr[index_of_mode]); /* printing out value that appears most with fractional precision, 
		need to print b/c also want to return how many times that element appeared (could have done other way around as well */
		return ultimate_mode_count;
	} else {
		return -1; // returning -1 if no observable mode
	}
}

float std_dev(float arr[], int size) {
	float avg = 0;
	int index = 0;
	float sum = 0;
	for (index = 0; index < size; index++) {
		sum += arr[index];
	}
	avg = sum / size; // wasn't fully sure how to do function calls outside of main, otherwise would have just used mean()

	int denom = size - 1;
	float std_sum = 0;
	for (index = 0; index < size; index++) {
		std_sum = std_sum + (((arr[index] - avg) * (arr[index] - avg)) / denom);
	}
	return (float)sqrt(std_sum); // leverages math lib sqrt function and casts to float (sqrt fnc only returns doubles)
}

int * rounded_vals(float arr[], int size){
	int *rounded_arr = (int *)malloc(size * sizeof(int)); // TutorialsPoint "C library - malloc() function"
    	for (int index = 0; index < size; index++) { // creates dynamically sized array with malloc and inserts rounded values
        	rounded_arr[index] = round(arr[index]);
	}
	return rounded_arr; // applies printing of pointer address in main()
}

char * ascii(float arr[], int size) {
	int *rounded_arr = (int *)malloc(size * sizeof(int)); // TutorialsPoint "C library - malloc() function"
	int index = 0;
        for (index = 0; index < size; index++) {
                rounded_arr[index] = round(arr[index]);
        } // conducts same rounding algorithm from above to translate into ascii - figure out function calling outside of main() for future reference

        // ascii values don't correspond to #s > 127 ~ DigitalCoach "Non ASCII Characters: find out what they are and how to remove them"
	char *asci_array = (char *)malloc(size * sizeof(char)); // malloc() TutorialsPoint, creates array with char pointer

    	for (index = 0; index < size; index++) {
        	if (rounded_arr[index] >= 0 && rounded_arr[index] <= 127) {
            		asci_array[index] = (char)rounded_arr[index];  // get ascii by casting to char and setting to current index in ascii array
		} else {
			asci_array[index] = '*';  // * char for elements that don't fulfill condition < 127
		}
	}
	return asci_array;
} 

int main(int argc, char * argv[]) { // argc counting the number of args being passed in, argv setting each indiv. arg as a string
	int size = atoi(argv[1]); // convert second arg given in script-call at index 1 to integer - interpreted as size of array
	
	float arr[size]; // create float array based on size arg given

	if (argc != size + 2) {
		printf("Size doesn't match number of values given.\n");
		return 0;
	} // check to make sure that #oftotal_args is equal to size + 2 b/c number of values + name of file + size value itself

	if (argc < 3) {
        	printf("Too few args provided");
        	return 0;
    	} // condition to make sure at least 3 args given - name of file, size, value (bare min)

    	int index = 0;
	for (index = 0; index < size; index++) {
        	arr[index] = atof(argv[index + 2]);
    	} // converting values starting at index 2 from str to float (atof) and appending to arr

	float avg = mean(arr, size); // mean function call
	printf("Mean of values: %.3f\n", avg); // 3 decimal precision syntax ~ geeksforgeeks

	float median_val = median(arr, size); // median function call
	printf("Median of values: %.3f\n", median_val);

	float mode_val = mode(arr, size); // mode function call
	printf("The mode of the array shows up %.1f times in the array!\n", mode_val);
	
	float std_val = std_dev(arr, size); // std function call
	printf("The standard deviation of the array values is %.3f.\n", std_val);

	int * rounded_values = rounded_vals(arr, size); // ptr address of rounded values array
	printf("Pointer value to rounded integer values of float array input: %p\n", (void*)rounded_values); // stackOverflow "C++ how to get the address stored in a void pointer?"
	// applying (void*) to integer array with pointer to access address 	

	char * asci_values = ascii(arr, size); // creates asci values array with char pointer to be returned from ascii()
	printf("ASCII values corresponding to rounded inputs:\n");
	for (int i = 0; i < size; i++) {
		printf("Value at index %d: '%c'\n", i, asci_values[i]); // uses format specifiers to tell printf what type of quantity to look for, first a decimal value for i, then char value for element in ascii array
	}

	return 0;
}
