#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

typedef struct {//stored together in a struct so parameter doesnt get crowded. and looks cleaner.
    char ***words;//3d array that categorizes words with their corresponding starting letters.
    int word_count[26];// array of number of words starting with each letter- as i capitalize/ remove one of the words after someone uses them size here wil decrement.
    int word_count_static[26];//size here will never decremenet/this will beb used for loops/nonstatic array will be used to check if there are no letters starting with certain letter
} WordsData; 
bool isOnlyLetters(const char *str) {//makes sure a word is only letters since the array will be out of bounds if non letters are used.
    for (int i = 0; i < strlen(str); i++) {
        if (!isalpha((unsigned char)str[i])) {
            return false;
        }
    }
    return true;
}
void toLowerCase(char *str) {//self explanotery
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}
bool coinflipAndWhoStarts(char *player1, char *player2){//in this function a coin flip is randomly prompted top p1 or 2, and whoever wins starts the game.
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
void printWordsData(const WordsData *data) {//for debugging purposes and used once in biginning.
    if (!data) {
        printf("WordsData is NULL.\n");
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (data->word_count_static[i] > 0) {
            printf("Letter %c: %d words\n", 'a' + i, data->word_count_static[i]);
            for (int j = 0; j < data->word_count_static[i]; j++) {
                printf("%s ", data->words[i][j]);
            }
            printf("\n\n");
        } else {
            printf("Letter %c: 0 words\n\n", 'a' + i);
        }
    }
}
void capitalizeFirstChar(char *str) {//helper for Find_Verify.
    if (str && *str) {
        *str = toupper((unsigned char)*str);
    }
}

//if a word is found our startegy is to capitalize it so if we find it again it will be capitalized which will indicate that it was already used.
/*
if a word is found our startegy is to capitalize it so if we find it again it will be capitalized which will indicate that it was already used.
case0=word found.
case1=word found but used.
case2=word doesnt exist.
case3=started with wrong letter.
case4=win(the word exists and its last letter has no remaining words in the list)
*/
int Find_Verify(WordsData *wordsData, char *word, char lastLetter, char requiredL){// case0=word found. case1=word found but used. case2=word doesnt exist. case3=started with wrong letter. case4=win
    char ***words = wordsData->words;
    int *word_count = wordsData->word_count;
    char firstLetter=word[0];
    if(requiredL!=' '){//' ' means its the first round.
        if (word[0]!= requiredL){// this is scase 3 done.
            return 3;
        }
    }
    /*if (word_count[lastLetter-'a']==0){//case 4(win)

        return 4;
    }
    */
    for(int i=0;i<wordsData->word_count_static[firstLetter-'a'];i++){
        char *wordOfArr = words[firstLetter-'a'][i];
        //printf("%s\t",wordOfArr);
        if(strcasecmp(word, wordOfArr) == 0){//word is equal to a spell
            if(isupper(wordOfArr[0])){
                 return 1;
            }//word found but is capitalized indicating it was used before
            else if (word_count[lastLetter-'a']==0){//case 4(win)
            return 4;
            }
            else{

                capitalizeFirstChar(words[firstLetter-'a'][i]);
                wordsData->word_count[firstLetter-'a']--;
                return 0;
            }
        }
    }
    return 2;//we have not found the word after looping through all the words that start with the necessary letter.
}

/*
#This function creates an array of 27 indixes(1 for each letter in alphabet).
#At each index another array is created and all the words(in the txt file) starting with the letter of the corresponding index are added to this array.
#finally the 2d array (or 3d if we count the words as array of chars) is returned.
#they are both stored in a struct.
*/
WordsData createWordsArrayFromFile(const char *filename) {//returns a Wordsdata struct, 
     WordsData data = {NULL, {0}, {0}};
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return data;
    }
    char word[26]; // this will be the variable we store the word in each line in

    // Read first line(get how many words)
    int numberOfWords=5;
    if (fgets(word, sizeof(word), file) == NULL) {
    perror("file is empty");
    fclose(file);
    return data;
}

// Convert the first line to an integer
if (sscanf(word, "%d", &numberOfWords) != 1) {
    perror("Failed to read the integer from the file");
    fclose(file);
    return data;
}
    char ***words = (char ***)malloc(26 * sizeof(char **));  // Allocate for 26 letters
    for (int i = 0; i < 26; i++) {
        words[i] = (char **)malloc(numberOfWords * sizeof(char *));  // Allocate for each list of words per letter
        //we are assuming each letter index array could hold maximume numberOfWords.
        for (int j = 0; j < numberOfWords; j++) {
            words[i][j] = NULL;  // Initialize each word pointer to NULL.later we will allocate memory with appropriate quantityfor each word.
        }
    }

    int word_count[26] = {0};
    /*
    The purpose of the word_count array is to keep track of how many 
    words have been stored for each letter of the alphabet in the words 2D array.
    */
    while (fgets(word, sizeof(word), file) != NULL) {
        size_t length = strlen(word);
        if (length > 0 && word[length - 1] == '\n') {
            word[length - 1] = '\0';
            length--;
        }// we here are getting the line, then removing the \n so now word is our word.

        int index = word[0] - 'a';
        if (index >= 0 && index < 26) {
            words[index][word_count[index]] = strdup(word);// here we are dynamically allocating memory for word in appropriate letter array.
            word_count[index]++;
        }
    }
    fclose(file);//done with file and filling array
    /*
    this loop  shrinks the allocated memory to exactly fit the corect number of words for each letter. If there are no words for a letter, it frees the memory entirely.
    */
    for (int i = 0; i < 26; i++) {
    if (word_count[i] > 0) {
        words[i] = realloc(words[i], word_count[i] * sizeof(char *));
    } else {
        // If no words were added for this letter, we free its memory
        free(words[i]);
        words[i] = NULL;
    }
}
    //printWordsArray(words,word_count);
    //printWordCounts(word_count);

    memcpy(data.word_count, word_count, sizeof(word_count));

    // Assigning the words array to the data struct
    data.words = words;
    return data;
}
// Function for player vs. player game
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
    bool p1turn = coinflipAndWhoStarts(player1,player2);//initiate coin flip
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
        printf("You chose Player vs Bot!\nComing soon...");
        
    }

    return 1;
}