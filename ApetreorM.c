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
    char strTopic[21]; 
    int nQuestion; 
    char strQuestion[151]; 
    char strChoices[3][31]; 
    char strAnswer[31]; 
} Question;

typedef struct {
    char strName[21];
    int nScore;
} PlayerScore;

// -------------------------------
// ----- FUNCTION PROTOTYPES -----
// -------------------------------

int find_question(Question *arrQuestions, int nQuestions, char *strQuestion);
void add_record(Question *arrQuestions, int *nQuestions);
void edit_record(Question *arrQuestions, int *nQuestions);
void delete_record(Question *arrQuestions, int *nQuestions);
void import_data(Question *arrQuestions, int *nQuestions);
void export_data(Question *arrQuestions, int *nQuestions);
void load_scores(PlayerScore *arrScores, int *nScores);
void save_scores(PlayerScore *arrScores, int nScores);
void add_score(PlayerScore *arrScores, int *nScores, char *strName, int nScore);
void display_scores(PlayerScore *arrScores, int *nScores);
void play_game(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores);
void admin_menu(Question *arrQuestions, int *nQuestions);
void game_menu(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores);
void main_menu(Question *arrQuestions, int nQuestions, char *strQuestion, PlayerScore *arrScores, int *nScores);


// --------------------------------------------
// ----- ADMIN RECORD MANAGEMENT FUNCTIONS-----
// --------------------------------------------

/* find_question returns t, which is either i or -1. it returns -1 if there are no same arrQuestions
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *strQuestion is used to refer to the string to compare to see if it exists in the array
	@param nQuestions is used to refer to the maximum amount of arrQuestions
	@return -1 if there are no similar arrQuestions found in the array when compared with param *strQuestion
	pre-condition: strQuestion can only be 150 characters long
*/
int find_question(Question *arrQuestions, int nQuestions, char *strQuestion)
{
	int i, t=-1;
	// Searches for arrQuestions that have same strName as input
    for (i = 0; i < nQuestions; i++) {
        if (strcmp(arrQuestions[i].strQuestion, strQuestion) == 0) {
            t=i;
        }
    }
    // Returns -1 if there are no same arrQuestions
    return t;
}

/* add_record is used to add a unique record based on the strQuestion to the array arrQuestions[]
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	@return void
	pre-condition: needs to be a unique strQuestion to add to the array
*/
void add_record(Question *arrQuestions, int *nQuestions)
{
    char strQuestion[151];
    char strAnswer[31];
    char strChoice1[31];
    char strChoice2[31];
    char strChoice3[31];
    char strTopic[21]; 
    int back = 0;

    // Ask for strQuestion and answer
    printf("Enter the question: ");
    scanf("%[^\n]", strQuestion);

    // Check if strQuestion already exists
    int index = find_question(arrQuestions, *nQuestions, strQuestion);
    // if same strQuestion found
    if (index != -1) {
        printf("The question already exists:\n");
        printf("Topic: %s\n", arrQuestions[index].strTopic);
        printf("Question number: %d\n", arrQuestions[index].nQuestion);
        printf("Question: %s\n", arrQuestions[index].strQuestion);
        printf("Choice 1: %s\n", arrQuestions[index].strChoices[0]);
        printf("Choice 2: %s\n", arrQuestions[index].strChoices[1]);
        printf("Choice 3: %s\n", arrQuestions[index].strChoices[2]);
        printf("Correct choice: %s\n", arrQuestions[index].strAnswer);
        // function = 0; to skip the rest of the function
        back = 1;
    }

    // If statement to skip rest of the function
    if (!back){
        
        // Ask for strTopic and strChoices
		printf("Enter the topic: ");
		// Use %s to accept one word only
		scanf("%s", strTopic);

		// Find the last strQuestion in the strTopic
		int nQuestion = 0;
		int i;
		for (i = 0; i < *nQuestions; i++) {
			if (strcmp(arrQuestions[i].strTopic, strTopic) == 0 && arrQuestions[i].nQuestion > nQuestion) {
				nQuestion = arrQuestions[i].nQuestion;
			}
		}

		printf("Enter choice 1: ");
		// Use %s to accept one word only
		scanf("%s", strChoice1);

		printf("Enter choice 2: ");
		scanf("%s", strChoice2);

		printf("Enter choice 3: ");
		scanf("%s", strChoice3);

		printf("Enter correct choice: ");
		scanf("%s", strAnswer);

		// Add the record to the collection
		Question new_question;
		strcpy(new_question.strTopic, strTopic);
		new_question.nQuestion = nQuestion + 1; // Increment the strQuestion number for this strTopic
		strcpy(new_question.strQuestion, strQuestion);
		strcpy(new_question.strChoices[0], strChoice1);
		strcpy(new_question.strChoices[1], strChoice2);
		strcpy(new_question.strChoices[2], strChoice3);
		strcpy(new_question.strAnswer, strAnswer);

		// Index is (*nQuestions) since arrays are 0-indexed
		arrQuestions[*nQuestions] = new_question;
		(*nQuestions)++;
		printf("Record added successfully!\n");
    }
}

