#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int isLeapYear(int year);
int getDayOfWeek(int year, int month, int day);
void printMonth(int year, int month);
void printYear(int year);
int getDaysInMonth(int year, int month);
char* getMonthName(int month);

int main() {
    int year, choice;

    while (1) {
        printf("\n=== Calendar Program ===\n");
        printf("1. Display Month\n");
        printf("2. Display Year\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter year: ");
                scanf("%d", &year);
                printf("Enter month (1-12): ");
                int month;
                scanf("%d", &month);
                if (month >= 1 && month <= 12) {
                    printMonth(year, month);
                } else {
                    printf("Invalid month!\n");
                }
                break;

            case 2:
                printf("Enter year: ");
                scanf("%d", &year);
                printYear(year);
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

char* getMonthName(int month) {
    char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return months[month - 1];
}

int getDayOfWeek(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    return (h + 5) % 7; // Convert to 0-6 where 0 is Sunday
}

void printMonth(int year, int month) {
    int daysInMonth = getDaysInMonth(year, month);
    int firstDay = getDayOfWeek(year, month, 1);
    char* monthName = getMonthName(month);

    printf("\n     %s %d\n", monthName, year);
    printf("Su Mo Tu We Th Fr Sa\n");
    printf("---------------------\n");

    // Print leading spaces
    for (int i = 0; i < firstDay; i++) {
        printf("   ");
    }

    // Print days
    for (int day = 1; day <= daysInMonth; day++) {
        printf("%2d ", day);
        if ((firstDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void printYear(int year) {
    printf("\n=== Calendar for %d ===\n", year);
    
    for (int month = 1; month <= 12; month++) {
        printMonth(year, month);
        printf("\n");
    }
} 