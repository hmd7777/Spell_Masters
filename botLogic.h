// Player vs Bot game logic
#ifndef BOT_LOGIC_H
#define BOT_LOGIC_H

#define MAX_DEPTH 10
#define INFINITY 10000 // or use <limits.h> for INT_MAX

#include "utilities.h"


// Function prototypes
char* chooseWordWithMinimax(WordsData *wordsdata, GameState *gameState);
/*
int minimax(GameState *gameState, int depth, bool isMaximizingPlayer, char *bestWord);
int evaluateGameState(GameState *gameState);
void updateGameState(GameState *gameState);
void undoGameStateUpdate(GameState *gameState);
bool isTerminalState(GameState *gameState);
*/
#endif // BOT_LOGIC_H