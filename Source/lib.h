#ifndef LIB_H
#define LIB_H

typedef struct {
    int maxSum;
    int start;
    int end;
} SubArrayResult;

int* readNumbersFromFile(const char *filePath, int *size);
SubArrayResult maxSubArray(int num[], int length);
void writeResultsToFile(const char *inputFileName, SubArrayResult result);

#endif