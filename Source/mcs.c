#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    int *numbers;
    int size;

    numbers = readNumbersFromFile(argv[1], &size);

    if (numbers == NULL) {
        return 1; // readNumbersFromFile already prints an error message
    }

    SubArrayResult result = maxSubArray(numbers, size);
    
    printf("Max subarray sum is: %d\n", result.maxSum);
    printf("Start index: %d\n", result.start);
    printf("End index: %d\n", result.end);

    writeResultsToFile(argv[1], result);

    free(numbers);
    return 0;
}