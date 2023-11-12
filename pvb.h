// Player vs Bot game logic
#ifndef PVB_H
#define PVB_H

#define MAX_WORDS_PER_LETTER 25 // Adjust this based on your needs
#define ALPHABET_SIZE 26

int** createWordsEndingInArray(char ***words, int wordCount[ALPHABET_SIZE]);
bool coinflipAndWhoStartsPvB(char *player1, char *bot);
void PlayerVsBot();

#endif // PVB_H