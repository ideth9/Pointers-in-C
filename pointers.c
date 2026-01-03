#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Resources used for fgets(), strtol(), and selection sort:
// geeksforgeeks.org/c-program-for-selection-sort/
// geeksforgeeks.org/fgets-function-in-c/
// tutorialspoint.com/c_standard_library/c_function_strtol.htm

//We first must define the ineteger array structure we will be working with. 
struct IntArray{
	int length;
	int* dataPtr;
};

/* Function to allocate memory, and initialize an array, and returns a pointer
to the array. */
struct IntArray* mallocIntArray(int length){
	// To create an array we must allocate memory using malloc. 
	struct IntArray *intarray = malloc(sizeof(struct IntArray));

	/* If our memory allocation for our array failed, we display a warning
	and exit the function. We will do something similar if the allocation 
	for our pointer fails. */
	if (intarray == NULL){
		fprintf(stderr, "Error allocating memory for array.\n");
                exit(EXIT_FAILURE);
	}

	// Initializes the length for our array. 
	intarray->length = length;

	/* We must also allocate memory for our data pointer in order 
	to locate the array we created. */
	intarray->dataPtr = malloc(length * sizeof(int));
	if (intarray->dataPtr == NULL){
		free(intarray);
		exit(EXIT_FAILURE);
	}

	return intarray;
}

void freeIntArray(struct IntArray* arrayPtr){
	/* We can free our array, if it has valid memory stored inside. We must check
	that the array is not empty using the NULL C pointer. */
	if (arrayPtr != NULL){
		free(arrayPtr->dataPtr);
		free(arrayPtr);
	}
}

void readIntArray(struct IntArray* array){
	/* fgets() requires a pointer to the string buffer where the input
	will be stored. We create this by initializing an empty array.  */
	char buffer[100];
	char* endptr;

	// We must prompt the user according to the length.
	for (int i = 0; i< array->length; i++){
		while (1){
			printf("Enter int: ");
	
			/* If the user does not input a valid integer, this will continuously
			prompt the user for valid input. */	
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                       		fprintf(stderr, "Invalid input\n");
 		                continue;
               		}
	
			// We must remove the newline chracter which fgets() includes.	
			buffer[strcspn(buffer, "\n")] = '\0';

			/* Using the strtol() function we convert the string the user input
			into a long integer. */
			long num = strtol(buffer, &endptr, 10);

			/* If the call to strtol() failed, that means an invalid input was
			given, and we must prompt the user for valid input. */
			if (endptr == buffer){
				printf("Invalid input\n");
				continue;
			}

			while (*endptr == ' ' || *endptr == '\t')
				endptr++;
		
			if (*endptr != '\0'){
				printf("Invalid input\n");
				continue;
			}

			// A final check to make sure the valid user input is positive.
			if (num <= 0){
				printf("Invalid input\n");
				continue;
			}
		
			// We then insert the input, into our array.
			array->dataPtr[i] = (int)num;
			break;
		}
	}
}

void swap(int* xp, int* yp){
     	/* In order to swap the value of our variables, we create temporary 
	variables to hold them. */ 
	int old_xp = *xp;
        int old_yp = *yp;
     
	// We swap the values by assigning them to our initial variables.  
	*xp = old_yp;
        *yp = old_xp;

}

void sortIntArray(struct IntArray* array){
	// To sort the entire list, we must traverse the list by its length. 
	for (int i = 0; i < array->length -1; i++){
		// We set our minimum value to be the first element of the array.	
		int min_idx = i;

		// We look to the next element in the array.
		for (int j = i + 1; j < array->length; j++){
			/* If the next element is less than the one prior it is set to be
			the minimum index. */
			if (array->dataPtr[j] < array->dataPtr[min_idx]){
				swap(&array->dataPtr[j], &array->dataPtr[min_idx]);	
			}
		}
	
		/* If our minimum index is not the first element of the array,
		we swap them. */ 	
		if (min_idx != i){
			swap(&array->dataPtr[i], &array->dataPtr[min_idx]);
		}
	}
} 

void printIntArray(struct IntArray* array){
	printf("[ ");
	
	/* Iterate through the entire list and print each individual
	element of the array. */
	for (int i = 0; i < array->length; i++){
		printf("%d", array->dataPtr[i]);
		if (i < array->length - 1){
			printf(", ");
		}
	}
	printf(" ]\n");
}

int main(){
	/* We follow a similar process as done in the readIntArray function to prompt
	the user for a valid length. */
	char buffer[100];
	char* endptr;
	int length;

	while (1){
		printf("Enter length: ");
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			fprintf(stderr, "Invalid input\n"); 
			continue;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] == '\0'){
                        printf("Exiting program.\n");
                        exit(0);
                }

		long num = strtol(buffer, &endptr, 10);

		if (endptr == buffer){
			printf("Invalid input\n");
			continue;
		}

		while (*endptr == ' ' || *endptr == '\t'){
			endptr++;
		}
		
		if (*endptr != '\0'){
			printf("Invalid input.\n");	
			continue;
		}

		if (num <= 0){
			printf("Invalid input.\n");
			continue;
		}

		length = (int)num;
		break;
	}

	/* Our call to the functions created earlier, in order to create and initialize
	an array, read the array, sort the array, print, and free the array. */

	struct IntArray* intarray = mallocIntArray(length);

	readIntArray(intarray);

	sortIntArray(intarray);
	
	printIntArray(intarray);

	freeIntArray(intarray);

	return 0;

}


