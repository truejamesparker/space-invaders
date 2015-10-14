#include "spaceshipSM.h"

// ----------------------------------------------------------------------------

void spaceshipSM_tick() {
	spaceship_move();

	// Decide when to start spaceship
	uint16_t r = (rand()%(1000))+1; // (rand()%(max-min+1))+min;

	// fancy probability CDF thing
	if (r <= SPACESHIP_START_PROBABILITY) {
		spaceship_start();
	}
}

// ----------------------------------------------------------------------------
