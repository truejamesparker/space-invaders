#include "spaceship.h"

// remember which way we are going
// use SCREEN_SHIFT_LEFT or SCREEN_SHIFT_RIGHT
static int8_t shiftDir = 0;

// remember where we are currently
static point_t origin = { .x = 0, .y = SPACESHIP_ORIGIN_Y };

// how big are we?
static symbolsize_t size = { .w = SPACESHIP_WIDTH, .h = SPACESHIP_HEIGHT };

int8_t chooseRandomShiftDirection();

// ----------------------------------------------------------------------------

void spaceship_start() {
	// Make sure we are not already flying through the air
	if (shiftDir) return;

	// set up the shift direction
	shiftDir = chooseRandomShiftDirection();

	// based on the random shift direction, choose an x origin
	origin.x = (shiftDir == SCREEN_SHIFT_RIGHT) ? \
			SPACESHIP_START_LEFT_X : SPACESHIP_START_RIGHT_X;

	// draw it on the screen, it will be hanging off the screen
	screen_drawSymbol(saucer_16x7, origin, size, SPACESHIP_SCALE, SPACESHIP_COLOR);
}

// ----------------------------------------------------------------------------

void spaceship_move() {
	if (shiftDir) { // first off, are we even moving?
		// check if we are off the screen
		if (origin.x > SPACESHIP_START_RIGHT_X && origin.x < SPACESHIP_START_LEFT_X) {
			shiftDir = 0;
			return;
		}

		// redraw
		screen_shiftElement(saucer_16x7, origin, size, (shiftDir*SPACESHIP_SHIFT_X), \
				SPACESHIP_SHIFT_Y, SPACESHIP_SCALE, SPACESHIP_COLOR);

		// shift our origin
		origin.x += (shiftDir*SPACESHIP_SHIFT_X*SPACESHIP_SCALE);

	}
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

int8_t chooseRandomShiftDirection() {
	// random number between 0 and 1
	int8_t rnd = rand() % 2; // (rand()%(max-min))+min
	return (rnd) ? SCREEN_SHIFT_LEFT : SCREEN_SHIFT_RIGHT;
}

// ----------------------------------------------------------------------------
