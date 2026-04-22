// Write a C program that defines a structure Employee with members: name, employee ID, and salary. 
// Take input for 5 employees and display the details of the employee with the highest salary.


#include <stdio.h>

#define MAX_EMPLOYEES 5
#define NAME_LEN      50

typedef struct {
    char  name[NAME_LEN];
    int   employeeID;
    float salary;
} Employee;

void readEmployee(Employee *e, int index) {
    printf("\n  Enter details for Employee %d:\n", index + 1);

    printf("    Name        : ");
    fgets(e->name, NAME_LEN, stdin);
    char *nl = e->name;
    while (*nl != '\n' && *nl != '\0') nl++;
    if (*nl == '\n') *nl = '\0';

    printf("    Employee ID : ");
    scanf("%d", &e->employeeID);

    printf("    Salary      : ");
    scanf("%f", &e->salary);

    while (getchar() != '\n');
}

Employee *highestSalary(Employee employees[], int size) {
    Employee *top = &employees[0];
    for (int i = 1; i < size; i++) {
        if (employees[i].salary > top->salary)
            top = &employees[i];
    }
    return top;
}

void displayEmployee(const Employee *e, int rank) {
    printf("  %-4d %-20s %-15d $%.2f\n",
           rank, e->name, e->employeeID, e->salary);
}

void displayAll(Employee employees[], int size) {
    printf("\n┌─────────────────────────────────────────────────────┐\n");
    printf(  "│               ALL EMPLOYEE RECORDS                 │\n");
    printf(  "├──────┬──────────────────────┬───────────────┬──────┤\n");
    printf(  "│  No. │ Name                 │ Employee ID   │ Salary        │\n");
    printf(  "├──────┼──────────────────────┼───────────────┼──────┤\n");
    for (int i = 0; i < size; i++)
        displayEmployee(&employees[i], i + 1);
    printf(  "└──────┴──────────────────────┴───────────────┴──────┘\n");
}

void displayTopEarner(const Employee *e) {
    printf("\n┌─────────────────────────────────────┐\n");
    printf(  "│         TOP EARNER                  │\n");
    printf(  "├─────────────────────────────────────┤\n");
    printf(  "│  Name        : %-20s │\n", e->name);
    printf(  "│  Employee ID : %-20d │\n", e->employeeID);
    printf(  "│  Salary      : $%-19.2f │\n", e->salary);
    printf(  "└─────────────────────────────────────┘\n");
}

int main() {
    Employee employees[MAX_EMPLOYEES];

    printf("╔══════════════════════════════════════╗\n");
    printf("║       EMPLOYEE DATA ENTRY            ║\n");
    printf("╚══════════════════════════════════════╝\n");

    for (int i = 0; i < MAX_EMPLOYEES; i++)
        readEmployee(&employees[i], i);

    displayAll(employees, MAX_EMPLOYEES);

    Employee *top = highestSalary(employees, MAX_EMPLOYEES);
    displayTopEarner(top);

    return 0;
}