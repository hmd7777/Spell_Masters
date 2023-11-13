#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#include "botLogic.h"
#include "utilities.h"
// Include other necessary headers

void TestPlayerVsBot() {
    char player1[50] = "Player"; // Directly assign player name for testing
    char bot[20] = "Bot"; // Directly assign bot name for testing

    // Directly set bot difficulty for testing
    char bot_difficulty[10] = "2"; // Example: Set to '2' for medium difficulty

    printf("Testing PlayerVsBot with %s difficulty\n", bot_difficulty);

    // Initialize wordsData, gameState and other variables needed for the battle
    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    for (int i = 0; i < 26; i++) {
        wordsData.word_count_static[i] = wordsData.word_count[i];
    }
    GameState gameState = createGameState(&wordsData);

    // Directly set the initial turn (true for player, false for bot)
    bool p1turn = true; // Example: Set true if player starts, false if bot starts

    char word[26];
    int status;
    char LastLetter;
    char FirstLetter = ' ';
    char *chosenPlayer;
    // Start the battle
    while(true){//start the battle
        if (p1turn) chosenPlayer = player1;
        else chosenPlayer = bot;

        do{
            printf("%s choose a spell(only letters): \n",chosenPlayer);
            if(!p1turn){
                Sleep(2000);
                char *chosenword = chooseWordWithMinimax(&wordsData, &gameState);
                printf("\n");
                printf("\n");
            if (chosenword) {
                strcpy(word, chosenword);
                printf("%s chooses %s\n", bot, chosenword);
            } else {
                printf("No valid move for %s\n", bot);
                break; // or handle this scenario appropriately
            }
            Sleep(1000);
            }
            else{
            scanf("%25s",word);
            toLowerCase(word);
            Sleep(1000);
        }
        }while (!isOnlyLetters(word));
        LastLetter = word[strlen(word) - 1];
        status = Find_Verify(&wordsData,  word,LastLetter, FirstLetter); // verify word
        if (status == 0) {
            printf("%s. Valid choice %s. \nNext turn:\n", word, chosenPlayer);
        } else if (status == 1) {
            printf("Oops, %s was already taken. Unlucky, %s.\n", word, chosenPlayer);
            break;
        } else if (status == 2) {
            printf("This word doesn't exist. Better luck next time, %s.\n", chosenPlayer);
            break;
        } else if (status == 3) {
            printf("Wrong starting letter (your word should have started with %c). Game over.\n", FirstLetter);
            break;
        } else {
            printf("Perfect pick! You win.\n");
            break;
            }
        char templetter = word[0];
        FirstLetter = LastLetter;
        gameState.wordsEndingIn[templetter - 'a'][LastLetter-'a']--;
        gameState.lastLetterBefore = FirstLetter;
        //print2dArray(gameState.wordsEndingIn);
        p1turn=!p1turn;
    }//print2dArray(gameState.wordsEndingIn);
    if (status>=1 && status<=3){
        if (p1turn) printf("Congratiolations %s!!.",bot);
        else printf("Congratiolations %s!!.",player1);
    }
    else{
        if (p1turn) printf("Congratiolations %s!!.",player1);
        else printf("Congratiolations %s!!.",bot);
    }
}

int main() {
    TestPlayerVsBot();
    return 0;
}