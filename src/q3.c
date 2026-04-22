// Write a C program that checks if a given string is a palindrome using pointers.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(const char *str) {
    const char *left  = str;
    const char *right = str + strlen(str) - 1;

    while (left < right) {
        if (tolower(*left) != tolower(*right))
            return 0;

        left++;
        right--;
    }
    return 1;
}

int main() {
    const char *words[] = {"racecar", "hello", "Madam", "level", "world", "Noon"};
    int count = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < count; i++) {
        printf("%-10s -> %s\n", words[i], isPalindrome(words[i]) ? "Palindrome" : "Not a Palindrome");
    }

    return 0;
}