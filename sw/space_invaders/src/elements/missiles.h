/*
 * missiles.h
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#ifndef MISSILES_H_
#define MISSILES_H_

#include "../globals.h"

#define MISSILE_HEIGHT 		6
#define MISSILE_WIDTH 		6
#define MISSILE_COUNT		4
#define MISSILE_SCALE		SCALE
#define MISSILE_SHIFT 		SCALE * 2

typedef struct{
	uint32_t* symbol;
	const bool up;
	bool active;
	const symbolsize_t size;
} missile_t;


void missiles_tank_fire();

void missiles_alien_fire(uint16_t type);


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
