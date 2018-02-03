/****************************
* Card Test 1
* adventurer card testing
****************************/
#include <stdlib.h>
#include <stdio.h>
#include "my_assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main (int argc, char** argv) {
  //Setup our game state, bruh
  struct gameState *g = newGame();

  //Lets set some other initial values
  int num_players = 2;
  int rand_seed = 69; //Haaaa *cough* yeah, that's right, punk.
  int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

  //Init the game and test that
  int status = initializeGame(num_players, kingdom, rand_seed, g);
  my_assert(status == 0, "Did the game init correctly?");

  //Simulate some nonsense
  int cardChoices = 0;
  buyCard(smithy, g);
  int results = cardEffect(adventurer, cardChoices, cardChoices, cardChoices, g, 0, NULL);
  my_assert(results == 0, "Testing adventurer card...");

  //Annnnnd, we are done. kthxbai<3
  return 0;
}
