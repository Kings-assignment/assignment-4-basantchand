// Write a C program that defines a structure Book with members: title, author, and price. 
// Allow the user to enter details of n books and then display all books whose price is above a 
// user-defined value.



#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 100

typedef struct {
    char  title[STR_LEN];
    char  author[STR_LEN];
    float price;
} Book;


void stripNewline(char *str) {
    while (*str != '\n' && *str != '\0') str++;
    if (*str == '\n') *str = '\0';
}

void flushInput() {
    while (getchar() != '\n');
}


void readBook(Book *b, int index) {
    printf("\n  Enter details for Book %d:\n", index + 1);

    printf("    Title  : ");
    fgets(b->title, STR_LEN, stdin);
    stripNewline(b->title);

    printf("    Author : ");
    fgets(b->author, STR_LEN, stdin);
    stripNewline(b->author);

    printf("    Price  : $");
    scanf("%f", &b->price);
    flushInput();
}

void printDivider() {
    printf("  ├──────┼──────────────────────────┼──────────────────────┼──────────────┤\n");
}

void printHeader() {
    printf("\n  ┌──────┬──────────────────────────┬──────────────────────┬──────────────┐\n");
    printf(  "  │  No. │ Title                    │ Author               │ Price        │\n");
    printDivider();
}

void printFooter() {
    printf("  └──────┴──────────────────────────┴──────────────────────┴──────────────┘\n");
}

void printBook(const Book *b, int index) {
    printf("  │ %-4d │ %-26.26s │ %-20.20s │ $%-11.2f │\n",
           index, b->title, b->author, b->price);
}


int filterByPrice(Book *books, int n, float threshold) {
    int found = 0;

    printHeader();
    for (int i = 0; i < n; i++) {
        if (books[i].price > threshold) {
            printBook(&books[i], i + 1);
            if (i < n - 1) printDivider();
            found++;
        }
    }
    printFooter();
    return found;
}



int main() {
    int n;

    printf("╔══════════════════════════════════════╗\n");
    printf("║         BOOK INVENTORY SYSTEM        ║\n");
    printf("╚══════════════════════════════════════╝\n");

    printf("\nHow many books do you want to enter? ");
    scanf("%d", &n);
    flushInput();

    if (n <= 0) {
        printf("Error: Number of books must be positive.\n");
        return 1;
    }

    Book *books = (Book *)malloc(n * sizeof(Book));
    if (books == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        readBook(&books[i], i);

    printf("\n  ALL BOOKS:\n");
    printHeader();
    for (int i = 0; i < n; i++) {
        printBook(&books[i], i + 1);
        if (i < n - 1) printDivider();
    }
    printFooter();

    float threshold;
    printf("\nEnter minimum price to filter: $");
    scanf("%f", &threshold);

    printf("\n  BOOKS WITH PRICE ABOVE $%.2f:\n", threshold);
    int found = filterByPrice(books, n, threshold);

    if (found == 0)
        printf("  No books found above $%.2f.\n", threshold);
    else
        printf("\n  %d book(s) found above $%.2f.\n", found, threshold);

    free(books);
    books = NULL;

    return 0;
}