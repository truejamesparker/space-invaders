#include "spaceship.h"

// remember which way we are going. Use SCREEN_SHIFT_LEFT or SCREEN_SHIFT_RIGHT
static int8_t shiftDir = 0;

// remember where we are currently
static point_t origin = { .x = 0, .y = SPACESHIP_ORIGIN_Y };

// current random score decisions
uint8_t scoreArray[SPACESHIP_SCORE_MAX_LEN];
uint8_t scoreArrayLength = 0;

// current score flash number
uint8_t flashNumber = 0;
bool flashOn = true; // flashOn == numbers, flashOff == SCREEN_BG_COLOR

// was I just killed?
bool justKilled = false;

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
	screen_drawSymbol(saucer_16x7, origin, spaceshipBitmapSize, SPACESHIP_SCALE, SPACESHIP_COLOR);
}

// ----------------------------------------------------------------------------

void spaceship_move() {
	if (shiftDir) { // first off, are we even moving?
		// check if we are off the screen
		if (origin.x > SPACESHIP_START_RIGHT_X && origin.x < SPACESHIP_START_LEFT_X) {
			shiftDir = 0;
			return;
		}

		audio_play_track(SOUND_SPACESHIP);
		// redraw
		screen_shiftElement(saucer_16x7, origin, spaceshipBitmapSize, (shiftDir*SPACESHIP_SHIFT_X), \
				SPACESHIP_SHIFT_Y, SPACESHIP_SCALE, SPACESHIP_COLOR);

		// shift our origin
		origin.x += (shiftDir*SPACESHIP_SHIFT_X*SPACESHIP_SCALE);
	}
}

//-----------------------------------------------------------------------------

bool spaceship_flashScore() {
	// are we in flash mode?
	if (!flashNumber) return false;

	// Flashing is really just drawing over with alternating colors
	uint32_t color = (flashOn) ? SPACESHIP_SCORE_COLOR : SCREEN_BG_COLOR;

	text_drawNumberString(scoreArray, scoreArrayLength, SPACESHIP_SCORE_MAX_LEN,
			origin, SPACESHIP_SCORE_SCALE, color);

	// next time we alternate color
	flashOn = !flashOn;

	// we did a flash, so decrement how many we have left
	flashNumber--;

	// don't ever say I was killed two calls in a row
	if (justKilled) {
		// so set future justKilled to false
		justKilled = false;

		// but say that this time it was true
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------

void spaceship_kill() {
	// You can't kill a dead spaceship
	if (!shiftDir) return;

	// get rid of the element on the screen and cancel its movement
	spaceship_cancel();

	audio_play_track(SOUND_SPACESHIP_KILLED);
	audio_mute_track(SOUND_SPACESHIP);

	// pick a random score between its bounds
	// (rand()%(max-min+1))+min
	uint32_t r = (rand()%(
					(SPACESHIP_SCORE_MAX/SPACESHIP_SCORE_STEP)
				   -(SPACESHIP_SCORE_MIN/SPACESHIP_SCORE_STEP)+1))
				   +(SPACESHIP_SCORE_MIN/SPACESHIP_SCORE_STEP);

	// calculate a valid score
	uint32_t score = r*SPACESHIP_SCORE_STEP;

	// Increase score!
	gameScreen_increaseScore(score);

	/** set up the score flashing **/
	// Get score info as an array so we can loop through each digit
	text_explodeNumber(score, SPACESHIP_SCORE_MAX_LEN, scoreArray, &scoreArrayLength);

	// Set the flashNumber to twice the flash count (1 flash is both on and off)
	flashNumber = 2*SPACESHIP_SCORE_FLASHES;

	// I was just killed
	justKilled = true;
}

// ----------------------------------------------------------------------------

point_t spaceship_get_origin(){
	return origin;
}

// ----------------------------------------------------------------------------

void spaceship_cancel() {
	// You can't kill a dead spaceship
	if (!shiftDir) return;

	// stop the spaceship from moving
	shiftDir = 0;

	// erase spaceship
	screen_drawSymbol(saucer_16x7, origin, spaceshipBitmapSize, SPACESHIP_SCALE, SCREEN_BG_COLOR);
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

int8_t chooseRandomShiftDirection() {
	// random number between 0 and 1
	int8_t rnd = rand() % 2; // (rand()%(max-min+1))+min
	return (rnd) ? SCREEN_SHIFT_LEFT : SCREEN_SHIFT_RIGHT;
}

// is the spaceship on the screen?
bool spaceship_isActive(){
	return (shiftDir!=0);
}