/* edit_record is used to edit already existing records, user needs to choose a strTopic, then a strQuestion inside that strTopic
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	pre-condition: needs to be an already existing record to edit
*/
void edit_record(Question *arrQuestions, int *nQuestions)
{
	int flag1 = 0;
    int nChoice = 0;
    int back = 0;
    int index;
    int error_checker = 0;
    int i, j;

    // loop to ask for input again if error
    while (!error_checker && !back){
        char topics[*nQuestions][21];
        int num_topics = 0;
        for (i = 0; i < *nQuestions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (!strcmp(topics[j], arrQuestions[i].strTopic)) {
                    is_duplicate = 1;
                    flag1 = 1;
                }
            }
            if (!is_duplicate) {
                strcpy(topics[num_topics], arrQuestions[i].strTopic);
                num_topics++;
            }
        }
        if (!flag1){
        printf("\nAvailable topics:\n");
        for (i = 0; i < num_topics; i++) {
            printf("%d. %s\n", i + 1, topics[i]);
        }
        printf("0. Go Back \n");

        // Ask for index of strTopic to edit
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

            // Display all arrQuestions from the selected strTopic
            if (!back){
            printf("\nList of questions from topic \"%s\":\n", topics[index]);
            int num_questions_from_topic = 0;
            for (i = 0; i < *nQuestions; i++) {
                if (!strcmp(arrQuestions[i].strTopic, topics[index])) {
                    printf("%d. %s\n", num_questions_from_topic + 1, arrQuestions[i].strQuestion);
                    num_questions_from_topic++;
                }
            }
            printf("0. Go Back\n");

            // Ask for index of strQuestion to edit
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
		printf("\nEnter your nChoice: ");
		scanf("%1d", &nChoice);
		getchar();// consume newline character
		switch (nChoice){
			case 1: {
    			printf("Enter the new question: ");
    			// %[^\n] to read multiple words
    			scanf("%[^\n]", new_question);
    			strcpy(arrQuestions[index].strQuestion, new_question);
    			printf("Record updated successfully!\n");
    			break;
    		}
			case 2: {
    			printf("Enter the new topic: ");
    			// %s to only read one word
    			scanf("%s", new_topic);
    			strcpy(arrQuestions[index].strTopic, new_topic);
    			printf("Record updated successfully!\n");
				break;
			}
			case 3: {
    			printf("Enter the new choice 1: ");
    			scanf("%s", new_choice1);
    			strcpy(arrQuestions[index].strChoices[0], new_choice1);
    			printf("Record updated successfully!\n");
				break;
			}
			case 4: {
    			printf("Enter the new choice 2: ");
    			scanf("%s", new_choice2);
    			strcpy(arrQuestions[index].strChoices[1], new_choice2);
    			printf("Record updated successfully!\n");
				break;
			}
			case 5: {
    			printf("Enter the new choice 3: ");
    			scanf("%s", new_choice3);
    			strcpy(arrQuestions[index].strChoices[2], new_choice3);
    			printf("Record updated successfully!\n");
    			break;
    		}
			case 6: {
				printf("Enter the new correct choice: ");
    			scanf("%s", new_correct_choice);
    			strcpy(arrQuestions[index].strAnswer, new_correct_choice);
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
            	nChoice = 0;
				break;
			}
		}
	}
}

/* delete_record makes the user choose a strTopic then an existing strQuestion inside that strTopic to delete
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	pre-condition: needs to be an already existing record to delete
*/
void delete_record(Question *arrQuestions, int *nQuestions) 
{
	int flag1 = 0;
    int i, j;
    int topic_index, question_index;
    int back = 0;
    int error_checker = 0;

    // Create an array of unique topics
    char topics[*nQuestions][21];
    int num_topics = 0;
    int found = 0;
	for (i = 0; i < *nQuestions && !found; i++) {
    	int is_duplicate = 0;
    	for (j = 0; j < num_topics && !found; j++) {
        	if (strcmp(topics[j], arrQuestions[i].strTopic) == 0) {
            	is_duplicate = 1;
            	found = 1;
        	}
    	}
    	if (!is_duplicate) {
        	strcpy(topics[num_topics], arrQuestions[i].strTopic);
        	num_topics++;
    	}
	}

    // Display topics and their associated arrQuestions
    printf("\nAvailable topics:\n");
    for (i = 0; i < num_topics; i++) {
        printf("%d. %s\n", i + 1, topics[i]);
    }

    // Prompt the user to choose a strTopic
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
        // Display arrQuestions associated with the chosen strTopic
        printf("Questions in topic %s:\n", topics[topic_index - 1]);
        int num_questions_in_topic = 0;
        for (i = 0; i < *nQuestions; i++) {
            if (strcmp(arrQuestions[i].strTopic, topics[topic_index - 1]) == 0) {
                num_questions_in_topic++;
                printf("%d. %s\n", num_questions_in_topic, arrQuestions[i].strQuestion);
            }
        }

        // Prompt the user to choose a strQuestion
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
            // Find the index of the selected strQuestion in the original array
            int original_index = 0;
            for (i = 0; i < *nQuestions; i++) {
                if (strcmp(arrQuestions[i].strTopic, topics[topic_index - 1]) == 0) {
                    original_index++;
                }
                if (original_index == question_index) {
                    flag1 = 1;
                }
            }
            
            if (!flag1){
			// Shift all the elements after the deleted element to fill the gap
        	for (i = original_index; i < *nQuestions - 1; i++) {
        	    arrQuestions[i] = arrQuestions[i + 1];
        	}
        	(*nQuestions)--;
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
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	pre-condition: text in the file needs to be in a specific format to read
*/
void import_data(Question *arrQuestions, int *nQuestions) 
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
	
    // Read file contents and store in the array of arrQuestions
    char strTopic[21];
    int nQuestion;
    char strQuestion[151];
    char strChoices[3][31];
    char strAnswer[31];

    if (!error_checker) {
	        while (fscanf(fp, "%s\n%d\n%[^\n]\n%s\n%s\n%s\n%s\n\n", strTopic, &nQuestion, strQuestion, strChoices[0], strChoices[1], strChoices[2], strAnswer) != EOF) {
            // Check if strQuestion already exists in the array
            if (find_question(arrQuestions, *nQuestions, strQuestion) != -1) {
                printf("Question '%s' already exists, skipping...\n", strQuestion);
                question_found = 1;
            }
			
			// if question_found is true, skips adding the strQuestion to the array
			if (!question_found){
            // Add new strQuestion to the array
            Question new_question;
            strcpy(new_question.strTopic, strTopic);
            new_question.nQuestion = nQuestion;
            strcpy(new_question.strQuestion, strQuestion);
            strcpy(new_question.strChoices[0], strChoices[0]);
            strcpy(new_question.strChoices[1], strChoices[1]);
            strcpy(new_question.strChoices[2], strChoices[2]);
            strcpy(new_question.strAnswer, strAnswer);

            arrQuestions[*nQuestions] = new_question;
            (*nQuestions)++;
        	}
        	
        	question_found = 0;
        }

        // Close the file
        fclose(fp);

        printf("Data imported successfully!\n");
    }
}
/* export_data exports the existing records on a .txt file in a specific format that import_data can read
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	pre-condition: needs to have already existing records
*/
void export_data(Question *arrQuestions, int *nQuestions) 
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

    // Write contents of array of arrQuestions to file
    int i;
    if (!error_checker){
    for (i = 1; i < *nQuestions; i++) {
        fprintf(fp, "%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", arrQuestions[i].strTopic, arrQuestions[i].nQuestion, arrQuestions[i].strQuestion, arrQuestions[i].strChoices[0], arrQuestions[i].strChoices[1], arrQuestions[i].strChoices[2], arrQuestions[i].strAnswer);
    }

    // Close the file
    fclose(fp);

    printf("Data exported successfully!\n");
	}
}


// --------------------------------
// ----- GAME/SCORE FUNCTIONS -----
// --------------------------------

/* load_scores reads the information provided in the .txt file arrScores.txt
	@param *arrScores is used to refer to the array arrScores[]
	@param *nScores is used to refer to the maximum ammount of arrScores
	pre-condition: arrScores.txt needs to exist
*/
void load_scores(PlayerScore *arrScores, int *nScores) 
{
    int flag1 = 0;
    int flag2 = 0;
    // Initialize loaded to 1 so that the file is only read once
    static int loaded = 1;
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
            while (fscanf(fp, "%s\n%d\n\n", arrScores[i].strName, &arrScores[i].nScore) != EOF) {
                i++;
            }
            *nScores = i;
            fclose(fp);

            loaded = 1;
        }
    }
}

