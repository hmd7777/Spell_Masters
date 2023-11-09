#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#include "utilities.h"
#include "pvp.h"
#include "pvb.h"

// Function for player vs. player game
int main() {
    
    printf("Welcome, Spell Master!\n\n");
    printf("Game description: A two-player wizard duel where strategy is key. Cast spells, ensuring they start with the last letter of your opponent's previous choice, while avoiding repeats. Prepare for magical battles!\n\n");
// Convert a string to lowercase

    char choice[10];

    do {
        printf("Please choose a game mode:\n");
        printf("1-PvP (Player vs Player)\n");
        printf("2-PvB (Player vs Bot)\n");
        printf("Enter your choice(Case insensetive): ");
        scanf("%s", choice);

        toLowerCase(choice);

    } while (strcmp(choice, "pvp") != 0 && strcmp(choice, "pvb") != 0);

    if (strcmp(choice, "pvp") == 0) {
        printf("You chose Player vs Player!\n");
        PlayerVsPlayer();
    } else {
        printf("You chose Player vs Bot!\n");
        PlayerVsBot();
    }

    return 1;
}