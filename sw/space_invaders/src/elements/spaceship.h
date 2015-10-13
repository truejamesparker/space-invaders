#ifndef SPACESHIFT_H_
#define SPACESHIFT_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "../globals.h"
#include "missiles.h"

#define SPACESHIP_COLOR			SCREEN_COLOR_RED
#define SPACESHIP_WIDTH			16
#define SPACESHIP_HEIGHT		7
#define SPACESHIP_ORIGIN_Y		MISSILE_TOP_BUFFER
#define SPACESHIP_SCALE			2

#define SPACESHIP_START_LEFT_X	(USHRT_MAX-(SPACESHIP_WIDTH*SPACESHIP_SCALE))
#define SPACESHIP_START_RIGHT_X	SCREEN_WIDTH
#define SPACESHIP_SHIFT_X		4
#define SPACESHIP_SHIFT_Y		0

// Kick off the spaceship, pick a direction to go
// and start drawing
void spaceship_start();

// shift the spaceship in the direction it is going
void spaceship_move();

#endif /* SPACESHIFT_H_ */
