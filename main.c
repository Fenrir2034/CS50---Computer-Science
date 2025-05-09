// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.c" // Include the Huffman coding implementation

// Function to run tests
void runTests()
{
    // Test case 1: Add your test cases here
    // Example: Test Huffman coding for a different set of data and frequencies
    char testData[] = {'a', 'b', 'c', 'd'};
    int testFreq[] = {10, 20, 30, 40};
    int testSize = sizeof(testData) / sizeof(testData[0]);

    printf("Running Test Case 1:\n");
    HuffmanCodes(testData, testFreq, testSize);

    // Add more test cases as needed
}

int test()
{
    // Original example
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);

    printf("Original Example:\n");
    HuffmanCodes(data, freq, size);

    // Run additional scenarios or test cases
    runTests();

    return 0;
}
