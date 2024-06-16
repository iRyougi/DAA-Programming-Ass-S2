# On the Solution of the Dynamic Programming Algorithm for the Maximum Contiguous Subarray Problem
### Documentation
Design by Taian Yu, 2230026198\
I will use markdown documentation to explain the algorithms I designed and the functions I implemented.\
In my project, I use dynamic memory allocation, which can cope with arrays of variable size

***

## The Formal Definition of the Problem
### Input
Read a file's name, file contains an array
### Output
Output a file named 'in_out'\
Outputs the sum of the largest contiguous subarrays, One Optimal Solution
### Solution <For example, -3 2 1 -4 5 2 -1 3 -1>
1. Compare the second value, 2, with the initial values, -3 and 2
It is found that 2 is relatively large\
Update the start of the largest subarray 2\
Update current Max sum to 2 (initial value -3)

2. Compare the sum of the third value with the starting points 2 and 1 of the largest subarray\
It is found that the sum of 2 and 1 is relatively large\
Compare the current maximum sum with the sum of 2 and 1\
Update the current maximum sum of 2 and 1 and 3

3. And So on

### High-Level Presentation
Start at the left edge of the array and work from left to right, keeping track of the largest subarray that has been processed so far. Given A maximal subarray of A[1..j], the solution is extended to A maximal subarray of A[1...j+1] based on the following property: The maximal subarray of A[1...j+1] is either the maximal subarray of A[1...j] or some subarray A[i...j+1] (1<=i<=j+1). Given the largest subarray of A[1...j], we can find the largest subarray of the shape A[i...j+1] in linear time

## The Recurrence Relation
$$dp[i]=max(num[i],dp[i−1]+num[i])$$
- The initialization condition is:
$$ dp[0]=num[0]$$

## Definitions of the Notations in Recurrence Relation
- dp[i]：The sum of the largest subarrays ending with num[i]
- num[i]：The ith element of the array
- dp[i-1]：The largest sum of subarrays ending with num[i-1]
- max：Maximum sum of subarrays in the whole array, final result

## Pseudocode 
``` pseudocode 
Input: An Array num[], The length of num[]
OutPut: The Sum; One Optimal Solution(start, end)

Begin
    Initialize result as a SubArrayResult object
        Set result.maxSum to num[0]
        Set result.start to 0
        Set result.end to 0

        Allocate memory for an array dp of size length

        Set dp[0] to num[0]
        Set max to dp[0]
        Set temp to 0

        For i from 1 to length - 1 do
            If dp[i - 1] is less than or equal to 0 do
                Set dp[i] to num[i]
                Set temp to i
            Else do
                Set dp[i] to num[i] + dp[i - 1]

            If dp[i] is greater than max do
                Set max to dp[i]
                Set start to temp
                Set end to i

        Set result.maxSum to max
        Return maxSum, start, end
```

## Time Cost Analysis

### File Read, Memory Dynamic Allocation
1. File opening and closing operations
   ```c++
   fopen(filePath, "r")
   fclose(file)
   ```
   - These are constant time operations, denoted $O(1)$.

2. Memory allocation and reallocation
   ```c
   malloc(capacity * sizeof(int))
   ```
   - The initial allocation is a constant time operation, denoted $O(1)$.
   
   ```c
   while (fscanf(file, "%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
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
   ```
   - Do this every time when the array's capacity need to be increase
   - In the worst case, if the input contains n integers and the array needs to be expanded by double each time, the expansion operation will be performed $O(log n)$ times, with each expansion operation requiring the elements of the existing array to be copied into the newly allocated larger memory. The number of element copies per expansion ranges from $1$ to $n/2$, so the total reallocation time is $O(n)$.
  
3. Read the contents of the file into an array
   ```c
   fscanf(file, "%d", &num)
   ```
   - The function reads the integers one by one.Reading a total of n integers takes $O(n)$ time.
   - Storing the read integer into an array takes $O(n)$ time.

4. Comprehensive analysis
   $$ O(1)+O(n)+O(n)=O(n) $$

### Dynamic Programming Algorithm
1. Initialization and memory allocation
    ```c
    SubArrayResult
    malloc(length * sizeof(int))
    ```
    - Initializing the SubArrayResult object and the variables dp, max, and temp is a constant time operation, denoted as $O(1)$.
    - Allocation is a constant time operation, denoted $O(1)$.

2. Main loop
   ```c
   for (int i = 1; i < length; i++) {
        if (dp[i - 1] <= 0) {
            dp[i] = num[i];
            temp = i;
        } else {
            dp[i] = num[i] + dp[i - 1];
        }
        if (dp[i] > max) {
            max = dp[i];
            result.start = temp;
            result.end = i;
        }
    }
   ```
    - The main loop goes from $1$ to $length-1$, executing $length-1$ times, and each operation within the loop takes constant $O(1)$ time. Therefore, the time complexity of the loop is $O(length)$.

3. Memory deallocation
    ```c
    free(dp);
    result.maxSum = max;
    return result;
    ```
    - These operations are constant time operations with $O(1)$ time complexity.

4. Comprehensive analysis
    $$O(1)+O(length)+O(1)=O(length)$$

### File output and result printing
1. Create an output filename
    ```c
    char outputFileName[256];
    snprintf(outputFileName, sizeof(outputFileName), "%s_out", inputFileName);
    ```
   - This part of the code uses snprintf to create the output filename. snprintf is a string manipulation function whose time complexity is proportional to the length of the string, assuming that the input filename is of filnamelength, the time complexity is $O(filnamelength)$.
2. Open the file
    ```c
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
    printf("Cannot open output file: %s\n", outputFileName);
    return;
    }
    ```
    - Opening a file is a constant time operation, denoted $O(1)$.
3. Write the maximum subarray sum with the start and end positions
    ```c
    fprintf(outputFile, "%d\n", result.maxSum);
    fprintf(outputFile, "%d %d\n", result.start, result.end);
    ```
    - Writing three integers to a file is a constant time operation, denoted $O(1)$.
4. Close the file
    ```c++
    fclose(outputFile);
    ```
    - Closing a file is a constant time operation, denoted $O(1)$.
5. Comprehensive analysis
    $$O(filnamelength)+O(1)+O(1)+O(1)+O(1)=O(filnamelength)$$
