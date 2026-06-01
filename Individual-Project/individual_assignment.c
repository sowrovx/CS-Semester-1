#include <stdio.h>

// global variable
int totalStudents = 5;

// function prototypes
float calculateAverage(int m1, int m2, int m3);
void displayResult(char name[], int total, float average, char grade);

int main()
{
    // local variables
    int i;
    
    // student information
    char name[30];
    int mark1, mark2, mark3;
    int total;
    float average;
    char grade;

    printf("STUDENT ACADEMIC PERFORMANCE SYSTEM\n");

    // loop for multiple students
    for (i = 1; i <= totalStudents; i++)
    {
        printf("\nStudent %d\n", i);

        // input student name 
        printf("Enter student name: ");
        scanf("%s", name);

        // input subject marks
        printf("Enter marks for Subject 1: ");
        scanf("%d", &mark1);

        printf("Enter marks for Subject 2: ");
        scanf("%d", &mark2);

        printf("Enter marks for Subject 3: ");
        scanf("%d", &mark3);

        // check for invalid marks
        if (mark1 < 0 || mark2 < 0 || mark3 < 0)
        {
            printf("Invalid marks. Student skipped.\n");
            continue;   // move to next student
        }

        // calculate total marks
        total = mark1 + mark2 + mark3;

        // get average from function
        average = calculateAverage(mark1, mark2, mark3);

        // decide grade
        if (average >= 80)
            grade = 'A';
        else if (average >= 65)
            grade = 'B';
        else if (average >= 50)
            grade = 'C';
        else
            grade = 'F';

        // show student result
        displayResult(name, total, average, grade);
    }

    return 0;
}

// calculates average marks
float calculateAverage(int m1, int m2, int m3)
{
    return (m1 + m2 + m3) / 3.0;
}

// displays final result
void displayResult(char name[], int total, float average, char grade)
{
    printf("\nName    : %s", name);
    printf("\nTotal   : %d", total);
    printf("\nAverage : %.2f", average);
    printf("\nGrade   : %c\n", grade);
}