/*The code for my tests is influenced by the code and materials provided
to us in the class resources and examples. The proffessor provided them as
templates to help guide our test writing.. There will be similarities in my code*/
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include "simpleAssert.c"

// runs the tests
int main () {
    int players = 2;
    int player1 = 0;
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic

    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    struct gameState state;
//shuffle should shuffle the deck and have the same amount of cards before and after shuffle
//player's handcount should remain the same before and after shuffle as well.
//I will attempt to shuffle a completely empty deck to see if I find bugs aswell.
    printf("Testing shuffle() function\n");

    initializeGame(players, k, randomSeed, &state);

    printf("\nShuffle max size deck\n");
    printf("Deck size remains equal\n");
    state.deckCount[player1]= MAX_DECK;
    shuffle(player1, &state);
    ass(state.deckCount[player1],MAX_DECK);

    printf("\nShuffle Empty deck\n");
    printf("Deck size remains equal\n");
    state.deckCount[player1]= 0;
    shuffle(player1, &state);
    ass(state.deckCount[player1],0);
    printf("\nShuffle function returns -1 for empty deck\n");
    ass(shuffle(player1, &state),-1);

    printf("\nShuffle 1 Card\n");
    printf("Deck size remains equal\n");
    state.deckCount[player1]= 1;
    shuffle(player1, &state);
    ass(state.deckCount[player1],1);
 
 // randomly chose a deck size for  this one
    printf("\nShuffle 25 Card deck\n");
    printf("Deck size remains equal\n");
    state.deckCount[player1]= 25;
    shuffle(player1, &state);
    ass(state.deckCount[player1],25);

    return 0;
}