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

//I expect these tests to fail because i bugged my adventure function in dominion.c for assignment2
//alot of these portions will be very similar to the templates provided in class
int main () {
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic
    int players = 2;
    int player1 = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int preCoins;
    int postCoins;

    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    //as in the examples from class:
    //create a gamestate, memcopy to preserve the state, then use the card we will be testing on the state
    struct gameState newState, oldState;

    initializeGame(players, k, randomSeed, &newState);
    memcpy(&oldState, &newState, sizeof(struct gameState));

    //save the number of coins that the player to a variable before card is played
    updateCoins(player1, &newState, 0);
    preCoins = newState.coins;

    cardEffect(adventurer, choice1, choice2, choice3, &newState, handpos, &bonus);
    //save number of coins that the player has to a variable after the card is played
    updateCoins(player1, &newState, 0);
    postCoins = newState.coins;

    //compares number of coins before and after the card is played. if we got
    //2 new treasure cards, this test will pass.
    //coins after should be two greater that coins before
    printf("Testing the adventurer card\n");
    printf("\ntest 1 ->> Treasure increase\n");
    printf("\nPlayer 1 treasure increases by 2\n");
    ass(postCoins, preCoins+2);

    
    printf("\ntest 2 ->> Draw two cards\n");
    printf("\nPlayer 1 adds 2 cards to hand\n");
    ass(newState.handCount[player1],oldState.handCount[player1]+2);

  
    return 0;
}