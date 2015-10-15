#include "tankSM.h"

volatile static uint32_t timeoutSMPeriods = 0;

// ----------------------------------------------------------------------------

void tankSM_tick() {

	// check if tank was hit, or is currently dead
	if (!tank_isAlive()) {
		// time to smoulder (the guises, not be angry)

		// if timeoutSMPeriods is 0, that means this is the first time
		// that this SM knew the tank was dead. Thus, do the housekeeping
		// (freeze the screen, smoulder, etc) and then start a timer
		// to lock everything out for a given length of time
		if (!timeoutSMPeriods) {
			// remove a tank life, will check if zero later
			uint8_t lives = gameScreen_increaseLives(-1);

			// lock the alien block SM and spaceship SM
			alienBlockSM_lock();
			spaceshipSM_lock();

			// deactivate all missiles
			missiles_deactivateAll();

			// remove the spaceship
			spaceship_cancel();

			// check if we need to enter the gameover mode (no more lives)
			if (!lives) {
				gameScreen_printGameOver();
			}

		} else if (timeoutSMPeriods == TANK_KILLED_TIMEOUT) {
			// the timeout has elapsed and we can resume game play

			// unlock the SMs
			alienBlockSM_unlock();
			spaceshipSM_unlock();

			// restart the tank
			tank_init();

			// reset the timer
			timeoutSMPeriods = 0;

			return;

		} else if (timeoutSMPeriods % 2) {
			// every other period, smoulder!
			tank_smoulder();
		}

		timeoutSMPeriods++;

		// skip polling the buttons
		return;
	}

	// Tank direction
	if (pushButtons_leftPressed()) {
		tank_left();
	} else if (pushButtons_rightPressed()) {
		tank_right();
	}

	// Tank shooting
	if (pushButtons_centerPressed()) {
		missiles_tankFire();
	}
}

// ----------------------------------------------------------------------------
