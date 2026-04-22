// Write a C program that defines a structure Car with members: model, year, and mileage. 
// Store information for 3 cars and find the car with the lowest mileage.
#include <stdio.h>
#include <string.h>

#define NUM_CARS   3
#define STR_LEN    50

typedef struct {
    char  model[STR_LEN];
    int   year;
    float mileage;
} Car;


void stripNewline(char *str) {
    while (*str != '\n' && *str != '\0') str++;
    if (*str == '\n') *str = '\0';
}

void flushInput() {
    while (getchar() != '\n');
}


void readCar(Car *c, int index) {
    printf("\n  Enter details for Car %d:\n", index + 1);

    printf("    Model   : ");
    fgets(c->model, STR_LEN, stdin);
    stripNewline(c->model);

    printf("    Year    : ");
    scanf("%d", &c->year);

    printf("    Mileage : ");
    scanf("%f", &c->mileage);
    flushInput();
}

void printDivider() {
    printf("  ├──────┬──────────────────────┬────────┬────────────────┤\n");
}

void printHeader() {
    printf("\n  ┌──────────────────────────────────────────────────────┐\n");
    printf(  "  │  No. │ Model                │  Year  │ Mileage        │\n");
    printDivider();
}

void printFooter() {
    printf("  └──────┴──────────────────────┴────────┴────────────────┘\n");
}

void printCar(const Car *c, int index, int highlight) {
    if (highlight)
        printf("  │ ▶%-3d │ %-20.20s │  %4d  │ %10.1f mi  │  ← Lowest\n",
               index, c->model, c->year, c->mileage);
    else
        printf("  │  %-3d │ %-20.20s │  %4d  │ %10.1f mi  │\n",
               index, c->model, c->year, c->mileage);
}


Car *lowestMileage(Car cars[], int size) {
    Car *lowest = &cars[0];
    for (int i = 1; i < size; i++) {
        if (cars[i].mileage < lowest->mileage)
            lowest = &cars[i];
    }
    return lowest;
}


void displayAll(Car cars[], int size, const Car *highlight) {
    printf("\n  ALL CARS:\n");
    printHeader();
    for (int i = 0; i < size; i++) {
        printCar(&cars[i], i + 1, &cars[i] == highlight);
        if (i < size - 1) printDivider();
    }
    printFooter();
}

void displayWinner(const Car *c) {
    int age = 2025 - c->year;

    printf("\n  ┌──────────────────────────────────────────┐\n");
    printf(  "  │           LOWEST MILEAGE CAR             │\n");
    printf(  "  ├──────────────────────────────────────────┤\n");
    printf(  "  │  Model      : %-26.26s  │\n", c->model);
    printf(  "  │  Year       : %-26d  │\n", c->year);
    printf(  "  │  Mileage    : %-10.1f mi               │\n", c->mileage);
    printf(  "  │  Age        : %-2d year(s)                  │\n", age);
    printf(  "  │  Avg/Year   : %-10.1f mi/year           │\n",
             age > 0 ? c->mileage / age : c->mileage);
    printf(  "  └──────────────────────────────────────────┘\n");
}


void displayChart(Car cars[], int size, const Car *lowest) {
    printf("\n  MILEAGE COMPARISON:\n\n");

    float maxMileage = cars[0].mileage;
    for (int i = 1; i < size; i++)
        if (cars[i].mileage > maxMileage)
            maxMileage = cars[i].mileage;

    int barWidth = 30;
    for (int i = 0; i < size; i++) {
        int filled = (int)((cars[i].mileage / maxMileage) * barWidth);
        printf("  %-20.20s │", cars[i].model);
        for (int j = 0; j < barWidth; j++)
            printf("%s", j < filled ? "█" : "░");
        printf("│ %.0f mi %s\n",
               cars[i].mileage, &cars[i] == lowest ? "← lowest" : "");
    }
}



int main() {
    Car cars[NUM_CARS];

    printf("╔═══════════════════════════════════════╗\n");
    printf("║         CAR INVENTORY SYSTEM          ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    for (int i = 0; i < NUM_CARS; i++)
        readCar(&cars[i], i);

    Car *lowest = lowestMileage(cars, NUM_CARS);

    displayAll(cars, NUM_CARS, lowest);
    displayWinner(lowest);
    displayChart(cars, NUM_CARS, lowest);

    return 0;
}