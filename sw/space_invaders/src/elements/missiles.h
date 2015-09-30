#ifndef MISSILES_H_
#define MISSILES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "aliens.h"
#include "tank.h"

#define MISSILE_HEIGHT 		6
#define MISSILE_WIDTH 		3
#define MISSILE_COUNT		4
#define MISSILE_SCALE		1
#define MISSILE_SHIFT 		6
#define MISSILE_COLOR 		SCREEN_COLOR_WHITE
#define TANK_MISSILE		0

typedef struct{
	point_t origin;
	const uint32_t* symbol_r;
	const uint32_t* symbol_l;
	const bool up;
	bool active;
	const symbolsize_t size;
} missile_t;


void missiles_tank_fire();
void missiles_move();
void missiles_alien_fire();


static missile_t missile_array[MISSILE_COUNT] = {
		{
				.symbol_r = missile0_6x6,			// missile type 1
				.symbol_l = missile0_6x6,
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile1_6x6,			// missile type 1
				.symbol_l = missile1_6x6,
				.up = false,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile2_6x6,			// missile type 2
				.symbol_l = missile2_6x6,
				.up = false,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile3r_6x6,
				.symbol_l = missile3l_6x6,
				.up = false,
				.active = false,
				.size = {.w = 6, .h = 6}
		},
};

//-----------------------------------------------------------------------------

void missiles_init();

#endif /* MISSILES_H_ */
