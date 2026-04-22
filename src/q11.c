// Write a C program to create a file and write a user-entered string into it. Then display a 
// message confirming that the file has been written successfully.


#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILENAME   "output.txt"
#define BUFFER_LEN 1024


void stripNewline(char *str) {
    while (*str != '\n' && *str != '\0') str++;
    if (*str == '\n') *str = '\0';
}

void printDivider(char ch, int width) {
    for (int i = 0; i < width; i++) putchar(ch);
    putchar('\n');
}

void currentTimestamp(char *buffer, int size) {
    time_t now     = time(NULL);
    struct tm *t   = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}


int writeToFile(const char *filename, const char *content, const char *timestamp) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return 0;

    fprintf(fp, "Timestamp : %s\n", timestamp);
    fprintf(fp, "Content   : %s\n", content);
    fprintf(fp, "Length    : %zu character(s)\n", strlen(content));

    fclose(fp);
    return 1;
}

void previewFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("  Could not open file for preview.\n");
        return;
    }

    printf("\n  FILE CONTENTS:\n  ");
    printDivider('-', 44);

    char line[BUFFER_LEN];
    while (fgets(line, sizeof(line), fp) != NULL)
        printf("  %s", line);

    printf("  ");
    printDivider('-', 44);
    fclose(fp);
}


int main() {
    char input[BUFFER_LEN];
    char timestamp[32];

    printf("╔══════════════════════════════════════════════╗\n");
    printf("║           FILE WRITE PROGRAM                 ║\n");
    printf("╚══════════════════════════════════════════════╝\n");

    printf("\n  Enter a string to write to \"%s\":\n  > ", FILENAME);
    fgets(input, BUFFER_LEN, stdin);
    stripNewline(input);

    if (strlen(input) == 0) {
        printf("\n  Error: Nothing to write — input was empty.\n");
        return 1;
    }

    currentTimestamp(timestamp, sizeof(timestamp));

    printf("\n  Writing to file...\n");

    if (!writeToFile(FILENAME, input, timestamp)) {
        printf("\n  ✗ Error: Could not open \"%s\" for writing.\n", FILENAME);
        printf("    Check directory permissions and try again.\n");
        return 1;
    }

    printf("\n  ┌────────────────────────────────────────────┐\n");
    printf(  "  │           FILE WRITE SUCCESSFUL            │\n");
    printf(  "  ├────────────────────────────────────────────┤\n");
    printf(  "  │  File      : %-29s  │\n", FILENAME);
    printf(  "  │  Timestamp : %-29s  │\n", timestamp);
    printf(  "  │  Length    : %-3zu character(s)               │\n", strlen(input));
    printf(  "  └────────────────────────────────────────────┘\n");

    previewFile(FILENAME);

    return 0;
}