/*
 * missiles.c
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */



#include "missiles.h"
static bool wobble;

void missiles_move(){
	int i;
	wobble = !wobble;
	for(i=0; i<MISSILE_COUNT; i++){
		missile_t missile = missile_array[i];
		if (missile.active){
			int16_t dir = missile.up ? -1 : 1;
			uint32_t* symbol = wobble ? missile.symbol_r : missile.symbol_l;
			screen_shiftElement(symbol, missile.origin, missile.size,
								0, dir*MISSILE_SHIFT, MISSILE_SCALE, SCREEN_COLOR_WHITE);
			missiles_shift_origin(i);
		}
	}
}

void missiles_tank_fire(){
	if (missile_array[TANK_MISSILE].active == false){ // no tank missile on screen

		missile_array[TANK_MISSILE].active = true;
		point_t tank_gun_origin = tank_get_origin();
		tank_gun_origin.x += (TANK_WIDTH*TANK_SCALE)/2 - (missile_array[TANK_MISSILE].size.w*MISSILE_SCALE)/2;
		tank_gun_origin.y -= MISSILE_HEIGHT*MISSILE_SCALE;

		missile_array[TANK_MISSILE].origin = tank_gun_origin;
		screen_drawSymbol(missile_array[TANK_MISSILE].symbol_r,
				missile_array[TANK_MISSILE].origin, missile_array[TANK_MISSILE].size,
				MISSILE_SCALE, SCREEN_COLOR_WHITE);
	}
}

void missiles_alien_fire(){
	int i;
	for(i=1; i<4; i++){
		if (missile_array[i].active==false){
			missiles_set_alien_origin(i);
			screen_drawSymbol(missile_array[i].symbol_r, missile_array[i].origin,
					missile_array[i].size, MISSILE_SCALE, MISSILE_COLOR);
			missile_array[i].active = true;
			break;
		}
	}
}

void missiles_shift_origin(uint16_t index){
	int16_t dir = missile_array[index].up ? -1 : 1;
	missile_array[index].origin.y += dir*MISSILE_SHIFT*MISSILE_SCALE;
}

void missiles_set_alien_origin(uint16_t index){
	uint16_t r = rand();
	point_t alien_point = alien_getAlienOrigin(r%10, 4);
	alien_point.y += (ALIEN_HEIGHT * ALIEN_SCALE);
	alien_point.x += (ALIEN_WIDTH * ALIEN_SCALE)/2;
	missile_array[index].origin = alien_point;
}


