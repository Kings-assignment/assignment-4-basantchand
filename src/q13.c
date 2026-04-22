// Write a C program that copies the contents of one file to another file.

#include <stdio.h>
#include <string.h>
#include <time.h>

#define SOURCE_FILE "source.txt"
#define DEST_FILE   "destination.txt"
#define BUFFER_SIZE 1024


void printBanner(const char *title) {
    int len = strlen(title) + 4;
    printf("\n  ╔");
    for (int i = 0; i < len; i++) printf("═");
    printf("╗\n  ║  %s  ║\n  ╚", title);
    for (int i = 0; i < len; i++) printf("═");
    printf("╝\n\n");
}

void printDivider(char ch, int width) {
    printf("  ");
    for (int i = 0; i < width; i++) putchar(ch);
    putchar('\n');
}

void currentTimestamp(char *buffer, int size) {
    time_t     now = time(NULL);
    struct tm *t   = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}


void createSourceFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    fprintf(fp, "File Copy Program — Source File\n");
    fprintf(fp, "================================\n\n");
    fprintf(fp, "This content was written to the source file.\n");
    fprintf(fp, "Each line will be copied to the destination.\n\n");
    fprintf(fp, "Line 1: The quick brown fox jumps over the lazy dog.\n");
    fprintf(fp, "Line 2: C file I/O uses FILE pointers and fopen/fclose.\n");
    fprintf(fp, "Line 3: Always close files to flush the write buffer.\n\n");
    fprintf(fp, "--- End of source file ---\n");

    fclose(fp);
    printf("  [✔] Source file \"%s\" created.\n", filename);
}


typedef struct {
    long lines;
    long bytes;
} FileStats;

FileStats getFileStats(const char *filename) {
    FileStats stats = {0, 0};
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return stats;

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        stats.lines++;
        stats.bytes += strlen(buffer);
    }

    fclose(fp);
    return stats;
}


typedef struct {
    long  linesCopied;
    long  bytesCopied;
    int   success;
} CopyResult;

CopyResult copyFile(const char *src, const char *dest) {
    CopyResult result = {0, 0, 0};

    FILE *srcFp  = fopen(src,  "r");
    if (srcFp == NULL) {
        printf("  [✗] Error: Cannot open source \"%s\".\n", src);
        return result;
    }

    FILE *destFp = fopen(dest, "w");
    if (destFp == NULL) {
        printf("  [✗] Error: Cannot open destination \"%s\".\n", dest);
        fclose(srcFp);
        return result;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), srcFp) != NULL) {
        fputs(buffer, destFp);
        result.linesCopied++;
        result.bytesCopied += strlen(buffer);
    }

    fclose(srcFp);
    fclose(destFp);
    result.success = 1;
    return result;
}


void displayFileContents(const char *filename, const char *label) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("  [✗] Cannot read \"%s\".\n", filename);
        return;
    }

    printf("  %s (\"%s\"):\n", label, filename);
    printDivider('-', 54);

    char   buffer[BUFFER_SIZE];
    int    lineNum = 1;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *nl = buffer;
        while (*nl != '\n' && *nl != '\0') nl++;
        if (*nl == '\n') *nl = '\0';
        printf("  %3d │ %s\n", lineNum++, buffer);
    }

    printDivider('-', 54);
    fclose(fp);
}

void displayCopyReport(const char *src, const char *dest,
                       CopyResult r, const char *timestamp) {
    printf("  ┌──────────────────────────────────────────────┐\n");
    printf("  │             COPY OPERATION REPORT            │\n");
    printf("  ├──────────────────────────────────────────────┤\n");
    printf("  │  Status      : %-29s  │\n", r.success ? "SUCCESS ✔" : "FAILED ✗");
    printf("  │  Source      : %-29s  │\n", src);
    printf("  │  Destination : %-29s  │\n", dest);
    printf("  │  Timestamp   : %-29s  │\n", timestamp);
    printf("  │  Lines       : %-29ld  │\n", r.linesCopied);
    printf("  │  Bytes       : %-29ld  │\n", r.bytesCopied);
    printf("  └──────────────────────────────────────────────┘\n\n");
}

void displayDiff(const char *src, const char *dest) {
    FileStats s = getFileStats(src);
    FileStats d = getFileStats(dest);

    printf("  ┌───────────────────────┬──────────────┬──────────────┐\n");
    printf("  │ Metric                │ Source       │ Destination  │\n");
    printf("  ├───────────────────────┼──────────────┼──────────────┤\n");
    printf("  │ Lines                 │ %-12ld │ %-12ld │\n", s.lines, d.lines);
    printf("  │ Bytes                 │ %-12ld │ %-12ld │\n", s.bytes, d.bytes);
    printf("  │ Match                 │ %-27s │\n",
           (s.lines == d.lines && s.bytes == d.bytes) ? "✔ Identical" : "✗ Mismatch");
    printf("  └───────────────────────┴──────────────┴──────────────┘\n\n");
}


int main() {
    char timestamp[32];

    printBanner("FILE COPY PROGRAM");

    FILE *check = fopen(SOURCE_FILE, "r");
    if (check == NULL)
        createSourceFile(SOURCE_FILE);
    else {
        fclose(check);
        printf("  [✔] Source file \"%s\" found.\n", SOURCE_FILE);
    }

    printf("\n");
    displayFileContents(SOURCE_FILE, "SOURCE FILE");

    printf("\n  Copying \"%s\"  →  \"%s\" ...\n\n", SOURCE_FILE, DEST_FILE);
    currentTimestamp(timestamp, sizeof(timestamp));
    CopyResult result = copyFile(SOURCE_FILE, DEST_FILE);

    
    displayCopyReport(SOURCE_FILE, DEST_FILE, result, timestamp);

    if (!result.success) return 1;

    printf("  VERIFICATION — FILE COMPARISON:\n");
    displayDiff(SOURCE_FILE, DEST_FILE);

    displayFileContents(DEST_FILE, "DESTINATION FILE");

    return 0;
}