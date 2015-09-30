/*
 * missiles.c
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */



#include "missiles.h"


void missiles_move(){
	int i;
	for(i=0; i<MISSILE_COUNT; i++){
		missile_t missile = missile_array[i];
		if (missile.active){
			if(missile.up){
				screen_shiftElement(missile.symbol, missile.origin, missile.size,
									0, MISSILE_SHIFT, MISSILE_SCALE, SCREEN_COLOR_WHITE);
				missiles_shift_origin(i, MISSILE_SHIFT * MISSILE_SCALE);
			}
		}
	}
}

void missiles_tank_fire(){
	if (missile_array[TANK_MISSILE].active == false){ // no tank missile on screen
		xil_printf("tank missile arming\n\r");

		missile_array[TANK_MISSILE].active = true;
		point_t tank_gun_origin = tank_get_origin();
		tank_gun_origin.x += (TANK_WIDTH*TANK_SCALE)/2 - 3;
		tank_gun_origin.y -= MISSILE_HEIGHT*MISSILE_SCALE;
		xil_printf("x: %d, y: %d\n\r", tank_gun_origin.x, tank_gun_origin.y);
		missile_array[TANK_MISSILE].origin = tank_gun_origin;
		screen_drawSymbol(missile_array[TANK_MISSILE].symbol,
				missile_array[TANK_MISSILE].origin, missile_array[TANK_MISSILE].size,
				MISSILE_SCALE, SCREEN_COLOR_WHITE);
	}
}

void missiles_alien_fire(){
	int i;
	for(i=1; i<4; i++){
		missile_t alien_missile = missile_array[i];
		if (alien_missile.active==false){
			screen_drawSymbol(alien_missile.symbol, alien_missile.origin,
					alien_missile.size, MISSILE_SCALE, MISSILE_COLOR);
			missile_array[i].active = true;
			missiles_set_alien_origin(i);
			break;
		}
	}
}

void missiles_shift_origin(uint16_t index, uint16_t shift){
	int16_t dir = missile_array[index].up ? 1 : -1;
	missile_array[index].origin.y += dir*shift;
}

void missiles_set_alien_origin(uint16_t index){

}
