// Write a C program to read the contents of a text file and display them on the screen.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME   "sample.txt"
#define LINE_LEN   256


void printBanner(const char *title) {
    int len = strlen(title) + 4;
    printf("\n  ╔");
    for (int i = 0; i < len; i++) printf("═");
    printf("╗\n  ║  %s  ║\n  ╚", title);
    for (int i = 0; i < len; i++) printf("═");
    printf("╝\n");
}

void printDivider(char ch, int width) {
    printf("  ");
    for (int i = 0; i < width; i++) putchar(ch);
    putchar('\n');
}


typedef struct {
    int lines;
    int words;
    int chars;
    int blank;
} FileStats;

FileStats analyzeFile(const char *filename) {
    FileStats stats = {0, 0, 0, 0};
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return stats;

    char line[LINE_LEN];
    while (fgets(line, sizeof(line), fp) != NULL) {
        stats.lines++;
        stats.chars += strlen(line);

        int isBlank = 1;
        for (char *p = line; *p != '\0'; p++)
            if (*p != ' ' && *p != '\t' && *p != '\n') { isBlank = 0; break; }
        if (isBlank) stats.blank++;

        int inWord = 0;
        for (char *p = line; *p != '\0'; p++) {
            if (*p != ' ' && *p != '\t' && *p != '\n') {
                if (!inWord) { stats.words++; inWord = 1; }
            } else {
                inWord = 0;
            }
        }
    }

    fclose(fp);
    return stats;
}


void createSampleFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    fprintf(fp, "The C Programming Language\n");
    fprintf(fp, "==========================\n");
    fprintf(fp, "\n");
    fprintf(fp, "C is a general-purpose programming language created\n");
    fprintf(fp, "by Dennis Ritchie at Bell Labs in the early 1970s.\n");
    fprintf(fp, "\n");
    fprintf(fp, "Key features of C:\n");
    fprintf(fp, "  - Low-level memory access via pointers\n");
    fprintf(fp, "  - Portable and efficient compiled code\n");
    fprintf(fp, "  - Structured programming with functions\n");
    fprintf(fp, "  - Foundation for C++, Java, and Python\n");
    fprintf(fp, "\n");
    fprintf(fp, "C remains one of the most widely used languages\n");
    fprintf(fp, "in systems, embedded, and OS development today.\n");

    fclose(fp);
}



void displayFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\n  ✗ Error: Cannot open \"%s\".\n", filename);
        printf("    Check the filename and try again.\n");
        return;
    }

    printBanner("FILE CONTENTS");
    printDivider('-', 54);

    char line[LINE_LEN];
    int  lineNum = 1;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *nl = line;
        while (*nl != '\n' && *nl != '\0') nl++;
        if (*nl == '\n') *nl = '\0';

        printf("  %3d │ %s\n", lineNum++, line);
    }

    printDivider('-', 54);
    fclose(fp);
}

void displayStats(const char *filename, FileStats s) {
    printf("\n  ┌─────────────────────────────────────────┐\n");
    printf(  "  │             FILE SUMMARY                │\n");
    printf(  "  ├─────────────────────────────────────────┤\n");
    printf(  "  │  File         : %-23s  │\n", filename);
    printf(  "  │  Total Lines  : %-23d  │\n", s.lines);
    printf(  "  │  Blank Lines  : %-23d  │\n", s.blank);
    printf(  "  │  Word Count   : %-23d  │\n", s.words);
    printf(  "  │  Char Count   : %-23d  │\n", s.chars);
    printf(  "  └─────────────────────────────────────────┘\n\n");
}


int main() {
    printBanner("FILE READER PROGRAM");

    FILE *check = fopen(FILENAME, "r");
    if (check == NULL)
        createSampleFile(FILENAME);
    else
        fclose(check);

    displayFile(FILENAME);

    FileStats stats = analyzeFile(FILENAME);
    displayStats(FILENAME, stats);

    return 0;
}