// Player vs Player game logic
#ifndef PVP_H
#define PVP_H
#include <stdbool.h>

//Requires:
//Two player names (player1 and player2) as input strings
//Effects:
//Returns a boolean value (true or false) indicating whether Player 1 or Player 2 starts the game based on the coin flip.
bool coinflipAndWhoStartsPvP(char *player1, char *player2);

//Requires:
//Two player names (player1 and player2) as input strings.
//A text file containing a list of words.
//Effects:
//Initiates and manages a PvP word game.
//Prints game-related messages, including player turns, word choices, and game outcomes.
void PlayerVsPlayer();


#endif // PVP_H
