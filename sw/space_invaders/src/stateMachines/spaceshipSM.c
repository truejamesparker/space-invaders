#include "spaceshipSM.h"

static uint32_t flashSMPeriods = 0;

volatile static bool locked = false;

// we don't want an spaceship to appear while we are mourning the death
// of the previous spaceship as that would be insensitive
// (as well as make the flashing score position glitch)
volatile static uint16_t mourningPeriodsRemaining = 0;

// ----------------------------------------------------------------------------

void spaceshipSM_tick() {
	// bail if this SM is locked
	if (locked) return;

	// keep track of how many periods have elapsed
	flashSMPeriods++;

	spaceship_move();

	// the score flashing happens slower than the moving.
	if (flashSMPeriods == SPACESHIP_FLASH_REFRESH) {
		bool justKilled = spaceship_flashScore();

		if (justKilled) {
			// enable the mourning period
			mourningPeriodsRemaining = SPACESHIP_MOURNING_PERIOD_LEN;
		}

		// reset the timer
		flashSMPeriods = 0;
	}

	if (!mourningPeriodsRemaining) {

		// Decide when to start spaceship
		uint16_t r = (rand()%(1000))+1; // (rand()%(max-min+1))+min;

		// fancy probability CDF thing
		if (r <= SPACESHIP_START_PROBABILITY) {
			spaceship_start();
		}

	} else {
		// mourn for a period
		mourningPeriodsRemaining--;
	}
}

// ----------------------------------------------------------------------------

void spaceshipSM_lock() {
	locked = true;
}

// ----------------------------------------------------------------------------

void spaceshipSM_unlock() {
	locked = false;
}

// ----------------------------------------------------------------------------
