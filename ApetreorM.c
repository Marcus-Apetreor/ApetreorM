#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifyPassword() {
    char password[20];
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(password, "password123") == 0) {
        printf("Password accepted.\n");
        return 1;
    } else {
        printf("Password incorrect.\n");
        return 0;
    }
}

void displayMenu() {
    printf("Main Menu\n");
    printf("1. Manage Data (admin)\n");
    printf("2. Play (player)\n");
    printf("3. Exit\n");
}

int getInput() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    int passwordVerified = 0;
    while (!passwordVerified) {
        passwordVerified = verifyPassword();
    }

    int choice = 0;
    while (choice != 3) {
        displayMenu();
        choice = getInput();

        switch (choice) {
            case 1:
                printf("You selected 'Manage Data'.\n");
                // Add admin code here
                break;
            case 2:
                printf("You selected 'Play'.\n");
                // Add player code here
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Error: Invalid Input.\n");
        }
    }

    return 0;
}
