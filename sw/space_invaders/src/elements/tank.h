#ifndef TANK_H_
#define TANK_H_

#include <stdint.h>
#include <stdbool.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "missiles.h"
#include "bunkers.h"

#define TANK_COLOR		SCREEN_COLOR_GREEN

// bitmap related values
#define TANK_SCALE		2
#define TANK_WIDTH 		(BITMAP_TANK_WIDTH*TANK_SCALE)
#define TANK_HEIGHT 	(BITMAP_TANK_HEIGHT*TANK_SCALE)

#define TANK_GUN_HEIGHT (3*TANK_SCALE)

// how many pixels to shift tank
#define TANK_SHIFT_X	4

//-----------------------------------------------------------------------------

// Draw the tank in the home position
void tank_init();

// Move the tank
void tank_right();
void tank_left();

// set the tank to dead
void tank_kill();

// the world can ask if the tank is alive
bool tank_isAlive();

// get origin of the tank
point_t tank_get_origin();

// switch between the smouldering guises
void tank_smoulder();

#endif /* TANK_H_ */
