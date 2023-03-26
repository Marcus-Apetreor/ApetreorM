#include <stdio.h>
#include <string.h>

int password() {
    char user_password[20];
    char password[] = "12345";
    
    printf("Enter password: ");
    scanf("%s", user_password);
    
    if(strcmp(user_password, password) == 0) {
        printf("Access granted.\n");
        return 1;
    }
    else {
        printf("Access denied.\n");
        return 0;
    }
}


