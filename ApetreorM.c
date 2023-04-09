/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
LEE JACOB MARCUS A. APETREOR, DLSU ID #12274410
*********************************************************************************************************/

// -------------------
// ----- HEADERS -----
// -------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// -------------------
// ----- STRUCTS -----
// -------------------

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

// -------------------------------
// ----- FUNCTION PROTOTYPES -----
// -------------------------------

int find_question(Question *questions, int num_questions, char *question);
void add_record(Question *questions, int *num_questions);
void edit_record(Question *questions, int *num_questions);
void delete_record(Question *questions, int *num_questions);
void import_data(Question *questions, int *num_questions);
void export_data(Question *questions, int *num_questions);
void load_scores(PlayerScore *scores, int *num_scores);
void save_scores(PlayerScore *scores, int num_scores);
void add_score(PlayerScore *scores, int *num_scores, char *name, int score);
void display_scores(PlayerScore *scores, int *num_scores);
void play_game(Question *questions, int num_questions, PlayerScore *scores, int *num_scores);
void admin_menu(Question *questions, int *num_questions);
void game_menu(Question *questions, int num_questions, PlayerScore *scores, int *num_scores);
void main_menu(Question *questions, int num_questions, char *question, PlayerScore *scores, int *num_scores);


// --------------------------------------------
// ----- ADMIN RECORD MANAGEMENT FUNCTIONS-----
// --------------------------------------------

/* find_question returns t, which is either i or -1. it returns -1 if there are no same questions
	@param *questions is used to refer to the array questions[]
	@param *question is used to refer to the string to compare to see if it exists in the array
	@param num_questions is used to refer to the maximum amount of questions
	@return -1 if there are no similar questions found in the array when compared with param *question
	pre-condition: question can only be 150 characters long
*/
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

/* add_record is used to add a unique record based on the question to the array questions[]
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	@return void
	pre-condition: needs to be a unique question to add to the array
*/
void add_record(Question *questions, int *num_questions)
{
    char question[151];
    char correct_choice[31];
    char choice1[31];
    char choice2[31];
    char choice3[31];
    char topic[21]; 
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
        printf("Question number: %d\n", questions[index].question_number);
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

		// Find the last question in the topic
		int question_number = 0;
		int i;
		for (i = 0; i < *num_questions; i++) {
			if (strcmp(questions[i].topic, topic) == 0 && questions[i].question_number > question_number) {
				question_number = questions[i].question_number;
			}
		}

		printf("Enter choice 1: ");
		// Use %s to accept one word only
		scanf("%s", choice1);

		printf("Enter choice 2: ");
		scanf("%s", choice2);

		printf("Enter choice 3: ");
		scanf("%s", choice3);

		printf("Enter correct choice: ");
		scanf("%s", correct_choice);

		// Add the record to the collection
		Question new_question;
		strcpy(new_question.topic, topic);
		new_question.question_number = question_number + 1; // Increment the question number for this topic
		strcpy(new_question.question, question);
		strcpy(new_question.choices[0], choice1);
		strcpy(new_question.choices[1], choice2);
		strcpy(new_question.choices[2], choice3);
		strcpy(new_question.correct_choice, correct_choice);

		// Index is (*num_questions) since arrays are 0-indexed
		questions[*num_questions] = new_question;
		(*num_questions)++;
		printf("Record added successfully!\n");
    }
}

