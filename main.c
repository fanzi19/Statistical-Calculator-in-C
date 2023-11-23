#include <stdio.h>
#include <stdlib.h>
#include "sourcefile.h"

/*
 * The main function of the program reads numerical data from a file specified as a command-line argument.
 * It then calculates various statistical measures such as mean, mode, geometric mean, harmonic mean, median,
 * and standard deviation using the provided functions. The results are printed to the console, including the
 * number of values, mean, mode (if it exists), geometric mean, harmonic mean, median, standard deviation,
 * and the unused capacity of the data array. The program ensures proper memory allocation and frees memory
 * before exiting.
 * 
 * Usage: ./basicstats <filename>
 *   - <filename>: Name of the file containing numerical data.
 */

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int size;
	int capacity;
	int resultSize;

	float *dataArray = ReadDataFile(argv[1], &size, &capacity);

	float mean = calMean(dataArray, size);
	float* mode = calMode(dataArray, size, &resultSize);
	float geometricMean = calGeometricMean(dataArray, size);
	float harmonicMean = calHarmonicMean(dataArray, size);
	float median = calMedian(dataArray, size);
	float standardDeviation = calStandardDeviation(dataArray, size, mean);

	printf("Results:\n");
	printf("---------\n");
	printf("   Num Values: %d\n", size);
	printf("         Mean: %f\n", mean);
	printf("         Mode:");
	if (mode == NULL) {
		printf(" NOT EXISTS");
	} else {
		for (int i = 0; i < resultSize; i++) {
			printf(" %f ", mode[i]);
		}
	}
    printf("\n");
	printf("GeometricMean: %f\n", geometricMean);
	printf(" HarmonicMean: %f\n", harmonicMean);
	printf("       Median: %f\n", median);
	printf("StandardDeviation: %f\n", standardDeviation);
	printf("Unused Array Capacity: %d\n", capacity - size);

	free(mode);
	free(dataArray);

	return EXIT_SUCCESS;

}