/* save_scores saves the arrScores and updates the .txt file arrScores.txt
	@param *arrScores is used to refer to the array arrScores[]
	@param nScores is used to refer to the maximum ammount of arrScores
	pre-condition: arrScores.txt needs to exist
*/
void save_scores(PlayerScore *arrScores, int nScores) 
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
    for (i = 0; i < nScores; i++) {
        name_exists = 0;
        for (j = 0; j < nScores; j++) {
            if (i != j && strcmp(arrScores[i].strName, arrScores[j].strName) == 0) {
                name_exists = 1;
                if (arrScores[i].nScore > arrScores[j].nScore) {
                    arrScores[j].nScore = arrScores[i].nScore;
                }
                flag2 = 1;
            }
        }
        if (!name_exists&&!flag2) {
            fprintf(fp, "%s\n%d\n\n", arrScores[i].strName, arrScores[i].nScore);
        }
    }
	}
    fclose(fp);
}

/* add_score is used to add names and their corresponding arrScores to the array, and update the nScore if the strName already exists
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	@param *strName is used to compare to arrScores[].strName to see if there is an existing strName
	@param nScore is integer used to add onto the player's existing nScore
	pre-condition: max ammount of arrScores is 50
*/
void add_score(PlayerScore *arrScores, int *nScores, char *strName, int nAdd) {
    int flag1 = 0;
    int flag2 = 0;
    if (*nScores == 50) {
        printf("Unable to add score - maximum number of scores reached!\n");
        flag1 = 1;
    }

    int i;
    if (!flag1){
        for (i = 0; i < *nScores; i++) {
            if (strcmp(arrScores[i].strName, strName) == 0) {
                arrScores[i].nScore += nAdd;
                flag2 = 1;
            }
        }

        if (!flag2) {
            PlayerScore new_score;
            strncpy(new_score.strName, strName, 21);
            new_score.nScore = nAdd;
            arrScores[*nScores] = new_score;
            (*nScores)++;
        }
    }
}

