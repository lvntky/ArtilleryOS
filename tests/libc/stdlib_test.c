/**
 * @file stdlib_test.c
 * @brief standard library testing
 *
 *
 * @date April 4th, 2024
 * @copyright 2023, Lukas R. Jackson
 *
 * @author Lukas R. Jackson (LukasJacksonEG@gmail.com)
 *
 * @license MIT License
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */

#include "../../kernel/libc/include/stdlib.h"
#include <stdio.h>

char memory[MEMORY_SIZE];
Node *head = NULL;

int main()
{
    // MALLOC USAGE
	int *array;
	char string[] = "Hello, world!\0";
	int string_length = sizeof(string) / sizeof(char);
	int i;

	// Example usage
	array = (int *)malloc(string_length * sizeof(int));
	if (array == NULL) {
		printf("Memory allocation failed!\n");
		return 1; // Exit the program with an error code
	}
	for (i = 0; i < string_length; i++) {
		array[i] = string[i];
	}
	// Print the string stored in the array
	printf("The string stored in the array is: ");
	for (i = 0; i < string_length; i++) {
		printf("%c", (char)array[i]);
	}
	printf("\n");
    // CALLOC USAGE 
    int* arr = (int*)calloc(5, sizeof(int));
    if (arr != NULL) {
        // Use the allocated memory
        for (int i = 0; i < 5; ++i) {
            printf("%d", arr[i]); // All elements should be 0
        }
        printf("\n");
        free(arr);
    }
    // REALLOC USAGE
    int* arr2 = (int*)malloc(5 * sizeof(int));
    if (arr2 != NULL) {
        // Use the allocated memory
        for (int i = 0; i < 5; ++i) {
            arr2[i] = i;
            printf("%d ", arr2[i]); // Prints 0 1 2 3 4
        }

        // Reallocate memory
        arr2 = (int*)realloc(arr2, 10 * sizeof(int));
        if (arr2 != NULL) {
            // Use the reallocated memory
            for (int i = 0; i < 10; ++i) {
                printf("%d %s", arr2[i], "\n"); // All elements should be 0 (since realloc does not initialize the new memory)
            }
        }

        // Free memory
        free(arr2);
    }

	free(array);
	return 0;
}