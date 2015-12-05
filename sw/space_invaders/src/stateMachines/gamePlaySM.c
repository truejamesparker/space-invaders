#include "gamePlaySM.h"

volatile static bool waitForButton = false;
volatile static bool gamePaused = false;

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
			controllerSM_unlock();

			// restart the tank
			tank_init();
		}
	}

	// If slideSwitch 0 is on, then pause the game.
	if (slideSwitches_isOn(SW_PAUSE)) gamePlaySM_pauseGame();
	else gamePlaySM_resumeGame();

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

void gamePlaySM_pauseGame() {
	if (gamePaused) return;
	xil_printf("Game Paused!\r\n");
	alienBlockSM_lock();
	spaceshipSM_lock();
	tankSM_lock();
	controllerSM_lock();

	gamePaused = true;
}

// ----------------------------------------------------------------------------

void gamePlaySM_resumeGame() {
	if (!gamePaused) return;
	xil_printf("Unpaused!\r\n");
	alienBlockSM_unlock();
	spaceshipSM_unlock();
	tankSM_unlock();
	controllerSM_unlock();

	gamePaused = false;
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void startNewLevel() {
	// redraw the aliens, top off lives
	aliens_cleanupKills();
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
	controllerSM_lock();

	// lock the alien block SM and spaceship SM
	alienBlockSM_lock();
	spaceshipSM_lock();
}

// ----------------------------------------------------------------------------
