#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// fail counter variables
int cardEffectFails = 0, shuffleFails = 0, drawCardFails = 0, handCountFails = 0, treasureCountFails = 0;

// function to check the adventurerCard
void checkAdventurerCard(int p, struct gameState *post) {
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int postCoins= 0;
    int preCoins = 0;
    int temphand[MAX_HAND];
    int drawntreasure = 0;
    // game state variable to manually act on the functions actions
    struct gameState pre;
    int cardDrawn;
    int z = 0;
    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));

 //check treasures before card is played
    updateCoins(p, &pre, 0);
    preCoins = pre.coins;
    
    //play adventurer
    if (cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus)) {
        cardEffectFails++;
    }
    //for these tests we place the actions of the function int the test and check for failure of any aspects.
    //
    while(drawntreasure < 2) {
            if (pre.deckCount[p] < 1) {//if the deck is empty we need to shuffle discard and add to deck
                  
                    if (shuffle(p, &pre) == -1 && pre.deckCount[p] >= 1) {
                      shuffleFails++;
                    }
            }
            if (drawCard(p, &pre) == -1 && pre.deckCount[p] != 0) {
                drawCardFails++;
            }
            cardDrawn = pre.hand[p][pre.handCount[p] - 1];//top card of hand is most recently drawn card.

            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                    drawntreasure++;
            else{
                    temphand[z] = cardDrawn;
                    pre.handCount[p]--; //this should just remove the top card (the most recently drawn one).
                    z++;
            }
    }
    while(z - 1 >= 0) {
            pre.discard[p][pre.discardCount[p]++] = temphand[z - 1]; // discard all cards in play that have been drawn
            z = z - 1;
    }

    updateCoins(p, post, 0);
    postCoins = post->coins;

    

    // check if treasures match up
    //it will not because of a bug i put in dominion.c
    if (postCoins != preCoins+2) {// this is plus2 because adventurer trys to get 2 treasure cards when played
      treasureCountFails++;
    }


    // handcount should not match up. I put a bug in dominion.c
    if (!(post->handCount[p] == pre.handCount[p]+1)) {
        handCountFails++;
    }
}

int main () {
    printf("***** RANDOM TESTING OF ADVENTURER CARD *****\n");
    int treasures[] = {copper,silver,gold}; //array coin types for use by the adventurer card
    int i, n, player;
    struct gameState testState;
    srand(time(NULL));

    // randomly initialized the game state
    for (n = 0; n < 16; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&testState)[i] = floor(Random() * 256);
      }

      
      // randomly select appropriate values
      // this time the deck must have atleast enought to draw
        player = floor(Random() * MAX_PLAYERS);
        testState.deckCount[player] = floor(Random() * ((MAX_DECK - 3) + 1) + 3);
        testState.discardCount[player] = 0 ; //nothing in the discard pile
        testState.handCount[player] = floor(Random() * MAX_HAND);
        testState.playedCardCount = floor(Random() * (MAX_DECK-1)); //must not forget this unless you love seg faults
        testState.whoseTurn = player;

      //put a couple treasures in the deck so that there will always be something to draw
      for (i = 0; i < 3; i++) {
        testState.deck[player][i] = treasures[rand() % 2];
      }
   
      checkAdventurerCard(player, &testState);
    }

    if (cardEffectFails == 0 && shuffleFails==0 && drawCardFails ==0 && handCountFails == 0 && treasureCountFails == 0) {
        printf ("ALL TESTS OK\n");
    }
    else {
        printf("\nWHAT FAILED??\n");

        printf("shuffle() failed: %d\n",shuffleFails);
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("Treasure Count did not gain 2: %d\n",treasureCountFails);
        printf("pre and post hand count do not match: %d\n",handCountFails);
    }
    return 0;
}