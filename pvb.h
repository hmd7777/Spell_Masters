// Player vs Bot game logic
#ifndef PVB_H
#define PVB_H

#define ALPHABET_SIZE 26

int** createWordsEndingInArray(char ***words, int wordCount[ALPHABET_SIZE]);

//Requires:
//Human player's name (player1) and bot's name (bot).
//Effects:
//Returns a boolean value (true or false) indicating whether the human player or the bot starts the game based on the coin flip.
bool coinflipAndWhoStartsPvB(char *player1, char *bot);

//Requires:
//Human player's name (player1).
//Bot difficulty level (input bot_difficulty).
//Effects:
//Initiates and manages a PvB word game.
//Prints game-related messages, including player turns, word choices, and game outcomes.
void PlayerVsBot();

#endif // PVB_H