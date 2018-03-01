#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "simpleAssert.c"

int main () {
    int numbPlayers = 2;
    int player1 = 0;
    int player2 = 0;

    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;
    struct gameState state, stateOriginal;

    
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOriginal,23,sizeof(struct gameState));

    // create the game state
    initializeGame(numbPlayers, k, seed, &state);

    // copy it to preserve it
    memcpy(&stateOriginal, &state, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("Testing the council room card\n");

    printf("\ntest1 >> Player1 gains 4 cards\n");
    ass(state.handCount[player1],stateOriginal.handCount[player1]+3);

    printf("\ntest2 >> Player1 gains 4 cards from his own pile\n");
    ass(state.deckCount[player1],stateOriginal.deckCount[player1]-4);

    printf("\ntest3 >> number of buys increments\n");
    ass(state.numBuys,stateOriginal.numBuys+1);

    printf("\ntest4 >> No change to victory cards: prov, duch, estate\n");
    ass(state.supplyCount[province],stateOriginal.supplyCount[province]);
    ass(state.supplyCount[duchy],stateOriginal.supplyCount[duchy]);
    ass(state.supplyCount[estate],stateOriginal.supplyCount[estate]);

    
    printf("\ntest5 >> Player2 gains a card\n");
    ass(state.handCount[player2],stateOriginal.handCount[player2]+1);
    printf("\ntest6 >> Player2 gains a card from his own deck\n");
    ass(state.deckCount[player2],stateOriginal.deckCount[player2]-1);

    return 0;
}