/* display_scores is used to display the already existing arrScores using a bubble sort algorithm to sort from highest nScore to lowest nScore
	@param *arrScores is used to refer to the array arrScores[]
	@param *nScores is used to refer to the maximum ammount of arrScores
	pre-condition: load_scores needs to be static when called
*/
void display_scores(PlayerScore *arrScores, int *nScores)
{
	int i;
    int new_scores_loaded = 0;
    load_scores(arrScores, nScores);
    if (new_scores_loaded) {
        // new scores have been loaded, so re-sort the array
        int i, j;
        PlayerScore temp;
        // bubble sort
        for (i = 0; i < *nScores - 1; i++) {
            for (j = 0; j < *nScores - i - 1; j++) {
                if (arrScores[j].nScore < arrScores[j+1].nScore) {
                    temp = arrScores[j];
                    arrScores[j] = arrScores[j+1];
                    arrScores[j+1] = temp;
                }
            }
        }
    }
    printf("Top Scores:\n");
    printf("-----------\n");
    for (i = 0; i < *nScores; i++) {
        printf("%d. %s - %d\n", i+1, arrScores[i].strName, arrScores[i].nScore);
    }
}

/* play_game is used to provide the UI of the game itself that the use can play
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param nQuestions is used to refer to the maximum amount of arrQuestions
	@param *arrScores is used to refer to the array arrScores[]
	@param *nScores is used to refer to the maximum amount of arrScores
	pre-condition: all of the integer parameters have to be initialized
*/
void play_game(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores) {
	int nAdd = 0;
    int flag1 = 0;
    int flag2 = 0;
    char strName[21];
    int i, j;
    printf("Enter your name: ");
    scanf("%s", strName);

    while (1&&!flag2) {
        // Reset flags
        flag1 = 0;

        // Create an array of unique topics
        char topics[nQuestions][21];
        int num_topics = 0;
        for (i = 0; i < nQuestions; i++) {
            int is_duplicate = 0;
            for (j = 0; j < num_topics; j++) {
                if (strcmp(topics[j], arrQuestions[i].strTopic) == 0) {
                    is_duplicate = 1;
                    flag1 = 1;
                }
            }
            if (!is_duplicate && !flag1) {
                strcpy(topics[num_topics], arrQuestions[i].strTopic);
                num_topics++;
            }
        }

        // Display topics and their associated arrQuestions
        if (!flag1){
            printf("\nAvailable topics:\n");
            for (i = 0; i < num_topics; i++) {
                printf("%d. %s\n", i + 1, topics[i]);
                printf("   Questions:\n");
                for (j = 0; j < nQuestions; j++) {
                    if (strcmp(arrQuestions[j].strTopic, topics[i]) == 0) {
                        printf("   - %s\n", arrQuestions[j].strQuestion);
                    }
                }
            }
            printf("0. End game\n");

            int nChoice;
            printf("\nEnter your choice: ");
            scanf("%1d%*c", &nChoice);

            if (nChoice == 0) {
                printf("\n%s, your final score is %d.\n", strName, nAdd);
                add_score(arrScores, nScores, strName, nAdd);
                flag2 = 1;  // set flag2 to 1 to exit while loop
            } else if (nChoice < 1 || nChoice > num_topics) {
                printf("\nInvalid choice. Please try again.\n");
            } else {
                int count = 0;
                for (i = 0; i < nQuestions; i++) {
                    if (strcmp(arrQuestions[i].strTopic, topics[nChoice - 1]) == 0) {
                        count++;
                    }
                }

                if (count == 0) {
                    printf("\nNo questions available for this topic. Please choose another topic.\n");
                } else {
                    int index = rand() % count + 1;
                    i = 0;
                    while (index > 0) {
                        if (strcmp(arrQuestions[i].strTopic, topics[nChoice - 1]) == 0) {
                            index--;
                        }
                        i++;
                    }
                    i--;

                    printf("\n%s\n", arrQuestions[i].strTopic);
                    printf("Q. %s\n", arrQuestions[i].strQuestion);
                    printf("1. %s\n", arrQuestions[i].strChoices[0]);
                    printf("2. %s\n", arrQuestions[i].strChoices[1]);
                    printf("3. %s\n", arrQuestions[i].strChoices[2]);
                    printf("\nType your answer: ");
                    char answer[31];
                    scanf("%s", answer);


       				if (strcmp(answer, arrQuestions[i].strAnswer) == 0) {
        			    printf("Correct! You earned 1 point.\n");
        			    nAdd++;
        			} else {
            			printf("Sorry, the correct answer is: %s\n", arrQuestions[i].strAnswer);
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
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param *nQuestions is used to refer to the maximum amount of arrQuestions
	pre-condition: nQuestions has to be initialized
*/
void admin_menu(Question *arrQuestions, int *nQuestions) 
{
    int nChoice = 0;
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
        scanf("%1d%*c", &nChoice);
        
        switch (nChoice) {
            case 1: {
                add_record(arrQuestions, nQuestions);
                break;
            }
            case 2: {
                edit_record(arrQuestions, nQuestions);
                break;
            }
            case 3: {
                delete_record(arrQuestions, nQuestions);
                break;
            }
            case 4: {
                import_data(arrQuestions, nQuestions);
                break;
            }
            case 5: {
                export_data(arrQuestions, nQuestions);
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
/* game_menu is used to display the game menu where users may play the game and view their arrScores
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param nQuestions is used to refer to the maximum amount of arrQuestions
	@param *arrScores is used to refer to the array arrScores[]
	@param *nScores is used to refer to the maximum amount of arrScores
	pre-condition: integer parameters need to be initialized
*/
void game_menu(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores) 
{
    int nChoice;
    do {
        printf("\n--- GAME MENU ---\n");
        printf("1. Play\n");
        printf("2. View Scores\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%1d%*c", &nChoice);
        switch (nChoice) {
            case 1:
                play_game(arrQuestions, nQuestions, arrScores, nScores);
                break;
            case 2:
                display_scores(arrScores, nScores);
                break;
            case 0:
                save_scores(arrScores, *nScores); // save arrScores before exiting
                printf("\nExiting game menu...\n");
                break;
            default:
                printf("\nError: Invalid Input\n");
                break;
        }
    } while (nChoice != 0);
}

/* main_menu is used to display the main menu where users may either access the admin menu or the game menu
	@param *arrQuestions is used to refer to the array arrQuestions[]
	@param nQuestions is used to refer to the maximum amount of arrQuestions
	@param *strQuestion is used to refer to the string strQuestion[]
	@param *arrScores is used to refer to the array arrScores[]
	@param *nScores is used to refer to the maximum amount of arrScores
	pre-condition: integer parameters need to be initialized
*/
void main_menu(Question *arrQuestions, int nQuestions, char *strQuestion, PlayerScore *arrScores, int *nScores) 
{
    int nChoice = -1;
    int back = 0;
    while (!back) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Manage Data [Admin]\n");
        printf("2. Game Menu\n");
        printf("0. Exit Program\n");
        printf("\nEnter your choice: ");
		scanf("%1d%*c", &nChoice);
        switch (nChoice) {
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
            			printf("\nAccess granted. Proceeding to admin menu.\n");
                        admin_menu(arrQuestions, &nQuestions);
        			} else if (strcmp(password, "0") == 0) {
            			printf("\nGoing back to main menu.\n");
            			back = 1;
        			} else {
            			printf("\nInvalid password. Try again.\n");
        			}
    			}
    			break;
			}
            case 2: {
    			printf("Proceeding to game menu.\n");
    			game_menu(arrQuestions, nQuestions, arrScores, nScores);
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
	Question arrQuestions[11];
    int nQuestions = 0;
    char strQuestion[151];
    PlayerScore arrScores[11];
    int nScores = 0;
    
    main_menu(arrQuestions, nQuestions, strQuestion, arrScores, &nScores);
    
    return 0;
}
