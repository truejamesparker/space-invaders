/*
 * tank.h
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#ifndef TANK_H_
#define TANK_H_

#include "../globals.h"
#include "../screen/screen.h"
#include "missiles.h"

#define TANK_COLOR	0x32CD32
#define TANK_WIDTH 	15
#define TANK_HEIGHT 8
#define TANK_SCALE 	SCALE
#define TANK_SHIFT  3

static const symbolsize_t tank_size= {
		.w = TANK_WIDTH,
		.h = TANK_HEIGHT
};


void tank_init();

void tank_draw();

void tank_right();

void tank_left();

point_t tank_get_origin();

#endif /* TANK_H_ */
