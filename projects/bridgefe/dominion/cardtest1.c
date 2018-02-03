/*The code for my tests is influenced by the code and materials provided
to us in the class resources and examples. The proffessor provided them as
templates to help guide our test writing.. There will be similarities in my code*/
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "simpleAssert.c"

//I expect these tests to fail because i bugged my smithy function in dominion.cfor assignment2
//alot of these portions will be very similar to the templates provided in class
int main () {
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic
    int players = 2;
    int player1 = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;


    // kingdom cards from class example. I stupidly kept doing this part wrong!!
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    //as in the examples from class:
    //create a gamestate, memcopy to preserve the state, then use the card we will be testing on the state
    struct gameState newState, oldState;

    initializeGame(players, k, randomSeed, &newState);
    memcpy(&oldState, &newState, sizeof(struct gameState));


    cardEffect(smithy, choice1, choice2, choice3, &newState, handpos, &bonus);


    printf("Testing the smithy card\n");
    printf("\ntest 1 ->> Draw three cards and discards 1\n");
    printf("Player 1 hand increased by 2 cards\n");
    //the change would only be two because we gain 3 then discard smithy.
    // equaling a growth of 2 cards.
    ass(newState.handCount[player1],oldState.handCount[player1]+3-1);

    printf("\ntest 2 ->> Draw three cards\n");
    printf("Player 1 deck decrease by 3 cards\n");
    ass(newState.deckCount[player1],oldState.deckCount[player1]-3);


    return 0;




}
