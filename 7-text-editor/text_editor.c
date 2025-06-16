#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

// Function prototypes
void createNewFile();
void openFile();
void saveFile(char *filename, char content[][MAX_LINE_LENGTH], int lineCount);
void displayContent(char content[][MAX_LINE_LENGTH], int lineCount);
void editContent(char content[][MAX_LINE_LENGTH], int *lineCount);

int main() {
    int choice;

    while (1) {
        printf("\n=== Text Editor ===\n");
        printf("1. Create New File\n");
        printf("2. Open File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createNewFile();
                break;
            case 2:
                openFile();
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

void createNewFile() {
    char filename[100];
    char content[MAX_LINES][MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("Enter filename (with .txt extension): ");
    scanf("%s", filename);

    printf("\nEnter your text (type 'END' on a new line to finish):\n");
    while (lineCount < MAX_LINES) {
        printf("%d: ", lineCount + 1);
        scanf(" %[^\n]s", content[lineCount]);
        
        if (strcmp(content[lineCount], "END") == 0) {
            break;
        }
        lineCount++;
    }

    saveFile(filename, content, lineCount);
    printf("File created and saved successfully!\n");
}

void openFile() {
    char filename[100];
    char content[MAX_LINES][MAX_LINE_LENGTH];
    int lineCount = 0;
    int choice;

    printf("Enter filename to open: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found!\n");
        return;
    }

    // Read file content
    while (lineCount < MAX_LINES && fgets(content[lineCount], MAX_LINE_LENGTH, file)) {
        // Remove newline character if present
        content[lineCount][strcspn(content[lineCount], "\n")] = 0;
        lineCount++;
    }
    fclose(file);

    while (1) {
        printf("\n=== File: %s ===\n", filename);
        printf("1. Display Content\n");
        printf("2. Edit Content\n");
        printf("3. Save Changes\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayContent(content, lineCount);
                break;
            case 2:
                editContent(content, &lineCount);
                break;
            case 3:
                saveFile(filename, content, lineCount);
                printf("Changes saved successfully!\n");
                break;
            case 4:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void saveFile(char *filename, char content[][MAX_LINE_LENGTH], int lineCount) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not save file!\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", content[i]);
    }

    fclose(file);
}

void displayContent(char content[][MAX_LINE_LENGTH], int lineCount) {
    if (lineCount == 0) {
        printf("File is empty!\n");
        return;
    }

    printf("\n=== File Content ===\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i + 1, content[i]);
    }
}

void editContent(char content[][MAX_LINE_LENGTH], int *lineCount) {
    int choice;
    int lineNum;
    char newLine[MAX_LINE_LENGTH];

    printf("\n=== Edit Options ===\n");
    printf("1. Add Line\n");
    printf("2. Edit Line\n");
    printf("3. Delete Line\n");
    printf("4. Return\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Add Line
            if (*lineCount >= MAX_LINES) {
                printf("Maximum line limit reached!\n");
                return;
            }
            printf("Enter new line: ");
            scanf(" %[^\n]s", content[*lineCount]);
            (*lineCount)++;
            printf("Line added successfully!\n");
            break;

        case 2: // Edit Line
            printf("Enter line number to edit (1-%d): ", *lineCount);
            scanf("%d", &lineNum);
            if (lineNum < 1 || lineNum > *lineCount) {
                printf("Invalid line number!\n");
                return;
            }
            printf("Enter new content: ");
            scanf(" %[^\n]s", content[lineNum - 1]);
            printf("Line edited successfully!\n");
            break;

        case 3: // Delete Line
            printf("Enter line number to delete (1-%d): ", *lineCount);
            scanf("%d", &lineNum);
            if (lineNum < 1 || lineNum > *lineCount) {
                printf("Invalid line number!\n");
                return;
            }
            // Shift remaining lines up
            for (int i = lineNum - 1; i < *lineCount - 1; i++) {
                strcpy(content[i], content[i + 1]);
            }
            (*lineCount)--;
            printf("Line deleted successfully!\n");
            break;

        case 4:
            return;

        default:
            printf("Invalid choice!\n");
    }
} 