#include <stdio.h>
#include <string.h>
#include <conio.h>

void mainMenu() {
    int choice = 0;
    int x = 1;
    while (x == 1) {
        printf("Main Menu:\n");
        printf("1. Manage Data [Admin Required]\n");
        printf("2. Play Game\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid Input\n");
            fflush(stdin);
            continue; //placeholder	
        }
        switch (choice) {
		case 1: {
    		int back = 0;
    		while (!back) {
        		char password[20];
        		int i = 0;
      				printf("Enter password (press 0 to go back): ");
      				while (1) {
            		char c = getch();
           			if (c == '\r') {  // Enter key
              				password[i] = '\0';  // Add null terminator to end string
              				break;
          				} else if (c == 8 && i > 0) {  // backspace character
              				printf("\b \b");
          				    i--;
      				    } else if (i < 19) {
      				        password[i++] = c;
      				        printf("*");
        			    }
        			}
        			if (strcmp(password, "adminpassword") == 0) {
        			    printf("\nAccess Granted. Proceeding to Manage Data.\n");
        			    // Call your function to manage data
        			    back = 1;
        			} else if (strcmp(password, "0") == 0) {
        			    printf("\nGoing back to main menu.\n");
        			    back = 1;
        			} else {
            			printf("\nInvalid Password. Try again.\n");
    			    }
    			}
    		break;
			}
            case 2: {
                printf("Proceeding to Play Game.\n");
                // Call your function to play game
                break;
            }
            case 3: {
                printf("Exiting program.\n");
                x = 0;
                break;
            }
            default: {
                printf("Error: Invalid Input\n");
                fflush(stdin);
                choice = 0;
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
