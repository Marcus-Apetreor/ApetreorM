#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char topic[21];
    int question_number;
    char question[151];
    char choices[3][31];
    char correct_choice[31];
} Question;

typedef struct {
    char name[21];
    int score;
} PlayerScore;

// --------------------------------------------
// ----- ADMIN RECORD MANAGEMENT FUNCTIONS-----
// --------------------------------------------

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
    char question[151];
    char correct_choice[31];
    char choice1[31];
    char choice2[31];
    char choice3[31];
    char topic[21];
    int error_checker = 0;
    int back = 0;

    // Ask for question and answer
    printf("Enter the question: ");
    scanf("%[^\n]", question);

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
        back = 1;
    }

    // If statement to skip rest of the function
    if (!back){
        
        // Ask for topic and choices
        printf("Enter the topic: ");
        // Use %s to accept one word only
        scanf("%s", topic);
        
        printf("Enter choice 1: ");
        // Use %s to accept one word only
        scanf("%s", choice1);

        printf("Enter choice 2: ");
        scanf("%s", choice2);
        
        printf("Enter choice 3: ");
        scanf("%s", choice3);
        
        // loop to ask for input again if error
        while(!error_checker){
            printf("Enter correct choice: (1-3)");
            // Use %s to accept one word only
            scanf("%s", correct_choice);
            if (*correct_choice<'1'||*correct_choice>'3'){
                printf("Error: Invalid Input\n");
            } else {
                error_checker=1;
            } 
        }
        // Add the record to the collection
        Question new_question;
        strcpy(new_question.topic, topic);
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
    int back = 0;
    int index;
    int error_checker = 0;
    int i, j;

    // loop to ask for input again if error
    while (!error_checker){

        char topics[*num_questions][21];
        int num_topics = 0;
        for (i = 0; i < *num_questions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (strcmp(topics[j], questions[i].topic) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate) {
                strcpy(topics[num_topics], questions[i].topic);
                num_topics++;
            }
        }
        printf("\nAvailable topics:\n");
        for (i = 0; i < num_topics; i++) {
            printf("%d. %s\n", i + 1, topics[i]);
        }
        printf("0. Go Back \n");

        // Ask for index of topic to edit
        printf("Enter the number of the topic to edit (1-%d): ", num_topics);
        scanf("%1d", &index);

        // Validate the index
        if (index < 0 || index > num_topics) {
            printf("Error: Invalid Input\n");
        } else if (index == 0){
            error_checker = 1;
            back = 1;
        } else {
            index--;  // Decrement index to match array index
            error_checker = 1;
        }

        printf("List of questions: \n");
        for (i = 0; i < *num_questions; i++) {
            printf("%d. %s\n", i + 1, questions[i].question);
        }
        printf("0. Go Back \n");

        // Ask for index of question to edit
        printf("Enter the number of the question to edit (1-%d): ", *num_questions);
        scanf("%1d", &index);

        // Validate the index
        if (index < 0 || index > *num_questions) {
            printf("Error: Invalid Input\n");
        } else if (index == 0){
            error_checker = 1;
            back = 1;
        } else {
            index--;  // Decrement index to match array index
            error_checker = 1;
        }
    }

    // Prompt for new information
    char new_question[151];
    char new_choice1[31];
    char new_choice2[31];
    char new_choice3[31];
    char new_topic[21];
    char new_correct_choice[31];
	
	while (!back){
		printf("\n--- EDIT MENU ---\n");
		printf("1. Edit Question \n");
		printf("2. Edit Topic \n");
		printf("3. Edit Choice 1 \n");
		printf("4. Edit Choice 2 \n");
		printf("5. Edit Choice 3 \n");
		printf("6. Edit Correct Choice \n");
		printf("0. Go Back \n");
		printf("\nEnter your choice: ");
		scanf("%1d", &choice);
		getchar();// consume newline character
		switch (choice){
			case 1: {
    			printf("Enter the new question: ");
    			// %[^\n] to read multiple words
    			scanf("%[^\n]", new_question);
    			strcpy(questions[index].question, new_question);
    			printf("Record updated successfully!\n");
    			break;
    		}
			case 2: {
    			printf("Enter the new topic: ");
    			// %s to only read one word
    			scanf("%s", new_topic);
    			strcpy(questions[index].topic, new_topic);
    			printf("Record updated successfully!\n");
				break;
			}
			case 3: {
    			printf("Enter the new choice 1: ");
    			scanf("%s", new_choice1);
    			strcpy(questions[index].choices[0], new_choice1);
    			printf("Record updated successfully!\n");
				break;
			}
			case 4: {
    			printf("Enter the new choice 2: ");
    			scanf("%s", new_choice2);
    			strcpy(questions[index].choices[1], new_choice2);
    			printf("Record updated successfully!\n");
			break;
			}
			case 5: {
    			printf("Enter the new choice 3: ");
    			scanf("%s", new_choice3);
    			strcpy(questions[index].choices[2], new_choice3);
    			printf("Record updated successfully!\n");
    		break;
    		}
			case 6: {
				printf("Enter the new correct choice: ");
    			scanf("%s", new_correct_choice);
    			strcpy(questions[index].correct_choice, new_correct_choice);
    			printf("Record updated successfully!\n");
    		break;
    		}
			case 0: {
				printf("Exiting edit menu");
				back = 1;
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
    int index;
	int i;
	int back = 0;
	int error_checker = 0;
	
	while (!error_checker){
    	printf("List of questions: \n");
    	for (i = 0; i < *num_questions; i++) {
    	    printf("%d. %s\n", i + 1, questions[i].question);
    	}
    	printf("0. Go Back \n");
    
    	printf("Enter the number of the question to delete: ");
    	scanf("%1d", &index);
    	if (index < 0 || index > *num_questions) {
    	    printf("Error: Invalid Input\n");
    	    getchar(); 
    	} else if (index == 0) {
    		back = 1;
    		error_checker = 1;
		} else {
		error_checker = 1;
		}
	}
	
	if (!back){
    	// Shift all the elements after the deleted element to fill the gap
    	for (i = index - 1; i < *num_questions - 1; i++) {
    	    questions[i] = questions[i+1];
    	}
    	(*num_questions)--;  // Decrement the number of questions
    	printf("Record deleted successfully.\n");
	}
}

// --------------------------------
// ----- GAME/SCORE FUNCTIONS -----
// --------------------------------

void load_scores(PlayerScore *scores, int *num_scores) {
	int i;
    FILE *fp = fopen("scores.txt", "r");
    if (fp == NULL) {
        *num_scores = 0;
        return;
    }
    
    fscanf(fp, "%d", num_scores);
    for (i = 0; i < *num_scores; i++) {
        fscanf(fp, "%s %d", scores[i].name, &scores[i].score);
    }

    fclose(fp);
}

void save_scores(PlayerScore *scores, int num_scores) {
    int i;
    FILE *fp = fopen("scores.txt", "a");
    if (fp == NULL) {
        printf("Unable to open file for saving scores!\n");
        return;
    }

    for (i = 0; i < num_scores; i++) {
        fprintf(fp, "%s\n%d\n\n", scores[i].name, scores[i].score);
    }

    fclose(fp);
}

void add_score(PlayerScore *scores, int *num_scores, char *name, int score) {
    if (*num_scores == 50) {
        printf("Unable to add score - maximum number of scores reached!\n");
        return;
    }

    PlayerScore new_score;
    strncpy(new_score.name, name, 21);
    new_score.score = score;
    scores[*num_scores] = new_score;
    (*num_scores)++;
}

void display_scores(PlayerScore *scores, int num_scores) {
	int i;
    printf("Top Scores:\n");
    printf("-----------\n");
    for (i = 0; i < num_scores; i++) {
        printf("%d. %s - %d\n", i+1, scores[i].name, scores[i].score);
    }
}

void play_game(Question *questions, int num_questions, PlayerScore *scores, int *num_scores) {
    char name[21];
    int i, j;
    printf("Enter your name: ");
    scanf("%s", name);

    int score = 0;
    while (1) {
        // Create an array of unique topics
        char topics[num_questions][21];
        int num_topics = 0;
        for (i = 0; i < num_questions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (strcmp(topics[j], questions[i].topic) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate) {
                strcpy(topics[num_topics], questions[i].topic);
                num_topics++;
            }
        }

        // Display topics and their associated questions
        printf("\nAvailable topics:\n");
        for (i = 0; i < num_topics; i++) {
            printf("%d. %s\n", i + 1, topics[i]);
            printf("   Questions:\n");
            for (j = 0; j < num_questions; j++) {
                if (strcmp(questions[j].topic, topics[i]) == 0) {
                    printf("   - %s\n", questions[j].question);
                }
            }
        }
        printf("%d. End game\n", num_topics + 1);

        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == num_topics + 1) {
            printf("\n%s, your final score is %d.\n", name, score);
            add_score(scores, num_scores, name, score);
            return;
        }

        if (choice < 1 || choice > num_topics) {
            printf("\nInvalid choice. Please try again.\n");
            continue;
        }

        int count = 0;
        for (i = 0; i < num_questions; i++) {
            if (strcmp(questions[i].topic, topics[choice - 1]) == 0) {
                count++;
            }
        }

        if (count == 0) {
            printf("\nNo questions available for this topic. Please choose another topic.\n");
            continue;
        }

        int index = rand() % count + 1;
        i = 0;
        while (index > 0) {
            if (strcmp(questions[i].topic, topics[choice - 1]) == 0) {
                index--;
            }
            i++;
        }
        i--;
		
		printf("\n%s\n", questions[i].topic);
        printf("Q. %s\n", questions[i].question);
        printf("1. %s\n", questions[i].choices[0]);
        printf("2. %s\n", questions[i].choices[1]);
        printf("3. %s\n", questions[i].choices[2]);
        printf("\nType your answer: ");
        char answer[31];
        fgets(answer, 31, stdin);
        answer[strcspn(answer, "\n")] = '\0'; // remove trailing newline character

        if (strcmp(answer, questions[i].correct_choice) == 0) {
            printf("Correct! You earned 1 point.\n");
            score++;
        } else {
            printf("Sorry, the correct answer is: %s\n", questions[i].correct_choice);
        }
    }
}

// --------------------------
// ----- MENU FUNCTIONS -----
// --------------------------

void admin_menu(Question *questions, int *num_questions) {
    int choice = 0;
    int adminAccess = 1;

    while (adminAccess == 1) {
        printf("\n--- ADMIN MENU ---:\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("0. Sign Out\n");
        printf("\nEnter your choice: ");
        scanf("%1d", &choice);
        
        switch (choice) {
            case 1: {
                add_record(questions, num_questions);
                break;
            }
            case 2: {
                edit_record(questions, num_questions);
                break;
            }
            case 3: {
                delete_record(questions, num_questions);
                break;
            }
            case 0: {
                printf("\nGoing back to main menu.\n");
                adminAccess = 0;
                break;
            }
            default: {
                printf("Error: Invalid Input\n");
                break;
            }
        }
    }
}

void game_menu(Question *questions, int num_questions, PlayerScore *scores, int *num_scores) {
    int choice;
    do {
        printf("\n--- GAME MENU ---\n");
        printf("1. Play\n");
        printf("2. View Scores\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%1d", &choice);
        switch (choice) {
            case 1:
                play_game(questions, num_questions, scores, num_scores);
                break;
            case 2:
                display_scores(scores, *num_scores);
                break;
            case 0:
                save_scores(scores, *num_scores); // save scores before exiting
                printf("\nExiting game menu...\n");
                break;
            default:
                printf("\nError: Invalid Input\n");
                break;
        }
    } while (choice != 0);
}


void main_menu(Question *questions, int num_questions, char *question, PlayerScore *scores, int *num_scores) {
    int choice = -1;
    int back = 0;
    while (!back) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Manage Data [Admin]\n");
        printf("2. Game Menu\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
		scanf("%1d", &choice);
        switch (choice) {
			case 1: {
 		    	int back = 0;
  		 		while (!back) {
        			char password[21];
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
                        admin_menu(questions, &num_questions);
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
    			printf("Proceeding to Game Menu.\n");
    			game_menu(questions, num_questions, scores, num_scores);
    			break;
			}
            case 0: {
                printf("Exiting program.\n");
                back = 1;
                break;
            }
            default: {
    			printf("Error: Invalid Input\n");
    			getchar();// consume newline character
    			break;
			}
        }
    }
}

int main() {
	Question questions[11];
    int num_questions = 0;
    char question[151];
    PlayerScore scores[11];
    int num_scores = 0;
    
    main_menu(questions, num_questions, question, scores, &num_scores);
    
    return 0;
}
