#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char topic[20];
    int question_number;
    char question[150];
    char choices[3][30];
    char correct_choice[30];
} Question;

int find_question(Question *questions, int num_questions, char *question)
{
	int i, t=-1;
	// Searches for questions that have same name as input
    for (i = 0; i < num_questions; i++) {
        if (strcmp(questions[i].question, question) == 0) {
            t=i;
        }
    }
    // Returns -1 if there are no same questions
    return t;
}

void add_record(Question *questions, int *num_questions)
{
    char question[150];
    char correct_choice[30];
    char choice1[30];
    char choice2[30];
    char choice3[30];
    char topic[20];
    int topic_questions = 0;
    int function = 1;

    // Ask for question and answer
    printf("Enter the question: ");
    getchar();  // Consume the newline character
    fgets(question, 150, stdin);
    question[strcspn(question, "\n")] = '\0';

    // Check if question already exists
    int index = find_question(questions, *num_questions, question);
    // if same question found
    if (index != -1) {
        printf("The question already exists:\n");
        printf("Topic: %s\n", questions[index].topic);
        printf("Question: %s\n", questions[index].question);
        printf("Choice 1: %s\n", questions[index].choices[0]);
        printf("Choice 2: %s\n", questions[index].choices[1]);
        printf("Choice 3: %s\n", questions[index].choices[2]);
        printf("Correct choice: %s\n", questions[index].correct_choice);
        // function = 0; to skip the rest of the function
        function = 0;
    }

	// If statement to skip rest of the function
	if (function == 1){
		
    // Ask for topic and choices
    printf("Enter the topic: ");
	scanf(" %[^\n]", topic); // read input until newline character is encountered	
	
    int i;
	for (i = 0; i < *num_questions; i++) {
    if (strcmp(questions[i].topic, topic) == 0) {
        topic_questions++;
    	}
	}
	int question_number = topic_questions + 1;

	printf("Enter choice 1: ");
	scanf(" %[^\n]", choice1);

	printf("Enter choice 2: ");
	scanf(" %[^\n]", choice2);

	printf("Enter choice 3: ");
	scanf(" %[^\n]", choice3);
	
	printf("Enter correct choice: ");
	scanf(" %[^\n]", correct_choice);

    // Add the record to the collection
    Question new_question;
    strcpy(new_question.topic, topic);
    new_question.question_number = question_number;
    strcpy(new_question.question, question);
    strcpy(new_question.choices[0], choice1);
    strcpy(new_question.choices[1], choice2);
    strcpy(new_question.choices[2], choice3);
    strcpy(new_question.correct_choice, correct_choice);

    questions[*num_questions] = new_question;
    (*num_questions)++;
    printf("Record added successfully!\n");
	}
}

