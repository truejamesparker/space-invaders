/*
 * bunkers.c
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */
#include "bunkers.h"

#define BUNKER_START_XOFFSET 24*BUNKER_SCALE

static point_t bunker_origins[4];


//-----------------------------------------------------------------------------

void bunkers_init_origins(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = {
				.x = i * 148 + BUNKER_START_XOFFSET,
				.y = 3*(SCREEN_HEIGHT)/4
		};
		bunker_origins[i] = origin;
	}
}

void bunkers_draw(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = bunker_origins[i];
		screen_drawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
	}

}

void bunker_damage(uint16_t index){

}
