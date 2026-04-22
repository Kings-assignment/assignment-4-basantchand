// Write a C program that reverses an array of characters using pointers.

#include <stdio.h>
#include <string.h>

void reverseArray(char *arr, int size) {
    char *left  = arr;
    char *right = arr + size - 1;

    while (left < right) {
        char temp = *left;
        *left     = *right;
        *right    = temp;

        left++;
        right--;
    }
}

int main() {
    char arr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
    int size   = sizeof(arr) / sizeof(arr[0]);

    printf("Before reverse: ");
    for (int i = 0; i < size; i++) printf("%c", arr[i]);

    reverseArray(arr, size);

    printf("\nAfter reverse:  ");
    for (int i = 0; i < size; i++) printf("%c", arr[i]);
    printf("\n");

    return 0;
}