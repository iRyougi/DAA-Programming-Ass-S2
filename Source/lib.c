#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

int* readNumbersFromFile(const char *filePath, int *size) {
    FILE *file;
    int *numbers;
    int num, count = 0;
    int capacity = 10; // Initial array capacity

    // Initialize size
    *size = 0;

    // Open file
    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", filePath);
        return NULL;
    }

    // Allocate memory
    numbers = (int *)malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;  //数组动态分配
            int *temp = (int *)realloc(numbers, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Memory reallocation failed\n");
                free(numbers);
                fclose(file);
                return NULL;
            }
            numbers = temp;
        }
        numbers[count++] = num;
    }

    fclose(file);

    *size = count;

    return numbers;
}

SubArrayResult maxSubArray(int num[], int length) {
    SubArrayResult result;
    result.maxSum = num[0];
    result.start = 0;
    result.end = 0;

    int* dp = (int*)malloc(length * sizeof(int));   // Allocate memory

    if (dp == NULL) {
        printf("Memory allocation failed\n");
        result.maxSum = -1;
        return result;
    }

    dp[0] = num[0];
    int max = dp[0];
    int temp = 0;

    for (int i = 1; i < length; i++) {
        if (dp[i - 1] <= 0) {
            dp[i] = num[i];
            temp = i; // Record start position
        } else {
            dp[i] = num[i] + dp[i - 1];  // Sum subsequent values
        }
           
        if (dp[i] > max) {
            max = dp[i];
            result.start = temp;
            result.end = i;
        }
    }

    result.maxSum = max;
    free(dp);
    return result;
}

void writeResultsToFile(const char *inputFileName, SubArrayResult result) {
    // Create output file name
    char outputFileName[256];
    snprintf(outputFileName, sizeof(outputFileName), "%s_out", inputFileName);

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Cannot open output file: %s\n", outputFileName);
        return;
    }

    fprintf(outputFile, "%d\n", result.maxSum);
    fprintf(outputFile, "%d %d\n", result.start, result.end);

    fclose(outputFile);
}