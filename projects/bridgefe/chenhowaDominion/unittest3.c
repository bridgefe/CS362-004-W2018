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
    int handPos = 0;
    int trashFlag = 0;

    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
   // srand(time(NULL)); //getting random with it
   // int randomSeed = rand(); //my random seed pic
    struct gameState state;

    //max starting hand of 5 cards
    initializeGame(players, k, 5, &state);

    printf("\nTesting numHandCards() function\n");

    printf("\nTest wether we have 5 starting cards in hand\n");
    ass(numHandCards(&state),5);

    drawCard(player1,&state);

    printf("\nDraw card, now have 6 cards\n");
    ass(numHandCards(&state),6);

    discardCard(handPos, player1, &state, trashFlag);

    printf("\nDiscard card, back to 5 cards\n");
    ass(numHandCards(&state),5);

    discardCard(handPos, player1, &state, trashFlag);
    discardCard(handPos, player1, &state, trashFlag);
    discardCard(handPos, player1, &state, trashFlag);
    discardCard(handPos, player1, &state, trashFlag);
    discardCard(handPos, player1, &state, trashFlag);

    printf("\nDiscard all, now have zero cards\n");
    ass(numHandCards(&state),0);

    return 0;
}