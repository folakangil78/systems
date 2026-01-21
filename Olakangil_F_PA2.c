/* I Francis Olakangil certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double * linear_func(int a, int b, const double * values, int size) {
	double * output_array = (double *)malloc(size * sizeof(double)); // function output array dynamic allocated
	
	for (int index = 0; index < size; index++) {
		output_array[index] = (a * values[index]) + b; 
	} // applies linear function formula to each value and appends to output
	
	return output_array;
}

double * quadratic_func(int a, int b, const double * values, int size) {
	double * output_array = (double *)malloc(size * sizeof(double)); // uses size param to multiply byte-size of indiv double for num of doubles needed in array (size)

	for (int index = 0; index < size; index++) {
		output_array[index] = (values[index] * values[index]) + (a * values[index]) + b;
	} // same as linear, applies formula of squaring input and adding to a param multiplied by and added to b param

	return output_array;
}

double * exp_func(int a, int b, const double * values, int size) {
	double * output_array = (double *)malloc(size * sizeof(double));
	
	for (int index = 0; index < size; index++) {
		output_array[index] = exp(a * values[index]); // exp fxn in math lib acts as applying e (euler's number) as base of exponent - quantity in () 
	}

	return output_array;
}

double * sin_func(int a, int b, const double * values, int size) {
	double * output_array = (double *)malloc(size * sizeof(double)); // same form of allocation for all because size of array remaining unchanged after operation

	for (int index = 0; index < size; index++) {
		output_array[index] = a * sin(b * values[index]); // math lib has sin func itself accepting args in terms of radians
	}

	return output_array;
}

int compareStrings(const char *string_var1, const char *string_var2) { // supplementary method to modularize string comparison for which function to calculate deriv of
	for (int index = 0; ; index++) {
		if (string_var1[index] != string_var2[index]) { 
			return -1; // this basically implies that any specific character of the function given does not match and it'll break the switch cases in deriv()
		}
		if (string_var1[index] == '\0') {
			return 0; // strings are all ended with a null terminator, that being 0, if the index matches this value, that means the string has reached the end without issue
		}
	} /* unsigned char logic citation: StackOverflow: "How do I properly compare strings in C?"
	and GeeksforGeeks "C program to Compare Two Strings without using strcmp() function" */
} //  impt note to use const char to represent the null-terminated arrays of characters that strings are, const *string wouldn't be valid although intuitive

