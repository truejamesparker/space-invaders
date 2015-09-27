/*
 * tank.c
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#include "tank.h"

#define TANK_SCALE SCALE
#define SHIFT_DISTANCE (TANK_SCALE * TANK_WIDTH) / 2

static point_t tank_origin = {.x = SCREEN_WIDTH/2 , .y = (7*SCREEN_HEIGHT)/8};

static missile_t missile;

void tank_init(){

}

void tank_draw(){
	screen_drawSymbol(tank_15x8, tank_origin, tank_size,
					TANK_SCALE, TANK_COLOR);
}

void tank_right() {
	screen_drawSymbol(tank_15x8, tank_origin, tank_size,
						TANK_SCALE, SCREEN_BG_COLOR);
	tank_origin.x += SHIFT_DISTANCE;
}

void tank_left() {
	screen_drawSymbol(tank_15x8, tank_origin, tank_size,
						TANK_SCALE, SCREEN_BG_COLOR);
	tank_origin.x -= SHIFT_DISTANCE;
}

//void tank_fire(){
//	missile_tank_fire();
//}

