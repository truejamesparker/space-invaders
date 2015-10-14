#include "alienBlockSM.h"

// ----------------------------------------------------------------------------

void alienBlockSM_tick() {
	// Always march the aliens
	aliens_march();

	if (aliens_areLiving()) {

		// Decide when to fire missiles
		uint16_t r = (rand()%(100))+1; // (rand()%(max-min+1))+min;

		// fancy probability CDF thing
		if (r <= ALIEN_BLOCK_MISSILE_PROBABILITY) {
			// Get the lowest living aliens
			uint16_t Xs[ALIEN_COL_COUNT];
			uint16_t Ys[ALIEN_COL_COUNT];
			aliens_getLowestAliens(Xs, Ys);

			// The loop makes sure some alien will fire
			bool fired = false;
			while(!fired) {
				// pick a random lowest living alien
				uint16_t x = (rand()%ALIEN_COL_COUNT);

				// fire!
				fired = missiles_alienFire(Xs[x], Ys[x]);
			}
		}

	} else { // the game is over!

	}
}

// ----------------------------------------------------------------------------
