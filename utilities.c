// Include standard libraries needed for the implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// ... other includes as necessary

#include "utilities.h"

int myMax(int a, int b) {
    return (a > b) ? a : b;
}

int myMin(int a, int b) {
    return (a < b) ? a : b;
}
// Implementation of the functions declared in helpers.h
// ...
bool isOnlyLetters(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalpha((unsigned char)str[i])) {
            return false;
        }
    }
    return true;
}
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}
void printWordsData(const WordsData *data) {//for debugging purposes and used once in biginning.
    if (!data) {
        printf("WordsData is NULL.\n");
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (data->word_count_static[i] > 0) {
            printf("Letter %c: %d words\n", 'a' + i, data->word_count_static[i]);
            for (int j = 0; j < data->word_count_static[i]; j++) {
                printf("%s ", data->words[i][j]);
            }
            printf("\n\n");
        } else {
            printf("Letter %c: 0 words\n\n", 'a' + i);
        }
    }
}
void capitalizeFirstChar(char *str) {//helper for Find_Verify.
    if (str && *str) {
        *str = toupper((unsigned char)*str);
    }
}
int Find_Verify(WordsData *wordsData, char *word, char lastLetter, char requiredL){
    char ***words = wordsData->words;
    int *word_count = wordsData->word_count;
    char firstLetter=word[0];
    if(requiredL!=' '){//' ' means its the first round.
        if (word[0]!= requiredL){// this is scase 3 done.
            return 3;
        }
    }
    /*if (word_count[lastLetter-'a']==0){//case 4(win)

        return 4;
    }
    */
    for(int i=0;i<wordsData->word_count_static[firstLetter-'a'];i++){
        char *wordOfArr = words[firstLetter-'a'][i];
        //printf("%s\t",wordOfArr);
        if(strcasecmp(word, wordOfArr) == 0){//word is equal to a spell
            if(isupper(wordOfArr[0])){
                 return 1;
            }//word found but is capitalized indicating it was used before
            else if (word_count[lastLetter-'a']==0){//case 4(win)
            return 4;
            }
            else{

                capitalizeFirstChar(words[firstLetter-'a'][i]);
                wordsData->word_count[firstLetter-'a']--;
                return 0;
            }
        }
    }
    return 2;//we have not found the word after looping through all the words that start with the necessary letter.
}
WordsData createWordsArrayFromFile(const char *filename) {//returns a Wordsdata struct, 
     WordsData data = {NULL, {0}, {0}};
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return data;
    }
    char word[26]; // this will be the variable we store the word in each line in

    // Read first line(get how many words)
    int numberOfWords=5;
    if (fgets(word, sizeof(word), file) == NULL) {
    perror("file is empty");
    fclose(file);
    return data;
}

// Convert the first line to an integer
if (sscanf(word, "%d", &numberOfWords) != 1) {
    perror("Failed to read the integer from the file");
    fclose(file);
    return data;
}
    char ***words = (char ***)malloc(26 * sizeof(char **));  // Allocate for 26 letters
    for (int i = 0; i < 26; i++) {
        words[i] = (char **)malloc(numberOfWords * sizeof(char *));  // Allocate for each list of words per letter
        //we are assuming each letter index array could hold maximume numberOfWords.
        for (int j = 0; j < numberOfWords; j++) {
            words[i][j] = NULL;  // Initialize each word pointer to NULL.later we will allocate memory with appropriate quantityfor each word.
        }
    }

    int word_count[26] = {0};
    /*
    The purpose of the word_count array is to keep track of how many 
    words have been stored for each letter of the alphabet in the words 2D array.
    */
    while (fgets(word, sizeof(word), file) != NULL) {
        size_t length = strlen(word);
        if (length > 0 && word[length - 1] == '\n') {
            word[length - 1] = '\0';
            length--;
        }// we here are getting the line, then removing the \n so now word is our word.

        int index = word[0] - 'a';
        if (index >= 0 && index < 26) {
            words[index][word_count[index]] = strdup(word);// here we are dynamically allocating memory for word in appropriate letter array.
            word_count[index]++;
        }
    }
    fclose(file);//done with file and filling array
    /*
    this loop  shrinks the allocated memory to exactly fit the corect number of words for each letter. If there are no words for a letter, it frees the memory entirely.
    */
    for (int i = 0; i < 26; i++) {
    if (word_count[i] > 0) {
        words[i] = realloc(words[i], word_count[i] * sizeof(char *));
    } else {
        // If no words were added for this letter, we free its memory
        free(words[i]);
        words[i] = NULL;
    }
}
    //printWordsArray(words,word_count);
    //printWordCounts(word_count);

    memcpy(data.word_count, word_count, sizeof(word_count));

    // Assigning the words array to the data struct
    data.words = words;
    return data;
}
void print2dArray(int **array) {
    // Print top header (columns)
    printf("   "); // Spacing for row header
    for (char col = 'a'; col <= 'z'; col++) {
        printf("%c ", col);
    }
    printf("\n");

    // Print each row
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // Print row header
        printf("%c  ", 'a' + i);

        // Print row data
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}
int** createWordsEndingInArray(char ***words, int wordCount[ALPHABET_SIZE]) {
    // Dynamically allocate the wordsEndingIn array
    int** wordsEndingIn = (int**)malloc(ALPHABET_SIZE * sizeof(int*));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        wordsEndingIn[i] = (int*)malloc(ALPHABET_SIZE * sizeof(int));
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            wordsEndingIn[i][j] = 0; // Initialize with 0
        }
    }

    // Fill the wordsEndingIn array based on words and wordCount
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < wordCount[i]; j++) {
            char *word = words[i][j];
            int len = strlen(word);
            if (len > 0) {
                int startIdx = word[0] - 'a';
                int endIdx = word[len - 1] - 'a';
                if (startIdx >= 0 && startIdx < ALPHABET_SIZE && endIdx >= 0 && endIdx < ALPHABET_SIZE) {
                    wordsEndingIn[startIdx][endIdx]++;
                }
            }
        }
    }
    
    return wordsEndingIn;
}

GameState createGameState(WordsData *wordsData) {
    GameState gameState;

    gameState.lastLetterBefore = ' '; // Initialize lastLetter
    memcpy(gameState.word_Count, wordsData->word_count, sizeof(wordsData->word_count));

    // Directly assign the pointer
    gameState.wordsEndingIn = createWordsEndingInArray(wordsData->words, wordsData->word_count);


    return gameState;
}
