// Write a C program that defines a structure called Student with members: name, roll number,
// and marks. Prompt the user to enter data for one student and display the information.

#include <stdio.h>

#define NAME_LEN 50

typedef struct
{
    char name[NAME_LEN];
    int rollNumber;
    float marks;
} Student;

void inputStudent(Student *s)
{
    printf("  Enter name       : ");
    fgets(s->name, NAME_LEN, stdin);

    char *nl = s->name;
    while (*nl != '\n' && *nl != '\0')
        nl++;
    if (*nl == '\n')
        *nl = '\0';

    printf("  Enter roll number : ");
    scanf("%d", &s->rollNumber);

    printf("  Enter marks       : ");
    scanf("%f", &s->marks);
}

void displayStudent(const Student *s)
{
    printf("\n┌─────────────────────────────┐\n");
    printf("│      STUDENT RECORD         │\n");
    printf("├─────────────────────────────┤\n");
    printf("│  Name        : %-14s │\n", s->name);
    printf("│  Roll Number : %-14d │\n", s->rollNumber);
    printf("│  Marks       : %-14.2f │\n", s->marks);
    printf("│  Grade       : %-14s │\n",
           s->marks >= 90 ? "A+" : s->marks >= 80 ? "A"
                               : s->marks >= 70   ? "B"
                               : s->marks >= 60   ? "C"
                               : s->marks >= 50   ? "D"
                                                  : "F");
    printf("└─────────────────────────────┘\n");
}

int main()
{
    Student s;

    printf("Enter student details:\n");
    inputStudent(&s);
    displayStudent(&s);

    return 0;
}