/* edit_record is used to edit already existing records, user needs to choose a topic, then a question inside that topic
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	pre-condition: needs to be an already existing record to edit
*/
void edit_record(Question *questions, int *num_questions)
{
	int flag1 = 0;
    int choice = 0;
    int back = 0;
    int index;
    int error_checker = 0;
    int i, j;

    // loop to ask for input again if error
    while (!error_checker && !back){
        char topics[*num_questions][21];
        int num_topics = 0;
        for (i = 0; i < *num_questions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (!strcmp(topics[j], questions[i].topic)) {
                    is_duplicate = 1;
                    flag1 = 1;
                }
            }
            if (!is_duplicate) {
                strcpy(topics[num_topics], questions[i].topic);
                num_topics++;
            }
        }
        if (!flag1){
        printf("\nAvailable topics:\n");
        for (i = 0; i < num_topics; i++) {
            printf("%d. %s\n", i + 1, topics[i]);
        }
        printf("0. Go Back \n");

        // Ask for index of topic to edit
        printf("Enter the number of the topic to edit (0-%d): ", num_topics);
        scanf("%d", &index);

        // Validate the index
        if (index < 0 || index > num_topics) {
            printf("Error: Invalid Input\n");
        } else if (index == 0){
            error_checker = 1;
            back = 1;
        } else {
            index--;  // Decrement index to match array index
            error_checker = 1;

            // Display all questions from the selected topic
            if (!back){
            printf("\nList of questions from topic \"%s\":\n", topics[index]);
            int num_questions_from_topic = 0;
            for (i = 0; i < *num_questions; i++) {
                if (!strcmp(questions[i].topic, topics[index])) {
                    printf("%d. %s\n", num_questions_from_topic + 1, questions[i].question);
                    num_questions_from_topic++;
                }
            }
            printf("0. Go Back\n");

            // Ask for index of question to edit
            printf("Enter the number of the question to edit (0-%d): ", num_questions_from_topic);
            scanf("%d", &index);

            // Validate the index
            if (index < 0 || index > num_questions_from_topic) {
                printf("Error: Invalid Input\n");
                error_checker = 0;
            } else if (index == 0){
                back = 1;
            } else {
                index--;  // Decrement index to match array index
            }
        	}    
        }
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

/* delete_record makes the user choose a topic then an existing question inside that topic to delete
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	pre-condition: needs to be an already existing record to delete
*/
void delete_record(Question *questions, int *num_questions) 
{
	int flag1 = 0;
    int i, j;
    int topic_index, question_index;
    int back = 0;
    int error_checker = 0;

    // Create an array of unique topics
    char topics[*num_questions][21];
    int num_topics = 0;
    int found = 0;
	for (i = 0; i < *num_questions && !found; i++) {
    	int is_duplicate = 0;
    	for (j = 0; j < num_topics && !found; j++) {
        	if (strcmp(topics[j], questions[i].topic) == 0) {
            	is_duplicate = 1;
            	found = 1;
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
    }

    // Prompt the user to choose a topic
    while (!error_checker){
        printf("Enter the number of the topic to delete a question from (type '0' to go back): ");
        scanf("%d", &topic_index);
        if (topic_index < 0 || topic_index > num_topics) {
            printf("Error: Invalid Input\n");
            getchar();
        } else if (topic_index == 0) {
            back = 1;
            error_checker = 1;
        } else {
            error_checker = 1;
        }
    }

    if (!back) {
        // Display questions associated with the chosen topic
        printf("Questions in topic %s:\n", topics[topic_index - 1]);
        int num_questions_in_topic = 0;
        for (i = 0; i < *num_questions; i++) {
            if (strcmp(questions[i].topic, topics[topic_index - 1]) == 0) {
                num_questions_in_topic++;
                printf("%d. %s\n", num_questions_in_topic, questions[i].question);
            }
        }

        // Prompt the user to choose a question
        error_checker = 0;
        while (!error_checker) {
            printf("Enter the number of the question to delete (type '0' to go back): ");
            scanf("%d", &question_index);
            if (question_index < 0 || question_index > num_questions_in_topic) {
                printf("Error: Invalid Input\n");
                getchar();
            } else if (question_index == 0) {
                back = 1;
                error_checker = 1;
            } else {
                error_checker = 1;
            }
        }

        if (!back) {
            // Find the index of the selected question in the original array
            int original_index = 0;
            for (i = 0; i < *num_questions; i++) {
                if (strcmp(questions[i].topic, topics[topic_index - 1]) == 0) {
                    original_index++;
                }
                if (original_index == question_index) {
                    flag1 = 1;
                }
            }
            
            if (!flag1){
			// Shift all the elements after the deleted element to fill the gap
        	for (i = original_index; i < *num_questions - 1; i++) {
        	    questions[i] = questions[i + 1];
        	}
        	(*num_questions)--;
        	printf("The selected question has been deleted.\n");
    	} else {
        	printf("Returning to main menu...\n");
    	}
	} else {
    printf("Returning to main menu...\n");
	}
	}
}
            
/* import_data imports information from .txt files and turns it into a record that is stored into the array
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	pre-condition: text in the file needs to be in a specific format to read
*/
void import_data(Question *questions, int *num_questions) 
{
    char filename[31];
    FILE *fp;
    int error_checker = 0;
    int question_found = 0;

    // Ask for filename
    printf("Enter the filename to load: ");
    scanf("%s", filename);

    // Try to open the file
    fp = fopen(filename, "r");

    // If file not found, display message and ask again
    while (fp == NULL) {
        printf("Error: File not found.\n");
        printf("Enter the filename to load (type '0' to go back): ");
        scanf("%s", filename);
        if (strcmp(filename, "0") == 0) {
            error_checker = 1;
        }
        if (!error_checker) {
            fp = fopen(filename, "r");
        }
    }
	
    // Read file contents and store in the array of questions
    char topic[21];
    int question_number;
    char question[151];
    char choices[3][31];
    char correct_choice[31];

    if (!error_checker) {
	        while (fscanf(fp, "%s\n%d\n%[^\n]\n%s\n%s\n%s\n%s\n\n", topic, &question_number, question, choices[0], choices[1], choices[2], correct_choice) != EOF) {
            // Check if question already exists in the array
            if (find_question(questions, *num_questions, question) != -1) {
                printf("Question '%s' already exists, skipping...\n", question);
                question_found = 1;
            }
			
			// if question_found is true, skips adding the question to the array
			if (!question_found){
            // Add new question to the array
            Question new_question;
            strcpy(new_question.topic, topic);
            new_question.question_number = question_number;
            strcpy(new_question.question, question);
            strcpy(new_question.choices[0], choices[0]);
            strcpy(new_question.choices[1], choices[1]);
            strcpy(new_question.choices[2], choices[2]);
            strcpy(new_question.correct_choice, correct_choice);

            questions[*num_questions] = new_question;
            (*num_questions)++;
        	}
        	
        	question_found = 0;
        }

        // Close the file
        fclose(fp);

        printf("Data imported successfully!\n");
    }
}
/* export_data exports the existing records on a .txt file in a specific format that import_data can read
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	pre-condition: needs to have already existing records
*/
void export_data(Question *questions, int *num_questions) 
{
    char filename[31];
    FILE *fp;
    int error_checker = 0;

    // Ask for filename
    printf("Enter the filename to save: ");
    scanf("%s", filename);

    // Try to open the file
    fp = fopen(filename, "w");

    // If file cannot be found, display error message and skip rest of the function
    if (fp == NULL) {
        printf("Error: File cannot be found.\n");
        error_checker = 1;
    }

    // Write contents of array of questions to file
    int i;
    if (!error_checker){
    for (i = 1; i < *num_questions; i++) {
        fprintf(fp, "%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", questions[i].topic, questions[i].question_number, questions[i].question, questions[i].choices[0], questions[i].choices[1], questions[i].choices[2], questions[i].correct_choice);
    }

    // Close the file
    fclose(fp);

    printf("Data exported successfully!\n");
	}
}


// --------------------------------
// ----- GAME/SCORE FUNCTIONS -----
// --------------------------------

/* load_scores reads the information provided in the .txt file scores.txt
	@param *scores is used to refer to the array scores[]
	@param *num_scores is used to refer to the maximum ammount of scores
	pre-condition: scores.txt needs to exist
*/
void load_scores(PlayerScore *scores, int *num_scores) 
{
	int flag1 = 0;
	int flag2 = 0;
	// use static int so it doesnt keep multiplying its score when called in display_scores
    static int loaded = 0;
    if (loaded) {
        flag1 = 1;
    }

    int i = 0;
    if (!flag1){
    FILE *fp = fopen("scores.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file for reading scores!\n");
        flag2 = 1;
    }
    if (!flag2){
    while (fscanf(fp, "%s %d", scores[i].name, &scores[i].score) != EOF) {
        i++;
    }
    *num_scores = i;
    fclose(fp);
	
    loaded = 1;
	}
	}
}

/* save_scores saves the scores and updates the .txt file scores.txt
	@param *scores is used to refer to the array scores[]
	@param num_scores is used to refer to the maximum ammount of scores
	pre-condition: scores.txt needs to exist
*/
void save_scores(PlayerScore *scores, int num_scores) 
{
	int flag1 = 0;
	int flag2 = 0;
    int i, j;
    int name_exists = 0;
    FILE *fp = fopen("scores.txt", "w");
    if (fp == NULL) {
        printf("Unable to open file for saving scores!\n");
        flag1 = 1;
    }
    if (!flag1){
    for (i = 0; i < num_scores; i++) {
        name_exists = 0;
        for (j = 0; j < num_scores; j++) {
            if (i != j && strcmp(scores[i].name, scores[j].name) == 0) {
                name_exists = 1;
                if (scores[i].score > scores[j].score) {
                    scores[j].score = scores[i].score;
                }
                flag2 = 1;
            }
        }
        if (!name_exists&&!flag2) {
            fprintf(fp, "%s\n%d\n\n", scores[i].name, scores[i].score);
        }
    }
	}
    fclose(fp);
}

/* add_score is used to add names and their corresponding scores to the array, and update the score if the name already exists
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	@param *name is used to compare to scores[].name to see if there is an existing name
	@param score is integer used to add onto the player's existing score
	pre-condition: max ammount of scores is 50
*/
void add_score(PlayerScore *scores, int *num_scores, char *name, int score) {
	int flag1 = 0;
	int flag2 = 0;
    if (*num_scores == 50) {
        printf("Unable to add score - maximum number of scores reached!\n");
        flag1 = 1;
    }

    int i;
    if (!flag1){
    for (i = 0; i < *num_scores; i++) {
        if (strcmp(scores[i].name, name) == 0) {
            scores[i].score += score;
            flag2 = 1;
        }
    }
	
	if (!flag2){
    PlayerScore new_score;
    strncpy(new_score.name, name, 21);
    new_score.score = score;
    scores[*num_scores] = new_score;
    (*num_scores)++;
	}
	}
}

/* display_scores is used to display the already existing scores using a bubble sort algorithm to sort from highest score to lowest score
	@param *scores is used to refer to the array scores[]
	@param *num_scores is used to refer to the maximum ammount of scores
	pre-condition: load_scores needs to be static when called
*/
void display_scores(PlayerScore *scores, int *num_scores)
{
    load_scores(scores, num_scores);
    int i, j;
    PlayerScore temp;
    // bubble sort
    for (i = 0; i < *num_scores - 1; i++) {
        for (j = 0; j < *num_scores - i - 1; j++) {
            if (scores[j].score < scores[j+1].score) {
                temp = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp;
            }
        }
    }
    printf("Top Scores:\n");
    printf("-----------\n");
    for (i = 0; i < *num_scores; i++) {
        printf("%d. %s - %d\n", i+1, scores[i].name, scores[i].score);
    }
}

/* play_game is used to provide the UI of the game itself that the use can play
	@param *questions is used to refer to the array questions[]
	@param num_questions is used to refer to the maximum amount of questions
	@param *scores is used to refer to the array scores[]
	@param *num_scores is used to refer to the maximum amount of scores
	pre-condition: all of the integer parameters have to be initialized
*/
void play_game(Question *questions, int num_questions, PlayerScore *scores, int *num_scores) {
    int flag1 = 0;
    int flag2 = 0;
    char name[21];
    int i, j;
    printf("Enter your name: ");
    scanf("%s", name);

    int score = 0;
    while (1&&!flag2) {
        // Reset flags
        flag1 = 0;

        // Create an array of unique topics
        char topics[num_questions][21];
        int num_topics = 0;
        for (i = 0; i < num_questions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (strcmp(topics[j], questions[i].topic) == 0) {
                    is_duplicate = 1;
                    flag1 = 1;
                }
            }
            if (!is_duplicate && !flag1) {
                strcpy(topics[num_topics], questions[i].topic);
                num_topics++;
            }
        }
		
        // Display topics and their associated questions
        if (!flag1){
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
            printf("0. End game\n");

            int choice;
            printf("\nEnter your choice: ");
            scanf("%1d%*c", &choice);

            if (choice == 0) {
                printf("\n%s, your final score is %d.\n", name, score);
                add_score(scores, num_scores, name, score);
                flag2 = 1;
            } else if (choice < 1 || choice > num_topics) {
                printf("\nInvalid choice. Please try again.\n");
            } else {
                int count = 0;
                for (i = 0; i < num_questions; i++) {
                    if (strcmp(questions[i].topic, topics[choice - 1]) == 0) {
                        count++;
                    }
                }

                if (count == 0) {
                    printf("\nNo questions available for this topic. Please choose another topic.\n");
                } else {
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
        			scanf("%s", answer);

       				if (strcmp(answer, questions[i].correct_choice) == 0) {
        			    printf("Correct! You earned 1 point.\n");
        			    score++;
        			} else {
            			printf("Sorry, the correct answer is: %s\n", questions[i].correct_choice);
        			}
    			}
    		}
    	}
    }
}

// --------------------------
// ----- MENU FUNCTIONS -----
// --------------------------

/* admin_menu is used to display the menu where users with admin access can modify and manipulate the records
	@param *questions is used to refer to the array questions[]
	@param *num_questions is used to refer to the maximum amount of questions
	pre-condition: num_questions has to be initialized
*/
void admin_menu(Question *questions, int *num_questions) 
{
    int choice = 0;
    int adminAccess = 1;

    while (adminAccess == 1) {
        printf("\n--- ADMIN MENU ---:\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. Import Data\n");
        printf("5. Export Data\n");
        printf("0. Sign Out\n");
        printf("\nEnter your choice: ");
        scanf("%1d%*c", &choice);
        
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
            case 4: {
                import_data(questions, num_questions);
                break;
            }
            case 5: {
                export_data(questions, num_questions);
                break;
            }
            case 0: {
                printf("\nExiting admin menu...\n");
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
/* game_menu is used to display the game menu where users may play the game and view their scores
	@param *questions is used to refer to the array questions[]
	@param num_questions is used to refer to the maximum amount of questions
	@param *scores is used to refer to the array scores[]
	@param *num_scores is used to refer to the maximum amount of scores
	pre-condition: integer parameters need to be initialized
*/
void game_menu(Question *questions, int num_questions, PlayerScore *scores, int *num_scores) 
{
    int choice;
    do {
        printf("\n--- GAME MENU ---\n");
        printf("1. Play\n");
        printf("2. View Scores\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%1d%*c", &choice);
        switch (choice) {
            case 1:
                play_game(questions, num_questions, scores, num_scores);
                break;
            case 2:
                display_scores(scores, num_scores);
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

/* main_menu is used to display the main menu where users may either access the admin menu or the game menu
	@param *questions is used to refer to the array questions[]
	@param num_questions is used to refer to the maximum amount of questions
	@param *question is used to refer to the string question[]
	@param *scores is used to refer to the array scores[]
	@param *num_scores is used to refer to the maximum amount of scores
	pre-condition: integer parameters need to be initialized
*/
void main_menu(Question *questions, int num_questions, char *question, PlayerScore *scores, int *num_scores) 
{
    int choice = -1;
    int back = 0;
    while (!back) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Manage Data [Admin]\n");
        printf("2. Game Menu\n");
        printf("0. Exit Program\n");
        printf("\nEnter your choice: ");
		scanf("%1d%*c", &choice);
        switch (choice) {
			case 1: {
 		    	int back = 0;
  		 		while (!back) {
        			char password[21];
        			int i = 0;
        			printf("Enter password (press 0 to go back): ");
        				int enter = 0;
        				while (!enter) {
            			char c = getch();
            			if (c == '\r') {  // Enter key
                			password[i] = '\0';  // Add null terminator to end string
                			enter = 1;
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
                printf("Exiting program...\n");
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

/* main() is used to initialize values and array/string sizes, return 0 and exits program when player exits main menu
*/
int main() {
	Question questions[11];
    int num_questions = 0;
    char question[151];
    PlayerScore scores[11];
    int num_scores = 0;
    
    main_menu(questions, num_questions, question, scores, &num_scores);
    
    return 0;
}