double * func_derivative(const char * func, double * val_plus, double * val, double * val_minus, int a, int b, int order, double h, int size) {
	switch(order) {
		case 0:
			if (compareStrings(func, "sin") == 0) {
				double *(* sin_fptr)(int, int, const double *, int); // creates fxn ptr with assoc. parameters for given sin fxn
				sin_fptr = &sin_func;
				return sin_fptr(a, b, val, size); // applies given params to fxn ptr
			}
			if (compareStrings(func, "lin") == 0) {
                                double *(* lin_fptr)(int, int, const double *, int);
                                lin_fptr = &linear_func;
                                return lin_fptr(a, b, val, size);
                        }
			if (compareStrings(func, "exp") == 0) {
                                double *(* exp_fptr)(int, int, const double *, int);
                                exp_fptr = &exp_func;
                                return exp_fptr(a, b, val, size); // all same convention as sin function but with separate pointers to specific function needed
                        }
			if (compareStrings(func, "quad") == 0) {
                                double *(* quad_fptr)(int, int, const double *, int);
                                quad_fptr = &quadratic_func;
                                return quad_fptr(a, b, val, size);
                        }
		case 1:
			if (compareStrings(func, "sin") == 0) {
                                double *(* sin_fptr)(int, int, const double *, int);
                                sin_fptr = &sin_func;
                               	double *normal_values = sin_fptr(a, b, val, size);
				double *plus_values = sin_fptr(a, b, val_plus, size);
				
				double *result = (double *)malloc(size * sizeof(double)); // cannot just apply operations to ptrs themselves as they only point to first value of array
				for (int i = 0; i < size; i++) { // need to iterate through arrays that the pointers are pointing to and apply op to each indiv element and re-append upon each iteration
        				result[i] = (plus_values[i] - normal_values[i]) / h;
    				}

    				return result;
                        }
			if (compareStrings(func, "lin") == 0) {
                                double *(* lin_fptr)(int, int, const double *, int);
                                lin_fptr = &linear_func;
                                double *normal_values_lin = lin_fptr(a, b, val, size);
				double *plus_values_lin = lin_fptr(a, b, val_plus, size);

				double *result = (double *)malloc(size * sizeof(double)); // creates new dynamically allocated array for resulting array after applying deriv op to each element
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_lin[i] - normal_values_lin[i]) / h;
                                }
                                
                                return result;
                        }
			if (compareStrings(func, "exp") == 0) {
                                double *(* exp_fptr)(int, int, const double *, int);
                                exp_fptr = &exp_func;
                                double *normal_values_exp = exp_fptr(a, b, val, size);
				double *plus_values_exp = exp_fptr(a, b, val_plus, size);

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_exp[i] - normal_values_exp[i]) / h; // makes sure to create separate pointers based on adding or subtracting values (taken as fxn params in signature)
                                }
                                
                                return result;
                        }
			if (compareStrings(func, "quad") == 0) {
                                double *(* quad_fptr)(int, int, const double *, int);
                                quad_fptr = &quadratic_func;
                                double *normal_values_quad = quad_fptr(a, b, val, size);
				double *plus_values_quad = quad_fptr(a, b, val_plus, size);

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_quad[i] - normal_values_quad[i]) / h;
                                }
                                
                                return result;
                        }
		case 2:
			if (compareStrings(func, "sin") == 0) {
                                double *(* sin_fptr)(int, int, const double *, int);
                                sin_fptr = &sin_func;
                                double *normal_values_sin = sin_fptr(a, b, val, size);   
                                double *plus_values_sin = sin_fptr(a, b, val_plus, size);
				double *minus_values_sin = sin_fptr(a, b, val_minus, size); // third pointer here for accessing minus values from h (all actually created in main and passed into param of fxn)

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_sin[i] - (2 * normal_values_sin[i]) + minus_values_sin[i]) / (h * h); // makes sure to apply second order deriv ops to each element and re-append
                                }
                                
                                return result;
                        }
			if (compareStrings(func, "lin") == 0) {
                                double *(* lin_fptr)(int, int, const double *, int);
                                lin_fptr = &linear_func;
                                double *normal_values_lin = lin_fptr(a, b, val, size);
                                double *plus_values_lin = lin_fptr(a, b, val_plus, size);
                                double *minus_values_lin = lin_fptr(a, b, val_minus, size);

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_lin[i] - (2 * normal_values_lin[i]) + minus_values_lin[i]) / (h * h);
                                }
                         
                                return result;
                        }
			if (compareStrings(func, "exp") == 0) {
                                double *(* exp_fptr)(int, int, const double *, int);
                                exp_fptr = &exp_func;
                                double *normal_values_exp = exp_fptr(a, b, val, size);
                                double *plus_values_exp = exp_fptr(a, b, val_plus, size);
                                double *minus_values_exp = exp_fptr(a, b, val_minus, size);

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_exp[i] - (2 * normal_values_exp[i]) + minus_values_exp[i]) / (h * h);
                                }
                         
                                return result;
                        }
			if (compareStrings(func, "quad") == 0) {
                                double *(* quad_fptr)(int, int, const double *, int);
                                quad_fptr = &quadratic_func;
                                double *normal_values_quad = quad_fptr(a, b, val, size);
                                double *plus_values_quad = quad_fptr(a, b, val_plus, size);
                                double *minus_values_quad = quad_fptr(a, b, val_minus, size); // repetitive structure for all different graphical function cases for the three orders - could have optimized better

				double *result = (double *)malloc(size * sizeof(double));
                                for (int i = 0; i < size; i++) {
                                        result[i] = (plus_values_quad[i] - (2 * normal_values_quad[i]) + minus_values_quad[i]) / (h * h);
                                }
                         
                                return result;
                        }
		default: {
			double *result;
			result = (double *)malloc(sizeof(double));
			 /* impt to use brackets here to denote local scope declaration of result pointer, specific syntax for switch blocks - ArduinoForum "defining a variable inside a switch() 
			statement produces 'strange' behaviour" */
			*result = 3.14159; // function still needs double ptr return type, can't simply return 3.14159 as a plain float value
			return result;
		}
	}

}

int main(int argc, char * argv[]) {
	int size = argc - 2; // b/c we are subtracting the file name (arg1) and the h-value from total argument count
	
	if (argc < 3) { // check to make sure at bare minimum one element and h-value is provided
		printf("Too few arguments provided!");
		return 0;
	}

	if (argc != size + 2) { // check to match number of args = size + filename + h-value
		printf("The number of arguments you have given don't match the number expected!");
		return 0;
	}
	
	double * input_values = (double *)malloc(size * sizeof(double));

	for (int index = 0; index < size; index++) {
		input_values[index] = atof(argv[index+1]); // initializes values of input_array with index+1 because 0th element acts as filename of executable
	} // loop condition of < size should work because iteration will stop as soon as array is fully populated with correct size, don't have to worry about processing incorrect/unneeded elements of argv
	
	double h = atof(argv[argc-1]); // uses logic of argc representing argv length to access last element in argv array (h) // need to cast to double because elements in argv intrinsically char

	double * val_plus = (double *)malloc(size * sizeof(double));

	for (int index = 0; index < size; index++) {
		val_plus[index] = input_values[index] + h;
	}

	double * val_minus = (double *)malloc(size * sizeof(double));

	for (int index = 0; index < size; index++) {
		val_minus[index] = input_values[index] - h;
	} // loop structures above populate +h and -h arrays for each element, accessing h value from last element of argv

	// test code here...
	


	free(input_values);
	free(val_plus);
	free(val_minus); // frees memory behind all dynamically allocated memory arrays in main including input values, +h values, and -h values

	return 0;
}





