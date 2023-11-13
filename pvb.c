#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "utilities.h"
#include "pvb.h"
#include "botLogic.h"


bool coinflipAndWhoStartsPvB(char *player1, char *bot){//in this function a coin flip is randomly prompted top p1 or 2, and whoever wins starts the game.
 // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Randomly choose Player 1 or Player 2
    int Rand = (rand() % 2) + 1;
    char *chosenPlayer;
    bool p1;
    if(Rand == 1){ 
        chosenPlayer = player1;
        p1=true;
    }
    else{ 
    chosenPlayer = bot;
    p1=false;
    }
    char choice[10];
    printf("Now,to determine who starts.\n");
    do {
        printf("%s heads or tails?(case insensetive)\n",chosenPlayer);
        if (chosenPlayer == player1){
        scanf("%s", choice);
        toLowerCase(choice);
        }
        else{
            int randomNumber = rand() % 2; // if 0 bot pick head else tails.
            if(randomNumber == 0) strcpy(choice, "heads");
            else strcpy(choice, "tails");
            Sleep(2000);
            printf("I %s choose %s.\n",bot, choice);
            Sleep(1000);
        }
    } while (strcmp(choice, "heads") != 0 && strcmp(choice, "tails") != 0);

    // Randomly generate heads or tails
    int result = rand() % 2; // 0 for heads, 1 for tails
    const char *results[] = {"heads", "tails"};
    Sleep(1000);
    printf("It's %s!\n", results[result]);
    Sleep(1000);

    // Check if the chosenPlayer's choice matches the result
    if (strcmp(choice, results[result]) == 0) {
        printf("%s, you won!\n", chosenPlayer);
        return p1 ==true;
    } else {
        printf("%s, you lost!\n", chosenPlayer);
        return p1 ==false;
    }
}
void PlayerVsBot() {
    
    char player1[50], bot[20];    
    printf("\nEnter your name: ");
    scanf(" %49[^\n]", player1);

    //select bot
    char bot_difficulty[10];
    int validInput = 0;

    while (!validInput) {
        printf("Choose the bot difficulty number: \n1-Bob(easy)\n2-Abdallah(medium)\n3-Abo Ubaida(hard)\n-");
        scanf("%99s", bot_difficulty);
        Sleep(400);
        // Check if the input is one of the valid options
        if (strcmp(bot_difficulty, "1") == 0 || strcmp(bot_difficulty, "2") == 0 || strcmp(bot_difficulty, "3") == 0) {
            validInput = 1;
            if (strcmp(bot_difficulty, "1") == 0) strcpy(bot, "Bob");
            if (strcmp(bot_difficulty, "2") == 0) strcpy(bot, "Abdallah");
            if (strcmp(bot_difficulty, "3") == 0) strcpy(bot, "Abu Ubaida");

        } else {
            printf("Invalid input. Please enter '1', '2', or '3'.\n");
        }
    }
    Sleep(400);
    printf("You chose: %s difficulty\n", bot_difficulty);
    

    printf("Hello %s!\nbelow you will see all the possible words you can chose from.\n",player1);
    Sleep(2000);
    WordsData wordsData = createWordsArrayFromFile("spells.txt");//initialize the words and words_count arrays
    for (int i = 0; i < 26; i++) {
    wordsData.word_count_static[i] = wordsData.word_count[i];
}
    printWordsData(&wordsData);//print all possible words

    bool p1turn = coinflipAndWhoStartsPvB(player1,bot);//initiate coin flip
    if (p1turn){
        printf("Congratz %s, you start. Now may the battle begin!\n",player1);
    }else{
        printf("Congratz %s, you start. Now may the battle begin!\n",bot);
    }
    char word[26];
    int status;
    char *chosenPlayer;
    char LastLetter;
    char FirstLetter = ' ';
    GameState gameState = createGameState(&wordsData);

    while(true){//start the battle
        if (p1turn) chosenPlayer = player1;
        else chosenPlayer = bot;

        do{
            printf("%s choose a spell(only letters): ",chosenPlayer);
            if(!p1turn){
                Sleep(1000);
                char *chosenword = chooseWordWithMinimax(&wordsData, &gameState,bot_difficulty);
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
            printf("1");
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
            printf("Perfect pick! %s win.\n",chosenPlayer);
            break;
            }
        FirstLetter = LastLetter;
        gameState.wordsEndingIn[FirstLetter- 'a'][LastLetter-'a']--;
        gameState.lastLetterBefore = FirstLetter;
        
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
