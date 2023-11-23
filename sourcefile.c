#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "sourcefile.h"

// Function to read data from a file and dynamically allocate memory for an array
float* ReadDataFile(const char* filename, int* size, int* capacity) {
	// Start out allocating an array of 20 float values
	*capacity = 20;
	*size = 0;

	float* dataArray = (float*)malloc(*capacity * sizeof(float));

	if (dataArray == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	// Open the File
	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		fprintf(stderr, "Error opening the file.\n");
		exit(EXIT_FAILURE);
	}

	// Read data
	float value;
	while (fscanf(file, "%f", &value) == 1) {
		// Check if the array is full or not
		if (*size == *capacity) {
			*capacity *= 2;
			float* newData = (float*)malloc(*capacity * sizeof(float));

			if (newData == NULL) {
				fprintf(stderr, "memory allocation failed.\n");
				free(dataArray);
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i< *size; i++) {
				newData[i] = dataArray[i];
			}

			free(dataArray);

			dataArray = newData;
		}

		dataArray[*size] = value;
		(*size)++;
	}

	return dataArray;
}

// Function to swap two elements
void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Quicksort algorithm for sorting an array of floats
void quicksort(const float *dataArray, int low, int high) {
	if (low < high) {
		int pivot_index = (low + high) / 2;
		float pivot = dataArray[pivot_index];
		int i = low;
		int j = high;

		while (i <= j) {
			while (dataArray[i] < pivot) {
				i++;
			}
			while (dataArray[j] > pivot) {
				j--;
			}
			if (i <= j) {
				swap(&dataArray[i], &dataArray[j]);
				i++;
				j--;
			}
		}
		if (low < j) {
			quicksort(dataArray, low, j);
		}
		if (i < high) {
			quicksort(dataArray, i, high);
		}
	}
}


// Function to calculate the mean of an array of floats
float calMean(const float *dataArray, int size){

	if (size == 0) {
		printf("Size is zero.\n");
		exit(EXIT_FAILURE);
	}

	float sum = 0.0;

	for (int i = 0; i < size; i++) {
		sum += dataArray[i];
	}

	return sum / size;
}

// Function to calculate the mode of an array of floats
float* calMode(const float *dataArray, int size, int *resultSize) {

	// Check for zero size
	if (size == 0) {
		printf("Size is zero.\n");
		exit(EXIT_FAILURE);
	}

	// Sort the array using quicksort
	quicksort(dataArray, 0, size-1);

	// Create countArray to record the quantity of each unique number in the array
	int* countArray = (int*)malloc(size * sizeof(int));
    if (countArray == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize countArray
    for (int i = 0; i < size; i++) {
        countArray[i] = 1;
    }

	int count = 1;
	int maxCount = 1;

	// Calculate countArray, and get the max quantity in the array
	for (int i = 0; i < size-1; i++) {
		if (dataArray[i] == dataArray[i+1]) {
			count ++;
		} else {
			if (count > maxCount) {
				maxCount = count;
			}
			countArray[i] = count;
			count = 1;
		}
	}

	// Create countOccurrences to record the occurences of max quantity in the array
	int* countOccurrences = (int*)malloc(size * sizeof(int));
    if (countOccurrences == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
    	countOccurrences[i] = 0;
    }

	// Count occurrences of the max count
    int occurrences = 0;
    for (int i = 0; i < size; i++) {
        if (countArray[i] == maxCount) {
            occurrences++;
        }
        countOccurrences[i] = occurrences;
        occurrences = 0;
    }

    occurrences = countOccurrences[0];
    for (int i = 0; i < size-1; i++) {
    	if (countOccurrences[i] < countOccurrences[i+1]) {
    		occurrences = countOccurrences[i+1];
    	}
    }

    // Check if all elements in the array have the same occurences
    // In the definition of mode, if all elements have the same occurrences, it means mode is not exists. 
    int checkMode = 0;
    for (int i = 1; i < size; i++) {
    	if (countOccurrences[i-1] == countOccurrences[i]) {
    		checkMode++;
    	}
    }

    free(countOccurrences);

    // Return NULL if all elements have the same occurrences
    if (checkMode == size-1) {
    	free(countArray);
    	return NULL;
    }

	// Allocate memory for the result array
    float* result = (float*)malloc(occurrences * sizeof(float));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Return the elements with the max quantity.
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (countArray[i] == maxCount) {
            result[j] = dataArray[i];
            j++;
        }
        *resultSize = j;
    }

    // Free temporary array
    free(countArray);

	return result; 
}

// Function to calculate the geometric mean of an array of floats
float calGeometricMean(const float *dataArray, int size) {

	// Check for zero size
	if (size == 0) {
		printf("Size is zero.\n");
		exit(EXIT_FAILURE);
	}

	double product = 1.0;

	for(int i = 0; i < size; i++) {
		product *= dataArray[i];
	}

	return pow(product, 1.0/size);
}

// Function to calculate the harmonic mean of an array of floats
float calHarmonicMean(const float *dataArray, int size) {

	// Check for zero size
	if (size == 0) {
		printf("Size is zero.\n");
		exit(EXIT_FAILURE);
	}

	float sum = 0.0;

	for(int i = 0; i < size; i++) {
		sum += 1.0 / dataArray[i];
	}

	return size / sum;
}

// Function to calculate the median of an array of floats
float calMedian(float *dataArray, int size) {
	
	// Sort the array using quicksort
	quicksort(dataArray, 0, size-1);

	if (size % 2 == 0) {

		return (dataArray[size / 2 - 1] + dataArray[size / 2]) / 2.0;

	} else {

		return dataArray[size / 2];
	}
}

// Function to calculate the standard deviation of an array of floats
float calStandardDeviation(const float *dataArray, int size, float mean) {

	// Check for zero size
	if (size == 0) {
		printf("Size is zero.\n");
		exit(EXIT_FAILURE);
	}

	float sumSquaredDiff = 0.0;

	for (int i = 0; i < size; i++) {
		float diff = dataArray[i] - mean;
		sumSquaredDiff += diff * diff;
	}

	return sqrt(sumSquaredDiff / size);
}



