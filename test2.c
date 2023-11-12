#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


#include "botLogic.h"
#include "utilities.h"
// Include other necessary headers

// Define test functions
void testFindMatchingWord() {

    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    MinimaxResult minimaxResult = { .firstLetter = 'a', .lastLetter = 'a' }; // Example test case
    char *expectedWord = "alohomora"; // Expected result for this test case

    char *result = findMatchingWord(&wordsData, minimaxResult);
    printf("expected: %s\n",expectedWord);
    printf("actual: %s\n",result);
    if (strcmp(result, expectedWord) == 0) {
        printf("Test findMatchingWord: PASS\n");
    } else {
        printf("Test findMatchingWord: FAIL\n");
    }
}


void testChooseWordWithMinimax() {
    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    GameState gameState = createGameState(&wordsData);
    gameState.lastLetterBefore = 'n';
    char *expectedWord = "expectedWord"; // Change based on your expected outcome

    char *result = chooseWordWithMinimax(&wordsData, &gameState);
    printf("expected: %s\n",expectedWord);
    printf("actual: %s\n",result);
    if (strcmp(result, expectedWord) == 0) {
        printf("Test chooseWordWithMinimax: PASS\n");
    } else {
        printf("Test chooseWordWithMinimax: FAIL\n");
    }
}

void testIsTerminalState() {
    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    GameState gameState = createGameState(&wordsData);
    gameState.lastLetterBefore = 'h';
    bool expected = true; // or false, depending on what you expect in this test case

    bool result = isTerminalState(&gameState);
    if (result == expected) {
        printf("Test isTerminalState: PASS\n");
    } else {
        printf("Test isTerminalState: FAIL\n");
    }
}


void testUpdateAndUndoGameState() {
    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    GameState gameState = createGameState(&wordsData);

    char startingLetter = 'a'; // Example starting letter
    char endingLetter = 'o';   // Example ending letter

    // Make a copy of relevant data for comparison
    int originalWordCount[ALPHABET_SIZE];
    memcpy(originalWordCount, gameState.word_Count, sizeof(originalWordCount));

    int originalWordsEndingIn[ALPHABET_SIZE][ALPHABET_SIZE];
    memcpy(originalWordsEndingIn, gameState.wordsEndingIn, sizeof(originalWordsEndingIn));

    // Apply update and undo operations
    updateGameState(&gameState, startingLetter, endingLetter);
    undoGameStateUpdate(&gameState, startingLetter, endingLetter);

    // Check if gameState is reverted correctly
    bool isRevertedCorrectly = true;
    if (memcmp(originalWordCount, gameState.word_Count, sizeof(originalWordCount)) != 0) {
        isRevertedCorrectly = false;
    }
    if (memcmp(originalWordsEndingIn, gameState.wordsEndingIn, sizeof(originalWordsEndingIn)) != 0) {
        isRevertedCorrectly = false;
    }

    // Print test result
    if (isRevertedCorrectly) {
        printf("Test update and undo GameState: PASS\n");
    } else {
        printf("Test update and undo GameState: FAIL\n");
    }
}
void printAllMoves(MinimaxResult* moves) {
    if (!moves) {
        printf("No moves to print.\n");
        return;
    }

    printf("Generated Moves:\n");
    for (int i = 0; moves[i].firstLetter != '\0' && moves[i].lastLetter != '\0'; i++) {
        printf("Move %d: Start with '%c', End with '%c'\n", i + 1, moves[i].firstLetter, moves[i].lastLetter);
    }
}
void testGeneratePossibleMoves() {
    // Setup a specific game state for testing
    WordsData wordsData = createWordsArrayFromFile("spells.txt");
    GameState gameState = createGameState(&wordsData);
    gameState.lastLetterBefore = 'n';
    // Call the function to test
    MinimaxResult* moves = generatePossibleMoves(&gameState);

    // Check if moves are generated correctly
    if (!moves) {
        printf("generatePossibleMoves Test: FAIL (No moves generated)\n");
        return;
    }

    bool isValid = true;
    for (int i = 0; moves[i].firstLetter != '\0' && moves[i].lastLetter != '\0'; i++) {
        int startIdx = moves[i].firstLetter - 'a';
        int endIdx = moves[i].lastLetter - 'a';

        // Check if the move is valid
        if (gameState.wordsEndingIn[startIdx][endIdx] <= 0) {
            isValid = false;
            break;
        }
    }

    // Check for sentinel value at the end
    if (moves[ALPHABET_SIZE * ALPHABET_SIZE].firstLetter != '\0' || moves[ALPHABET_SIZE * ALPHABET_SIZE].lastLetter != '\0') {
        isValid = false;
    }

    if (isValid) {
        printf("generatePossibleMoves Test: PASS\n");
    } else {
        printf("generatePossibleMoves Test: FAIL (Invalid moves generated)\n");
    }
    printAllMoves(moves);
    // Free allocated memory
    free(moves);
}


int main() {
    //testFindMatchingWord();
    //testChooseWordWithMinimax();
    //testIsTerminalState();
    //testUpdateAndUndoGameState();
    testGeneratePossibleMoves();
    return 0;
}