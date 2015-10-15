#ifndef SPACESHIFT_H_
#define SPACESHIFT_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../globals.h"
#include "../text/text.h"
#include "missiles.h"

#define SPACESHIP_COLOR			SCREEN_COLOR_RED
#define SPACESHIP_WIDTH			16
#define SPACESHIP_HEIGHT		7
#define SPACESHIP_ORIGIN_Y		MISSILE_TOP_BUFFER
#define SPACESHIP_SCALE			2

#define SPACESHIP_START_LEFT_X	(USHRT_MAX-(SPACESHIP_WIDTH*SPACESHIP_SCALE))
#define SPACESHIP_START_RIGHT_X	SCREEN_WIDTH
#define SPACESHIP_SHIFT_X		1
#define SPACESHIP_SHIFT_Y		0

// scoring
#define SPACESHIP_SCORE_COLOR		SCREEN_COLOR_WHITE
#define SPACESHIP_SCORE_SCALE		2
#define SPACESHIP_SCORE_FLASHES		3
#define SPACESHIP_SCORE_MAX_LEN		3
#define SPACESHIP_SCORE_MAX			350
#define SPACESHIP_SCORE_MIN			50
#define SPACESHIP_SCORE_STEP		50

// Kick off the spaceship, pick a direction to go and start drawing
void spaceship_start();

// shift the spaceship in the direction it is going
void spaceship_move();

// kill the spaceship, flashing the points in its place
void spaceship_kill();

// flash the score on and off after a spaceship kill.
// returns true if this is the alien was just killed
bool spaceship_flashScore();

// get the current position of the spaceship
point_t spaceship_get_origin();

// return if spaceship is on the screen
bool spaceship_isActive();

#endif /* SPACESHIFT_H_ */
