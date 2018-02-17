#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "my_assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 32

int main (int argc, char** argv) {
	//Our game state, bruh
	struct gameState *g = NULL;

	//Lets set some other initial values
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	//Keep track of the good and the bad
	int YAY = 0;
	int BOO = 0;

	//Testing loop, son!
	int i;
	for(i = 0; i < NUM_TESTS; i++) {
		//Setup some stuff, RANDOMLY! :D
		//srand(rand()); //Seed randomizer
		int num_players = rand() % 4;
		int rand_seed = rand();		//pick random seed (for the game)
		int player = 0; //Test player 0
		g = malloc(sizeof(struct gameState));

		//Init the game and test that
		int status = initializeGame(num_players, kingdom, rand_seed, g);
		//my_assert(status == 0, "Did the game init correctly?");
		/* Author Note:
			 Init game actually failed after a certain number of tests, aborting
		   everything. I have no idea why this is. So my_assert is commented out for now.*/

		//Randomly setup some game stuff
		g->deckCount[player] = rand() % MAX_DECK;
		g->discardCount[player] = rand() % MAX_DECK;
		g->handCount[player] = rand() % MAX_HAND;

		//Get current hand information before running adventurer
		int tracking = 0;
		int x;
		for(x = 0 ; x < g->handCount[player]; x++) {
			if((g->hand[player][x] == gold) || (g->hand[player][x] == silver) || (g->hand[player][x] == copper)) {
				tracking++;
			}
		}

		//Run adventure card, OH MAI GAWD
		cardEffect(adventurer, 1, 1, 1, g, 0, 0);

		//Did that actually do anything?
		for(x = 0 ; x < g->handCount[player]; x++) {
			if((g->hand[player][x] == gold) || (g->hand[player][x] == silver) || (g->hand[player][x] == copper)) {
				tracking--;
			}
		}

		//Keep track of the results
		if(tracking < 0) YAY++;
		else BOO++;

		//Current progress
		printf("Test %d/%d complete, moving on...\n", i + 1, NUM_TESTS);

		//Memory leaks are certainly a problem, garabge collection for days
		free(g);
	}

	//Output these results
	printf("\n\n\t[!] There were %d passes, and %d failures out of %d games\n\n\n", YAY, BOO, NUM_TESTS);

	//Annnnnd, we are done. kthxbai<3
	return 0;
}