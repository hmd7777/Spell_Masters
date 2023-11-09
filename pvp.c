#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#include "pvp.h"
#include "utilities.h"
bool coinflipAndWhoStartsPvP(char *player1, char *player2){//in this function a coin flip is randomly prompted top p1 or 2, and whoever wins starts the game.
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
    chosenPlayer = player2;
    p1=false;
    }
    char choice[10];
    printf("Now,to determine who starts.\n");
    do {
        printf("%s heads or tails?(case insensetive)\n",chosenPlayer);
        scanf("%s", choice);
        toLowerCase(choice);
    } while (strcmp(choice, "heads") != 0 && strcmp(choice, "tails") != 0);

    // Randomly generate heads or tails
    int result = rand() % 2; // 0 for heads, 1 for tails
    const char *results[] = {"heads", "tails"};
    printf("It's %s!\n", results[result]);

    // Check if the chosenPlayer's choice matches the result
    if (strcmp(choice, results[result]) == 0) {
        printf("%s, you won!\n", chosenPlayer);
        return p1 ==true;
    } else {
        printf("%s, you lost!\n", chosenPlayer);
        return p1 ==false;
    }
}
void PlayerVsPlayer() {
    
    char player1[50], player2[50];    
    printf("\nPlayer 1, enter your name: ");
    scanf(" %49[^\n]", player1);

    printf("Player 2: ");
    scanf(" %49[^\n]", player2); 
    WordsData wordsData = createWordsArrayFromFile("spells.txt");//initialize the words and words_count arrays
    for (int i = 0; i < 26; i++) {
    wordsData.word_count_static[i] = wordsData.word_count[i];
}
    printWordsData(&wordsData);//print all possible words
    printf("Hello %s and %s!\nAbove you can see all the possible words you can chose from.\n",player1,player2);
    bool p1turn = coinflipAndWhoStartsPvP(player1,player2);//initiate coin flip
    if (p1turn){
        printf("Congratz %s, you start. Now may the battle begin!\n",player1);
    }else{
        printf("Congratz %s, you start. Now may the battle begin!\n",player2);
    }
    char word[26];
    int status;
    char *chosenPlayer;
    char LastLetter;
    char Required = ' ';
    while(true){//start the battle
        if (p1turn) chosenPlayer = player1;
        else chosenPlayer = player2;
        do{
            printf("%s choose a spell(only letters): ",chosenPlayer);
            scanf("%25s",word);
            toLowerCase(word);
        }while (!isOnlyLetters(word));
        LastLetter = word[strlen(word) - 1];
        status = Find_Verify(&wordsData,  word,LastLetter, Required);
        if (status == 0) {
            printf("%s. Valid choice %s. \nNext turn:\n", word, chosenPlayer);
        } else if (status == 1) {
            printf("Oops, %s was already taken. Unlucky, %s.\n", word, chosenPlayer);
            break;
        } else if (status == 2) {
            printf("This word doesn't exist. Better luck next time, %s.\n", chosenPlayer);
            break;
        } else if (status == 3) {
            printf("Wrong starting letter (your word should have started with %c). Game over.\n", Required);
            break;
        } else {
            printf("Perfect pick! You win.\n");
            break;
}
        Required = LastLetter;
        p1turn=!p1turn;
        
    }
    if (status>=1 && status<=3){
        if (p1turn) printf("Congratiolations %s!!.",player2);
        else printf("Congratiolations %s!!.",player1);
    }
    else{
        if (p1turn) printf("Congratiolations %s!!.",player1);
        else printf("Congratiolations %s!!.",player2);
    }
    
}
