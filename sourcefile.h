#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>

/*
 * Function declarations for reading numerical data from a file, calculating various statistical measures,
 * and managing dynamic memory allocation.
 */

float* ReadDataFile(const char* filename, int* size, int* capacity);
float calMean(const float *dataArray, int size);
float* calMode(const float *dataArray, int size, int *resultSize);
float calGeometricMean(const float *dataArray, int size);
float calHarmonicMean(const float *dataArray, int size);
float calMedian(float *dataArray, int size);
float calStandardDeviation(const float *dataArray, int size, float mean);

#endif