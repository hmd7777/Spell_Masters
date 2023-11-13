#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#include "botLogic.h"
#include "utilities.h"

#define WINNING_SCORE 50

char* findMatchingWord(WordsData *wordsData, MinimaxResult minimaxResult) {
    int index = minimaxResult.firstLetter - 'a';  // Convert letter to index (assuming lowercase)
    for (int i = 0; i < wordsData->word_count[index]; i++) {
        char *currentWord = wordsData->words[index][i];
        if (currentWord != NULL && islower(currentWord[0])) {  // Check if the first letter is lowercase
            int len = strlen(currentWord);
            if (currentWord[len - 1] == minimaxResult.lastLetter) {
                // Found a word that matches the criteria
                return currentWord;
            }
        }
    }
    return NULL; // No matching word found
}
char* chooseInitialWordWithMinimax(WordsData *wordsData, GameState *gameState, int depth) {
    int bestScore = INT_MIN;
    char *bestWord = NULL;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    // Iterate over all words
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < wordsData->word_count[i]; j++) {
            char *currentWord = wordsData->words[i][j];

            // Check if the word is valid (not used before)
            if (isValidWord(currentWord)) {
                // Temporarily update the game state
                char lastLetter = currentWord[strlen(currentWord) - 1];
                updateGameState(gameState, currentWord[0], lastLetter);

                // Perform Minimax with Alpha-Beta pruning
                MinimaxResult result = minimax(gameState, depth, false, alpha, beta);

                // Undo the update
                undoGameStateUpdate(gameState, currentWord[0], lastLetter);

                // Update the best score and word if necessary
                if (result.score > bestScore) {
                    bestScore = result.score;
                    bestWord = currentWord;
                    alpha = result.score; // Update alpha
                }
            }
        }
    }

    // Return the best starting word found
    return bestWord; // Note: Ensure this word is properly handled or duplicated if necessary.
}

bool isValidWord(char *word) {
    // Assuming the word is invalid if its first letter is capitalized
    return islower(word[0]);
}

char* chooseWordWithMinimax(WordsData *wordsData, GameState *gameState,char* difficulty) {
    int num = atoi(difficulty);
    num = 4-num;
    //printf("Running chooseWordWithMinimax...\n");
    // Step 1: Run the Minimax algorithm to determine the best starting and ending letters
    if(gameState->lastLetterBefore == ' '){
        return chooseInitialWordWithMinimax(wordsData,gameState,num);
    }
    MinimaxResult result = minimax(gameState, num, true, INT_MIN, INT_MAX);

    
    // Step 2: Use the Minimax result to find a matching word
    char* chosenWord = findMatchingWord(wordsData, result);
    //printf("Matching word found: %s\n", chosenWord ? chosenWord : "None");
    // Return the chosen word
    return chosenWord; // Note: You might want to handle the case where no matching word is found
}

MinimaxResult minimax(GameState *gameState, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    MinimaxResult result;
    result.firstLetter = '\0';
    result.lastLetter = '\0';
    result.score = isMaximizingPlayer ? INT_MIN : INT_MAX;

    if (depth == 0 || isTerminalState(gameState)) {
        result.score = evaluateGameState(gameState);
        return result;
    }

    MinimaxResult* moves = generatePossibleMoves(gameState);
    if (!moves) {
        result.score = isMaximizingPlayer ? INT_MIN : INT_MAX;
        return result;
    }

    for (int i = 0; moves[i].firstLetter != '\0' && moves[i].lastLetter != '\0'; i++) {
        updateGameState(gameState, moves[i].firstLetter, moves[i].lastLetter);
        MinimaxResult tempResult = minimax(gameState, depth - 1, !isMaximizingPlayer, alpha, beta);
        undoGameStateUpdate(gameState, moves[i].firstLetter, moves[i].lastLetter);

        if (isMaximizingPlayer) {
            if (tempResult.score > result.score) {
                result.score = tempResult.score;
                result.firstLetter = moves[i].firstLetter;
                result.lastLetter = moves[i].lastLetter;
            }
            alpha = myMax(alpha, result.score);
        } else {
            if (tempResult.score < result.score) {
                result.score = tempResult.score;
                result.firstLetter = moves[i].firstLetter;
                result.lastLetter = moves[i].lastLetter;
            }
            beta = myMin(beta, result.score);
        }

        // Alpha-beta pruning condition
        if (beta <= alpha) {
            break;
        }
    }

    freeGeneratedMoves(moves);
    return result;
}

