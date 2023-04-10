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

typedef struct{
	int nQuestion; 
    char strTopic[151]; 
    char strQuestion[151]; 
    char strChoices[3][151]; 
    char strAnswer[151]; 
} Question;

typedef struct{
	int nScore;
    char strName[21];
} PlayerScore;

// -------------------------------
// ----- FUNCTION PROTOTYPES -----
// -------------------------------

int find_question(Question *arrQuestions, int nQuestions, char *strQuestion);
void add_record(Question *arrQuestions, int *nQuestions);
void edit_record(Question *arrQuestions, int nQuestions);
void delete_record(Question *arrQuestions, int *nQuestions);
void import_data(Question *arrQuestions, int *nQuestions);
void export_data(Question *arrQuestions, int *nQuestions);
void load_scores(PlayerScore *arrScores, int *nScores);
void save_scores(PlayerScore *arrScores, int nScores);
void add_score(PlayerScore *arrScores, int *nScores, char *strName, int nScore);
void display_scores(PlayerScore *arrScores, int *nScores);
void play(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores);
void admin_menu(Question *arrQuestions, int *nQuestions);
void game_menu(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores);
void main_menu(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores);


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
    char strAnswer[151];
    char strChoice1[151];
    char strChoice2[151];
    char strChoice3[151];
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
void edit_record(Question *arrQuestions, int nQuestions)
{
    char topic[21];
    int question_num;
    int back = 0;
	int i, j;
	int index;
    // Display available topics
    printf("Available topics:\n");
    for (i = 0; i < nQuestions; i++) {
    // Check if this topic has already been printed
    	int already_printed = 0;
    	int found_topic = 0;
    	for (j = 0; j < i && !found_topic; j++) {
        	if (strcmp(arrQuestions[i].strTopic, arrQuestions[j].strTopic) == 0) {
            	already_printed = 1;
            	found_topic = 1;
        	}
    	}
    	if (!already_printed) {
        	printf("%s\n", arrQuestions[i].strTopic);
    	}
	}

    // Ask for topic
    printf("Enter topic: ");
    scanf("%s", topic);

    // Display questions in the selected topic
    printf("Questions in topic '%s':\n", topic);
    int num_questions = 0;
    for (i = 0; i < nQuestions; i++) {
        if (strcmp(arrQuestions[i].strTopic, topic) == 0) {
            printf("%d. %s\n", arrQuestions[i].nQuestion, arrQuestions[i].strQuestion);
            num_questions++;
        }
    }

    // Ask for question number to edit
    if (!back) {
        printf("Enter question number to edit: ");
        scanf("%d", &question_num);

        // Find the question to edit
        index = -1;
        int found_question = 0;  // initialize the flag variable to false
        for (i = 0; i < nQuestions && !found_question; i++) {
            if (strcmp(arrQuestions[i].strTopic, topic) == 0 && arrQuestions[i].nQuestion == question_num) {
                index = i;
                found_question = 1;  // set the flag variable to true
            }
        }
        if (!found_question) {  // check the value of the flag variable
            printf("Error: Invalid Input\n");
            back = 1;
        }
        if (!question_num) {
        	printf("Going back...\n");
        	back = 1;
		}
    }

    // Ask for field to modify
    if (!back) {
        char field[10];
        printf("Enter field to modify (topic, question, choice1, choice2, choice3, answer): ");
        scanf("%s", field);

        // Modify the selected field
        if (strcmp(field, "topic") == 0) {
            printf("Enter new topic: ");
            scanf("%s", arrQuestions[index].strTopic);
            printf("Record updated successfully!");
        }
        else if (strcmp(field, "question") == 0) {
            printf("Enter new question: ");
            scanf(" %[^\n]", arrQuestions[index].strQuestion);
            printf("Record updated successfully!");
        }
        else if (strcmp(field, "choice1") == 0) {
            printf("Enter new choice 1: ");
            scanf(" %[^\n]", arrQuestions[index].strChoices[0]);
            printf("Record updated successfully!");
        }
        else if (strcmp(field, "choice2") == 0) {
            printf("Enter new choice 2: ");
            scanf(" %[^\n]", arrQuestions[index].strChoices[1]);
            printf("Record updated successfully!");
        }
        else if (strcmp(field, "choice3") == 0) {
            printf("Enter new choice 3: ");
            scanf(" %[^\n]", arrQuestions[index].strChoices[2]);
            printf("Record updated successfully!");
        }
        else if (strcmp(field, "answer") == 0) {
            printf("Enter new answer: ");
            scanf("%s", arrQuestions[index].strAnswer);
            printf("Record updated successfully!");
        }
        else {
            printf("Error: Invalid Input\n");
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
    char topic[21];
    int i, j, questionNumber, choice;
    int topicFound = 0, questionFound = 0;

    // Display available topics
    printf("Available topics:\n");
    for (i = 0; i < *nQuestions; i++) {
        // Check if topic has already been displayed
        if (strcmp(arrQuestions[i].strTopic, "") != 0) {
            int topicDisplayed = 0;
            for (j = 0; j < i && !topicDisplayed; j++) {
                if (strcmp(arrQuestions[i].strTopic, arrQuestions[j].strTopic) == 0) {
                    topicDisplayed = 1;
                }
            }
            // If topic has not been displayed, display it
            if (!topicDisplayed) {
                printf("%s\n", arrQuestions[i].strTopic);
            }
        }
    }

    // Ask for topic
    printf("Enter topic: ");
    scanf("%s", topic);

    // Check if topic exists
    for (i = 0; i < *nQuestions; i++) {
        if (strcmp(arrQuestions[i].strTopic, topic) == 0) {
            topicFound = 1;
            printf("%d. %s\n", arrQuestions[i].nQuestion, arrQuestions[i].strQuestion);
        }
    }

    // If topic exists, ask for question to delete
    if (topicFound) {
        printf("Enter question number to delete: ");
        scanf("%d", &questionNumber);

        // Check if question exists
        for (i = 0; i < *nQuestions; i++) {
            if (strcmp(arrQuestions[i].strTopic, topic) == 0 && arrQuestions[i].nQuestion == questionNumber) {
                questionFound = 1;
                printf("Are you sure you want to delete this record? (1 = Yes, 2 = No): ");
                scanf("%d", &choice);

                // Delete record if user confirms deletion
                if (choice == 1) {
                    for (j = i; j < *nQuestions - 1; j++) {
                        arrQuestions[j] = arrQuestions[j + 1];
                        // Decrement question number of questions after the deleted question
                        if (strcmp(arrQuestions[j].strTopic, topic) == 0) {
                            arrQuestions[j].nQuestion--;
                        }
                    }
                    (*nQuestions)--;
                    printf("Record deleted successfully!\n");
                } else {
                    printf("Record not deleted.\n");
                }
            }
        }

        if (!questionFound) {
            printf("Error: Invalid Input\n");
        }
    } else {
        printf("Error: Invalid Input\n");
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
        	printf("Going back...\n");
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
    for (i = 0; i < *nQuestions; i++) {
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
    static int loaded = 0;
    int file_unopened = 0; // flag variable
    if (!loaded) {
        FILE *fp = fopen("scores.txt", "r");
        if (fp == NULL) {
            printf("Unable to open file for reading scores!\n");
            file_unopened=1;
        }
		
		if(!file_unopened){
        int i = 0;
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
    int i, j;
    PlayerScore temp;

    load_scores(arrScores, nScores);

    // sort the array using bubble sort
    for (i = 0; i < *nScores - 1; i++) {
        for (j = 0; j < *nScores - i - 1; j++) {
            if (arrScores[j].nScore < arrScores[j+1].nScore) {
                temp = arrScores[j];
                arrScores[j] = arrScores[j+1];
                arrScores[j+1] = temp;
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
    int score = 0;
    int i, j;
    int isTopicDisplayed;
    int incorrect;
    int loop = 1;
    char playerName[21];
    printf("Enter your name: ");
    scanf("%s", playerName);
    getchar(); // clear the newline character from the input buffer
    
    while (loop) {
    	incorrect = 0;
        printf("\nAvailable Topics:\n");
        printf("-----------------\n");
        
        // display the list of available topics
        int topicCount = 1;	
		for (i = 0; i < nQuestions; i++) {
    		isTopicDisplayed = 0;
    		j = 0;
    		while (j < i && !isTopicDisplayed) {
        		if (strcmp(arrQuestions[i].strTopic, arrQuestions[j].strTopic) == 0) {
            		isTopicDisplayed = 1;
        		}
        		j++;
    		}
    		if (!isTopicDisplayed) {
        		printf("%d. %s\n", topicCount++, arrQuestions[i].strTopic);
    		}
		}

        
        // let the player choose a topic
        printf("\nChoose a topic (enter a number): ");
        int topicChoice;
        scanf("%d", &topicChoice);
        getchar(); // clear the newline character from the input buffer
        
        // display a random question from the chosen topic
        printf("\nQuestion: ");
        Question chosenQuestion;
        do {
            int randomQuestionIndex = rand() % nQuestions;
            chosenQuestion = arrQuestions[randomQuestionIndex];
        } while (strcmp(chosenQuestion.strTopic, arrQuestions[topicChoice - 1].strTopic) != 0);
        
        printf("%s\n", chosenQuestion.strQuestion);
        for (i = 0; i < 3; i++) {
            printf("%s\n", chosenQuestion.strChoices[i]);
        }
        printf("\nEnter your answer: ");
        char playerAnswer[151];
        fgets(playerAnswer, 151, stdin);
        strtok(playerAnswer, "\n"); // remove the newline character from the player's answer
        
        // check if the answer is correct
        if (strcmp(playerAnswer, chosenQuestion.strAnswer) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Sorry, that's incorrect.\n");
            incorrect = 1;
        }
        
        if (!incorrect){
	        // let the player choose whether to end the game or not
        	printf("\nYour score is: %d\n", score);
        	printf("Do you want to end the game? (y/n): ");
        	char endChoice;
        	scanf("%c", &endChoice);
        	getchar(); // clear the newline character from the input buffer
        	
        	if (endChoice == 'y') {
            	printf("\n%s, your final score is: %d\n", playerName, score);
            	add_score(arrScores, nScores, playerName, score);
            	loop = 0;
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
                edit_record(arrQuestions, *nQuestions);
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
void main_menu(Question *arrQuestions, int nQuestions, PlayerScore *arrScores, int *nScores) 
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
	Question arrQuestions[151];
    int nQuestions = 0;
    PlayerScore arrScores[151];
    int nScores = 0;
    
    main_menu(arrQuestions, nQuestions, arrScores, &nScores);
    
    return 0;
}
