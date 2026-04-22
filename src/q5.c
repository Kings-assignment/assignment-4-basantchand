// Write a C program that dynamically allocates memory for a string entered by the user and finds its length using pointers.

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

int stringLength(const char *str) {
    const char *ptr = str;
    while (*ptr != '\0')
        ptr++;
    return ptr - str;
}

int main() {
    char buffer[MAX_BUFFER];

    printf("Enter a string: ");
    fgets(buffer, MAX_BUFFER, stdin);

    char *newline = buffer;
    while (*newline != '\n' && *newline != '\0')
        newline++;
    if (*newline == '\n')
        *newline = '\0';

    int len = stringLength(buffer);

    char *str = (char *)malloc((len + 1) * sizeof(char));

    if (str == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    char *src  = buffer;
    char *dest = str;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';

    printf("\nCharacter breakdown:\n");
    for (char *ptr = str; *ptr != '\0'; ptr++) {
        printf("  [%ld]  Address: %p  ->  Char: '%c'  (ASCII: %d)\n",
               ptr - str, (void *)ptr, *ptr, *ptr);
    }

    printf("\nDynamically allocated string : \"%s\"\n", str);
    printf("Length (excluding '\\0')      : %d\n", len);
    printf("Memory allocated             : %d byte(s)\n", len + 1);

    free(str);
    str = NULL;

    return 0;
}