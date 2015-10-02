#ifndef TANK_H_
#define TANK_H_

#include "../globals.h"
#include "../screen/screen.h"
#include "missiles.h"

#define TANK_COLOR		SCREEN_COLOR_GREEN

// bitmap related values
#define TANK_WIDTH 		15
#define TANK_HEIGHT 	8
#define TANK_SCALE		2

// how many pixels to shift tank
#define TANK_SHIFT_X	4

// size of tank bitmap
static const symbolsize_t tank_size = {
		.w = TANK_WIDTH,
		.h = TANK_HEIGHT
};

//-----------------------------------------------------------------------------

// Draw the tank in the home position
void tank_init();

// Move the tank
void tank_right();
void tank_left();

// get origin of the tank
point_t tank_get_origin();

#endif /* TANK_H_ */
