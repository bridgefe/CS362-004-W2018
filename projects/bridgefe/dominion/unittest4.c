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
    int players = 3;
   
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic

    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    struct gameState state;

    printf("\nTesting whoseTurn() function\n");

    initializeGame(players, k, randomSeed, &state);

    printf("\n It is player0's turn\n");
    ass(whoseTurn(&state),0);
    endTurn(&state);

    printf("\n It is player1's turn\n");
    ass(whoseTurn(&state),1);
    endTurn(&state);

    printf("\n It is player2's turn\n");
    ass(whoseTurn(&state),2);
    endTurn(&state);

    return 0;
}