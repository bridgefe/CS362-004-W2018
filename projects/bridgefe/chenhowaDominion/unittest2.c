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
    srand(time(NULL)); //getting random with it
    int randomSeed = rand(); //my random seed pic

    // kingdom cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    struct gameState state, state2;

    printf("Testing isGameOver() function\n");

    initializeGame(players, k, randomSeed, &state);

    state.supplyCount[province] = 1;

    state.supplyCount[0] = 0;
    state.supplyCount[1] = 0;
    state.supplyCount[2] = 0;

    printf("\nfull province, empty supplies\n");
    ass(isGameOver(&state),1); //game over

    state.supplyCount[province] = 0;

    state.supplyCount[0] = 1;
    state.supplyCount[1] = 1;
    state.supplyCount[2] = 1;

    printf("\nno provinces, three empty supplies\n");
    ass(isGameOver(&state),1); // game over

//initialized another game so that previous variable changes didnt mess with results.
    initializeGame(players, k, randomSeed, &state2);

    state2.supplyCount[province] = 0;

    printf("\nNo provinces\n");
    ass(isGameOver(&state2),1); //game over

    state.supplyCount[0] = 0;
    state.supplyCount[1] = 0;
    state.supplyCount[2] = 0;
    

    printf("\nThree supplies empty\n");
    ass(isGameOver(&state2),1); //game over

    state2.supplyCount[province] = 1;

    state2.supplyCount[0] = 1;
    state2.supplyCount[1] = 1;
    state2.supplyCount[2] = 1;

    printf("\nfull provinces. Full supply count\n");
    ass(isGameOver(&state2),0); //not game over

    return 0;
}