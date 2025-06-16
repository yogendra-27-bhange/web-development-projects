#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15

struct Contact {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_NAME_LENGTH];
};

// Function prototypes
void addContact(struct Contact contacts[], int *count);
void displayContacts(struct Contact contacts[], int count);
void searchContact(struct Contact contacts[], int count);
void updateContact(struct Contact contacts[], int count);
void deleteContact(struct Contact contacts[], int *count);
void saveToFile(struct Contact contacts[], int count);
void loadFromFile(struct Contact contacts[], int *count);

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;

    // Load existing contacts
    loadFromFile(contacts, &count);

    while (1) {
        printf("\n=== Phone Directory System ===\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(contacts, &count);
                break;
            case 2:
                displayContacts(contacts, count);
                break;
            case 3:
                searchContact(contacts, count);
                break;
            case 4:
                updateContact(contacts, count);
                break;
            case 5:
                deleteContact(contacts, &count);
                break;
            case 6:
                saveToFile(contacts, count);
                printf("Contacts saved successfully. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addContact(struct Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Maximum contact limit reached!\n");
        return;
    }

    printf("\nEnter Contact Details:\n");
    printf("Name: ");
    scanf(" %[^\n]s", contacts[*count].name);
    printf("Phone: ");
    scanf("%s", contacts[*count].phone);
    printf("Email: ");
    scanf("%s", contacts[*count].email);

    (*count)++;
    printf("Contact added successfully!\n");
}

void displayContacts(struct Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts in the directory!\n");
        return;
    }

    printf("\n%-30s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-30s %-15s %-30s\n", 
               contacts[i].name,
               contacts[i].phone,
               contacts[i].email);
    }
}

void searchContact(struct Contact contacts[], int count) {
    char searchTerm[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter name or phone number to search: ");
    scanf(" %[^\n]s", searchTerm);

    printf("\nSearch Results:\n");
    printf("%-30s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (strstr(contacts[i].name, searchTerm) != NULL ||
            strstr(contacts[i].phone, searchTerm) != NULL) {
            printf("%-30s %-15s %-30s\n", 
                   contacts[i].name,
                   contacts[i].phone,
                   contacts[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts found matching the search criteria.\n");
    }
}

void updateContact(struct Contact contacts[], int count) {
    char searchName[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter name of contact to update: ");
    scanf(" %[^\n]s", searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            printf("\nEnter new details:\n");
            printf("Phone: ");
            scanf("%s", contacts[i].phone);
            printf("Email: ");
            scanf("%s", contacts[i].email);
            printf("Contact updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }
}

void deleteContact(struct Contact contacts[], int *count) {
    char searchName[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter name of contact to delete: ");
    scanf(" %[^\n]s", searchName);

    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            // Shift remaining contacts up
            for (int j = i; j < *count - 1; j++) {
                strcpy(contacts[j].name, contacts[j + 1].name);
                strcpy(contacts[j].phone, contacts[j + 1].phone);
                strcpy(contacts[j].email, contacts[j + 1].email);
            }
            (*count)--;
            printf("Contact deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }
}

void saveToFile(struct Contact contacts[], int count) {
    FILE *file = fopen("phone_directory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s\n", 
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email);
    }

    fclose(file);
}

void loadFromFile(struct Contact contacts[], int *count) {
    FILE *file = fopen("phone_directory.txt", "r");
    if (file == NULL) {
        printf("No existing contacts found.\n");
        return;
    }

    *count = 0;
    while (*count < MAX_CONTACTS && 
           fscanf(file, "%s %s %s", 
                  contacts[*count].name,
                  contacts[*count].phone,
                  contacts[*count].email) == 3) {
        (*count)++;
    }

    fclose(file);
    printf("Loaded %d contacts.\n", *count);
} 