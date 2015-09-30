/*
 * missiles.h
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#ifndef MISSILES_H_
#define MISSILES_H_

#include "../globals.h"
#include "../screen/screen.h"
#include "aliens.h"
#include "tank.h"

#define MISSILE_HEIGHT 		6
#define MISSILE_WIDTH 		6
#define MISSILE_COUNT		4
#define MISSILE_SCALE		1
#define MISSILE_SHIFT 		SCALE * 3
#define MISSILE_COLOR 		SCREEN_COLOR_WHITE
#define TANK_MISSILE		0

typedef struct{
	point_t origin;
	uint32_t* symbol;
	const bool up;
	bool active;
	const symbolsize_t size;
} missile_t;


void missiles_tank_fire();
void missiles_move();
void missiles_alien_fire();


static missile_t missile_array[MISSILE_COUNT] = {
		{
				.symbol = missile0_6x6,			// missile type 1
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol = missile1_6x6,			// missile type 1
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol = missile2_6x6,			// missile type 2
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol = missile3_6x6,
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
};

#endif /* MISSILES_H_ */