int evaluateGameState(GameState *gameState) {
    if (!gameState || gameState->lastLetterBefore < 'a' || gameState->lastLetterBefore > 'z') {//maybe
        return 0;
    }
    int index = gameState->lastLetterBefore - 'a';
    return WINNING_SCORE -gameState->word_Count[index];
}

//Determines if the game state is a terminal state, i.e., the game is over or a certain condition is met (like no valid moves left).
bool isTerminalState(GameState *gameState) {
    // Get the index of the last letter used in the game
    int index = gameState->lastLetterBefore - 'a';
    //printf("nigger");
    // Check if the array is valid and the index is within bounds
    if (index < 0 || index >= ALPHABET_SIZE) {
        return true; // This could also be handled differently based on your game's logic
    }

    // Check if there are no words available that start with this letter
    if (gameState->word_Count[index] == 0) {
        return true; // Terminal state reached
    }
    return false; // More moves are possible
}


void updateGameState(GameState *gameState, char startingLetter, char endingLetter) {
   // printf("Updating game state with starting letter: %c, ending letter: %c\n", startingLetter, endingLetter);
    if (!gameState || startingLetter < 'a' || startingLetter > 'z' || endingLetter < 'a' || endingLetter > 'z') {
        // Handle invalid input
        return;
    }

    // Convert letters to array indices
    int startIdx = startingLetter - 'a';
    int endIdx = endingLetter - 'a';

    // Decrement the word count for the starting letter
    if (gameState->word_Count[startIdx] > 0) {
        gameState->word_Count[startIdx]--;
    }

    // Update the wordsEndingIn array
    if (gameState->wordsEndingIn[startIdx][endIdx] > 0) {
        gameState->wordsEndingIn[startIdx][endIdx]--;
    }

    // Update the last letter for the next turn
    gameState->lastLetterBefore = endingLetter;

    // Additional updates to GameState can be made here if necessary
}
//Reverts changes made by updateGameState. This is crucial for backtracking in the Minimax algorithm.
void undoGameStateUpdate(GameState *gameState, char startingLetter, char endingLetter) {
    //printf("Undoing game state update for starting letter: %c, ending letter: %c\n", startingLetter, endingLetter);
    if (!gameState || startingLetter < 'a' || startingLetter > 'z' || endingLetter < 'a' || endingLetter > 'z') {
        // Handle invalid input
        return;
    }

    // Convert letters to array indices
    int startIdx = startingLetter - 'a';
    int endIdx = endingLetter - 'a';

    // Increment the word count for the starting letter
    // This undoes the decrement done in updateGameState
    gameState->word_Count[startIdx]++;

    // Update the wordsEndingIn array
    // This undoes the decrement done in updateGameState
    gameState->wordsEndingIn[startIdx][endIdx]++;

    // You might also need to restore the last letter before the move
    // This depends on how you are tracking the sequence of moves in your game
    // gameState->lastLetterBefore = <previous last letter>;
}

//Generates all possible moves (letter pairs in your case) from the current game state.
MinimaxResult* generatePossibleMoves(GameState *gameState) {
    if (!gameState) {
        return NULL;
    }

    // Convert the last letter used to an index
    int lastLetterIndex = gameState->lastLetterBefore - 'a';
    if (lastLetterIndex < 0 || lastLetterIndex >= ALPHABET_SIZE) {
        return NULL;  // Invalid last letter
    }

    // Allocate memory for the moves array
    MinimaxResult* moves = malloc(ALPHABET_SIZE * sizeof(MinimaxResult)); // Only need ALPHABET_SIZE moves at most
    if (!moves) {
        return NULL;  // Memory allocation failure
    }

    int moveCount = 0;
    for (int j = 0; j < ALPHABET_SIZE; j++) {
        if (gameState->wordsEndingIn[lastLetterIndex][j] > 0) {
            moves[moveCount].firstLetter = gameState->lastLetterBefore;
            moves[moveCount].lastLetter = 'a' + j;
            moveCount++;
        }
    }

    // Set the sentinel value
    moves[moveCount].firstLetter = '\0'; // Use '\0' as the sentinel value
    moves[moveCount].lastLetter = '\0';

    return moves;
}


//If generatePossibleMoves dynamically allocates memory for the moves, you'll need a function to free that memory.
void freeGeneratedMoves(MinimaxResult *moves) {
    //printf("Freeing generated moves...\n");
    if (moves) {
        free(moves);
    }
}