// Player vs Bot game logic
#ifndef BOT_LOGIC_H
#define BOT_LOGIC_H

#define MAX_WORDS_PER_LETTER 30
#define MAX_DEPTH 10
#define INFINITY 10000 // or use <limits.h> for INT_MAX

#include "utilities.h"

bool isValidWord(char *word);
char* chooseInitialWordWithMinimax(WordsData *wordsData, GameState *gameState,int diff);
// Function prototypes
char* findMatchingWord(WordsData *wordsData, MinimaxResult minimaxResult);

char* chooseWordWithMinimax(WordsData *wordsdata, GameState *gameState,char* difficulty);

//This is the core of the Minimax algorithm. It simulates all possible moves from the current game state and evaluates them recursively.
MinimaxResult minimax(GameState *gameState, int depth, bool isMaximizingPlayer, int min, int max);

//This function evaluates the game state from the perspective of the player. It returns a score based on how favorable the game state is.
int evaluateGameState(GameState *gameState);

//Determines if the game state is a terminal state, i.e., the game is over or a certain condition is met (like no valid moves left).
bool isTerminalState(GameState *gameState);

//Updates the game state with a new move. This is used within the Minimax function to simulate a move.
void updateGameState(GameState *gameState, char startingLetter, char endingLetter);

//Reverts changes made by updateGameState. This is crucial for backtracking in the Minimax algorithm.
void undoGameStateUpdate(GameState *gameState, char startingLetter, char endingLetter);

//Generates all possible moves (letter pairs in your case) from the current game state.
MinimaxResult* generatePossibleMoves(GameState *gameState);

//If generatePossibleMoves dynamically allocates memory for the moves, you'll need a function to free that memory.
void freeGeneratedMoves(MinimaxResult *moves);

#endif // BOT_LOGIC_H