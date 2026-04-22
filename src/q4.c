// Write a C program that dynamically allocates memory for an integer array of size n, where n is entered by the user. Prompt the user to enter n elements and display them using pointers.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: Size must be a positive integer.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int *ptr = arr; ptr < arr + n; ptr++) {
        printf("  Element %ld: ", ptr - arr + 1);
        scanf("%d", ptr);
    }

    printf("\nArray elements:\n");
    for (int *ptr = arr; ptr < arr + n; ptr++) {
        printf("  [%ld] Address: %p  ->  Value: %d\n", ptr - arr, (void *)ptr, *ptr);
    }

    free(arr);
    arr = NULL;

    return 0;
}