void edit_record(Question *questions, int *num_questions)
{
    int choice = 0;
	int x = 1;
	int index;
	int errorChecker = 1;
	
	// loop to ask for input again if error
	while (errorChecker == 1){
    	// Ask for index of question to edit
		printf("Enter the index of the question to edit (1-%d): ", *num_questions);
		scanf("%d", &index);
		getchar();  // Consume the newline character

		// Validate the index
		if (index < 1 || index > *num_questions) {
    		printf("Invalid index. Please input a valid index.\n");
		} else {
    		index--;  // Decrement index to match array index
    		errorChecker = 0;
		}	
	}

    // Prompt for new information
    char new_question[150];
    char new_choice1[30];
    char new_choice2[30];
    char new_choice3[30];
    char new_topic[20];
    char new_correct_choice[30];
	
	while (x == 1){
		printf("Edit Menu: \n");
		printf("1. Edit Question \n");
		printf("2. Edit Topic \n");
		printf("3. Edit Choice 1 \n");
		printf("4. Edit Choice 2 \n");
		printf("5. Edit Choice 3 \n");
		printf("6. Edit Correct Choice \n");
		printf("0. Go Back \n");
		if (scanf("%d", &choice) != 1) {
			getchar();  // Consume the newline character
            printf("Error: Invalid Input\n");
            fflush(stdin);
            choice = 0;
        }
		switch (choice){
			case 1: {
				getchar();  // Consume the newline character
    			printf("Enter the new question: ");
    			scanf("%[^\n]%*c", new_question);
    			strcpy(questions[index].question, new_question);
    			printf("Record updated successfully!\n");
    			break;
    		}
			case 2: {
    			printf("Enter the new topic: ");
    			scanf("%[^\n]%*c", new_topic);
    			strcpy(questions[index].topic, new_topic);
    			printf("Record updated successfully!\n");
				break;
			}
			case 3: {
    			printf("Enter the new choice 1: ");
    			scanf("%[^\n]%*c", new_choice1);
    			strcpy(questions[index].choices[0], new_choice1);
    			printf("Record updated successfully!\n");
				break;
			}
			case 4: {
    			printf("Enter the new choice 2: ");
    			scanf("%[^\n]%*c", new_choice2);
    			strcpy(questions[index].choices[1], new_choice2);
    			printf("Record updated successfully!\n");
			break;
			}
			case 5: {
    			printf("Enter the new choice 3: ");
    			scanf("%[^\n]%*c", new_choice3);
    			strcpy(questions[index].choices[2], new_choice3);
    			printf("Record updated successfully!\n");
    		break;
    		}
			case 6: {
				printf("Enter the new correct choice: ");
    			scanf("%[^\n]%*c", new_correct_choice);
    			strcpy(questions[index].correct_choice, new_correct_choice);
    			printf("Record updated successfully!\n");
    		break;
    		}
			case 0: {
				printf("Exiting edit menu");
				x = 0;
				break;
			}
			default: {
				printf("Error: Invalid Input\n");
            	fflush(stdin);
            	choice = 0;
				break;
			}
		}
	}
}

void delete_record(Question *questions, int *num_questions) {
    int index, i;
    printf("Enter the number of the question to delete: ");
    if (scanf("%d", &index) < 1) {
        printf("Error: Invalid Input\n");
        fflush(stdin);
        return;
    }
    if (index < 1 || index > *num_questions) {
        printf("Error: Invalid Index\n");
        return;
    }
    // Shift all the elements after the deleted element to fill the gap
    for (i = index - 1; i < *num_questions - 1; i++) {
        questions[i] = questions[i+1];
    }
    (*num_questions)--;  // Decrement the number of questions
    printf("Record deleted successfully.\n");
}

void play_game() {
}

void main_menu(Question *questions, int num_questions, char *question) {
    int choice = 0;
    int dataChoice = 0;
    int adminAccess = 1;
    int x = 1;
    while (x == 1) {
        printf("Main Menu:\n");
        printf("1. Manage Data [Admin Required]\n");
        printf("2. Play Game\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid Input\n");
            fflush(stdin);
            choice = 0;
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
            		} else if (c == 8) {  // backspace character
                		if (i > 0) {
                			printf("\b \b");
                			i--;
                		}
            		} else if (i < 19) {
                		password[i++] = c;
                		printf("*");
            		}
        		}
        		if (strcmp(password, "adminpassword") == 0) {
            		printf("\nAccess Granted. Proceeding to Manage Data.\n");
            		while (adminAccess == 1) {
                		printf("\nManage Data Menu:\n");
                		printf("1. Add Record\n");
                		printf("2. Edit Record\n");
                		printf("3. Delete Record\n");
                		printf("0. Sign Out\n");
                		printf("Enter your choice: ");
                		if (scanf("%d", &dataChoice) != 1) {
                    		printf("Error: Invalid Input\n");
                    		fflush(stdin);
                    		dataChoice = 0;
                		}
                		switch (dataChoice) {
                    		case 1: {
                        		add_record(questions, &num_questions);
                        		break;
                    		}
                    		case 2: {
								edit_record(questions, &num_questions);
                                 break;
							}
                    		case 3: {
                        		delete_record(questions, &num_questions);
                        		break;
                    		}
                    		case 0: {
                        		printf("\nGoing back to main menu.\n");
                        		adminAccess = 0;
                        		break;
                    		}
                    		default: {
                        		printf("Error: Invalid Input\n");
                        		fflush(stdin);
                        		dataChoice = 0;
                        		break;
                    		}
                		}
            		}
            		adminAccess=1;
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
                // play_game()
                break;
            }
            case 0: {
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
	Question questions[10];
    int num_questions = 0;
    char question[150];
    
    main_menu(questions, num_questions, question);
    
    return 0;
}
