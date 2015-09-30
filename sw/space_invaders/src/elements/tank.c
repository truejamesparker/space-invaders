/*
 * tank.c
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#include "tank.h"


//#define SHIFT_DISTANCE (TANK_SCALE * TANK_WIDTH) / 2

static point_t tank_origin = {.x = SCREEN_WIDTH/2 , .y = (7*SCREEN_HEIGHT)/8};

static missile_t missile;

void tank_init(){

}

point_t tank_get_origin(){
	return tank_origin;
}

void tank_draw(){
	screen_drawSymbol(tank_15x8, tank_origin, tank_size,
					TANK_SCALE, TANK_COLOR);
}

void tank_right() {
	screen_shiftElement(tank_15x8, tank_origin, tank_size,
			TANK_SHIFT, 0, TANK_SCALE, SCREEN_COLOR_GREEN);
	tank_origin.x += TANK_SHIFT;
}

void tank_left() {
	screen_shiftElement(tank_15x8, tank_origin, tank_size,
				-TANK_SHIFT, 0, TANK_SCALE, SCREEN_COLOR_GREEN);
	tank_origin.x -= TANK_SHIFT;
}

//void tank_fire(){
//	missile_tank_fire();
//}

