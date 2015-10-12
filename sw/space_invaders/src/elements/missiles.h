#ifndef MISSILES_H_
#define MISSILES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "aliens.h"
#include "tank.h"
#include "bunkers.h"

// missile size info
#define MISSILE_HEIGHT 		7
#define MISSILE_WIDTH 		3
#define MISSILE_COUNT		4
#define MISSILE_SCALE		1 // how much should we scale?
#define MISSILE_SHIFT 		8 // how many pixels shold we move by every time?

// color def
#define MISSILE_COLOR 		SCREEN_COLOR_WHITE

// index of tank missile in missile array
#define TANK_MISSILE		0


// missile struct definition
typedef struct{
	point_t origin;				// current location of missile
	const uint32_t* symbol_r;	// alternating missile bitmap
	const uint32_t* symbol_l;	// alternating missile bitmap
	const bool up; 				// missile direction
	bool active;				// missle in flight?
	const symbolsize_t size;	// size of missile bitmap
} missile_t;

// function delcarations
void missiles_tank_fire();
void missiles_move();
void missiles_alien_fire();


// array of all missile types
static missile_t missile_array[MISSILE_COUNT] = {
		{
				.symbol_r = missile0_3x7,			// missile type 1 (tank)
				.symbol_l = missile0_3x7,
				.up = true,
				.active = false,
				.size = {.w = 3, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile1_3x7,			// missile type 2 (alien)
 				.symbol_l = missile1_3x7,
				.up = false,
				.active = false,
				.size = {.w = 3, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile2r_3x7,			// missile type 3 (alien)
				.symbol_l = missile2l_3x7,
				.up = false,
				.active = false,
				.size = {.w = 3, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile3r_6x7,			// missile type 4 (alien)
				.symbol_l = missile3l_6x7,
				.up = false,
				.active = false,
				.size = {.w = 6, .h = MISSILE_HEIGHT}
		},
};

//-----------------------------------------------------------------------------

void missiles_init();

#endif /* MISSILES_H_ */
