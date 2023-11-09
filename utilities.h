// Helpers and data structures definitions
#ifndef HELPERS_H
#define HELPERS_H

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

//makes sure a word is only letters since the array will be out of bounds if non letters are used.
bool isOnlyLetters(const char *str);
void toLowerCase(char *str);//string to lowers case
void printWordsData(const WordsData *data);//for debugging purposes and used once in beginning.
void capitalizeFirstChar(char *str);//helper for Find_Verify(capitalizing first letter in a arrray to mark it as visited).

/*
#This function creates an array of 27 indixes(1 for each letter in alphabet).
#At each index another array is created and all the words(in the txt file) starting with the letter of the corresponding index are added to this array.
#finally the 2d array (or 3d if we count the words as array of chars) is returned.
#they are both stored in a struct.
*/
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

#endif // HELPERS_H