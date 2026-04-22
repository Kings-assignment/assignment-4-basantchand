// Write a C program that uses a structure Point with members x and y, representing coordinates. 
// Write a function that takes two Point structures and returns the distance between them.

#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Point;

float distance(Point a, Point b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrtf(dx * dx + dy * dy);
}

Point midpoint(Point a, Point b) {
    Point mid;
    mid.x = (a.x + b.x) / 2.0f;
    mid.y = (a.y + b.y) / 2.0f;
    return mid;
}

float slope(Point a, Point b) {
    if (b.x - a.x == 0) return 0.0f;
    return (b.y - a.y) / (b.x - a.x);
}


Point readPoint(const char *label) {
    Point p;
    printf("  Enter %s coordinates:\n", label);
    printf("    x : ");
    scanf("%f", &p.x);
    printf("    y : ");
    scanf("%f", &p.y);
    return p;
}

void displayPoint(const char *label, Point p) {
    printf("  %-10s →  (%.2f, %.2f)\n", label, p.x, p.y);
}

int main() {
    printf("╔══════════════════════════════════════╗\n");
    printf("║        POINT DISTANCE CALCULATOR     ║\n");
    printf("╚══════════════════════════════════════╝\n");

    printf("\nPoint A:\n");
    Point a = readPoint("Point A");

    printf("\nPoint B:\n");
    Point b = readPoint("Point B");

    float dist = distance(a, b);
    Point mid  = midpoint(a, b);
    float sl   = slope(a, b);

    printf("\n┌─────────────────────────────────────────┐\n");
    printf(  "│              RESULTS                    │\n");
    printf(  "├─────────────────────────────────────────┤\n");
    displayPoint("Point A", a);
    displayPoint("Point B", b);
    printf(  "  ─────────────────────────────────────── \n");
    printf(  "  Distance   →  %.4f units\n",   dist);
    printf(  "  Midpoint   →  (%.2f, %.2f)\n", mid.x, mid.y);
    printf(  "  Slope      →  %.4f\n",          sl);
    printf(  "└─────────────────────────────────────────┘\n");

    printf("\n  COORDINATE GRID:\n\n");

    int rows = 9, cols = 21;
    int ax = (int)roundf(a.x), ay = (int)roundf(a.y);
    int bx = (int)roundf(b.x), by = (int)roundf(b.y);
    int mx = (int)roundf(mid.x), my = (int)roundf(mid.y);

    for (int row = rows / 2; row >= -(rows / 2); row--) {
        printf("  %2d │", row);
        for (int col = -(cols / 2); col <= cols / 2; col++) {
            if      (col == ax && row == ay) printf(" A");
            else if (col == bx && row == by) printf(" B");
            else if (col == mx && row == my) printf(" M");
            else if (row == 0 && col == 0)   printf(" +");
            else if (row == 0)               printf(" ─");
            else if (col == 0)               printf(" │");
            else                             printf("  ");
        }
        printf("\n");
    }
    printf("     └");
    for (int col = -(cols / 2); col <= cols / 2; col++)
        printf("──");
    printf("\n      ");
    for (int col = -(cols / 2); col <= cols / 2; col += 2)
        printf("%-4d", col);
    printf("\n\n  A = Point A   B = Point B   M = Midpoint\n");

    return 0;
}