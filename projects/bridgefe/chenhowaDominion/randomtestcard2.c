#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//These random tests were inspired and influenced by the provided example of testDrawCard.c 
//there will be similarities in the code. 

//global failure of tests tracking
int cardEffectFails=0, drawCardFails=0, handCountFails=0, discardCardFails=0, numActionsFails=0;

// function to check the smithyCard
void checkVillageCard(int p, struct gameState *post) {

    struct gameState pre;

    memcpy(&pre,post,sizeof(struct gameState));
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    // call the card effect function with the village card
    if(cardEffect(village, choice1, choice2, choice3, post, handpos, &bonus)){
    	cardEffectFails++;
    }


    
    // check if any drawcard failed
    if (drawCard(p,&pre) == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }

    if(!(post->numActions == pre.numActions+2)){
        numActionsFails++;
    }

    // call discardCard
    if(discardCard(0, p, &pre, 0)){
        discardCardFails++;
    }


    
    if (!(post->handCount[p] == pre.handCount[p])) {
        handCountFails++;
        //////////////////////////////////////////////////////////
    }
}

int main () {
    printf("***** RANDOM TESTING OF VILLAGE CARD *****\n");
    //this one works fine because i implemented no buggerrooonies!!!!
   
    int i, n, player;
    struct gameState testState;
    srand(time(NULL));

    // randomly initialized the game state as seen in testDrawCard.c
    for (n = 0; n < 5000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&testState)[i] = floor(Random() * 256);
        }
        // randomly select appropriate values
        player = floor(Random() * MAX_PLAYERS);
        testState.deckCount[player] = floor(Random() * MAX_DECK);
        testState.discardCount[player] = floor(Random() * MAX_DECK);
        testState.handCount[player] = floor(Random() * MAX_HAND);
        testState.playedCardCount = floor(Random() * (MAX_DECK-1)); //must not forget this unless you love seg faults
        testState.whoseTurn = player;
        // call the check function
        checkVillageCard(player,&testState);
    }

    if(cardEffectFails ==0 && drawCardFails ==0 && handCountFails == 0 && numActionsFails == 0 && discardCardFails == 0)
    {
 		printf ("ALL TESTS OK\n");
 	}
 	else{
 		printf("\nWHAT FAILED??\n");
     
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("Handcount failed: %d\n",handCountFails);
        printf("numActions increase failed: %d\n",numActionsFails);
        printf("discardCard() failed: %d \n", discardCardFails);
 	}
    
    return 0;
}