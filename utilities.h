// Helpers and data structures definitions
#ifndef HELPERS_H
#define HELPERS_H

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 25
#include <stdbool.h>
/*typedef struct {//stored together in a struct so parameter doesnt get crowded. and looks cleaner.
    char ***words;//3d array that categorizes words with their corresponding starting letters.
    int word_count[26];// array of number of words starting with each letter- as i capitalize/ remove one of the words after someone uses them size here wil decrement.
    int word_count_static[26];//size here will never decremenet/this will beb used for loops/nonstatic array will be used to check if there are no letters starting with certain letter
} WordsData; 
*/
typedef struct {
    char ***words;
    int word_count[26];
    int word_count_static[26];
} WordsData;

typedef struct {
    int word_Count[ALPHABET_SIZE];                
    int **wordsEndingIn; 
    char lastLetterBefore;
} GameState;

//makes sure a word is only letters since the array will be out of bounds if non letters are used.
bool isOnlyLetters(const char *str);
//requires: str is a pointer to a null-terminated string.
//effects: Checks if the string str contains only alphabetical letters. Returns true if only letters are found, otherwise returns false.
bool isOnlyLetters(const char *str);
void toLowerCase(char *str);//string to lowers case
//requires: str is a pointer to a null-terminated string.
//effects: Converts all uppercase letters in the string str to lowercase.
void toLowerCase(char *str);//string to lowers case
void printWordsData(const WordsData *data);//for debugging purposes and used once in beginning.
//requires: data is a pointer to a WordsData structure.
//effects: Prints the contents of the WordsData structure for debugging purposes.
void printWordsData(const WordsData *data);
void capitalizeFirstChar(char *str);//helper for Find_Verify(capitalizing first letter in a arrray to mark it as visited).
//requires: str is a pointer to a null-terminated string.
//effects: Capitalizes the first character of the string str.
void capitalizeFirstChar(char *str);

/*
#This function creates an array of 27 indixes(1 for each letter in alphabet).
#At each index another array is created and all the words(in the txt file) starting with the letter of the corresponding index are added to this array.
#finally the 2d array (or 3d if we count the words as array of chars) is returned.
#they are both stored in a struct.
*/
WordsData createWordsArrayFromFile(const char *filename);
//requires: filename is a string representing the name of a file.
//effects: Creates a 3D array (WordsData) from words in the specified file, categorizing them by their starting letters. Returns the WordsData structure.
WordsData createWordsArrayFromFile(const char *filename);
//if a word is found our startegy is to capitalize it so if we find it again it will be capitalized which will indicate that it was already used.
/*
if a word is found our startegy is to capitalize it so if we find it again it will be capitalized which will indicate that it was already used.
case0=word found.
case1=word found but used.
case2=word doesnt exist.
case3=started with wrong letter.
case4=win(the word exists and its last letter has no remaining words in the list)
*/
int Find_Verify(WordsData *wordsData, char *word, char lastLetter, char requiredL);
//requires:
//wordsData is a pointer to a WordsData structure.
//word is a pointer to a null-terminated string.
//lastLetter is a character indicating the last letter of the previous word.
//requiredL is the required starting letter for the word.
//effects: Verifies if word is valid based on several criteria: uncapitalized (unused), starts with requiredL, and exists in wordsData. Returns an integer code representing different scenarios (0: word found and valid, 1: word found but already used, 2: word doesnt exist, 3: wrong starting letter, 4: win condition).
int Find_Verify(WordsData *wordsData, char *word, char lastLetter, char requiredL);
int** createWordsEndingInArray(char ***words, int wordCount[ALPHABET_SIZE]);
//requires:
//words is a pointer to a 3D array of characters.
//wordCount is an array of integers representing the count of words for each alphabet letter.
//effects: Creates a 2D array indicating the number of words ending in each alphabet letter. Returns a pointer to the 2D array.
int** createWordsEndingInArray(char ***words, int wordCount[ALPHABET_SIZE]);
GameState createGameState(WordsData *wordsData);
//requires: wordsData is a pointer to a WordsData structure.
//effects: Creates and returns a GameState structure based on the given WordsData.
GameState createGameState(WordsData *wordsData);
void print2dArray(int array[ALPHABET_SIZE][ALPHABET_SIZE]);
//requires: array is a 2D array of integers with dimensions defined by ALPHABET_SIZE.
//effects: Prints the 2D array array for debugging purposes.
void print2dArray(int array[ALPHABET_SIZE][ALPHABET_SIZE]);
#endif // HELPERS_H
