#include "gamePlaySM.h"

volatile static bool waitForButton = false;

void startNewLevel();
void gameOver();

// ----------------------------------------------------------------------------

void gamePlaySM_tick() {
	// If I'm in game over state, just wait here until the user presses a btn
	if (waitForButton) {
		if (pushButtons_anyPressed()) {
			waitForButton = false;

			// reset screen
			screen_clear();
			gameScreen_init();
			aliens_init();
			bunkers_init();

			// restart the march speed
			alienBlockSM_marchSlow();

			// unlock SMs and such
			alienBlockSM_unlock();
			spaceshipSM_unlock();
			tankSM_unlock();

			// restart the tank
			tank_init();
		}
	}

	// here I need to check different game play states
	// There are three different game play events:
	// 1. I killed all the aliens, so start a new level
	// 2. I lost all my lives, so go to Gameover
	// 3. Aliens dropped below the bunkers, so go to Gameover

	// check if aliens are all gone
	if (!aliens_areLiving()) {
		startNewLevel();
	}

	// check if I have no more lives or if aliens are below bunkers
	if (!gameScreen_getTankLives() || aliens_belowBunkers()) {
		gameOver();
	}
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void startNewLevel() {
	// redraw the aliens, top off lives
	aliens_init();
	gameScreen_increaseLives(LIVES_MAX);

	// restart the march speed
	alienBlockSM_marchSlow();
}

// ----------------------------------------------------------------------------

void gameOver() {
	gameScreen_printGameOver();
	waitForButton = true;

	// this will lock the tank so you can't move it,
	// and also keep it smouldering during the "GAME OVER" screen
	tankSM_lock();

	// lock the alien block SM and spaceship SM
	alienBlockSM_lock();
	spaceshipSM_lock();
}

// ----------------------------------------------------------------------------
