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

//alot of these portions will be very similar to the templates provided in class
int main () {
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic
    int players = 2;
    int player1 = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    //as in the examples from class:
    //create a gamestate, memcopy to preserve the state, then use the card we will be testing on the state
    struct gameState newState, oldState;

    initializeGame(players, k, randomSeed, &newState);
    memcpy(&oldState, &newState, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &newState, handpos, &bonus);
    
    //compares number of coins before and after the card is played. if we got
    //2 new treasure cards, this test will pass.
    //coins after should be two greater that coins before
    printf("Testing the great hall card\n");

    //this will fail due to a bug i introduced in assignment 2
    printf("\ntest 1 ->> hand count increases by 1\n");
    printf("\nPlayer 1 hand increase by 1\n");
    //these two should be equal becuase we get a card and then discard a card
    ass(newState.handCount[player1],oldState.handCount[player1]);
    
    //this will fail due to a bug i introduced in assignment2
    printf("\ntest 2 ->> deck size decrease\n");
    printf("\nPlayer 1 deck decreased by 1 card\n");
    ass(newState.deckCount[player1],oldState.deckCount[player1]-1);

    printf("\ntest 3 ->> action increase\n");
    printf("\nPlayer 1 actions increase by 1\n");
    ass(newState.numActions,oldState.numActions+1);


    return 0;
}