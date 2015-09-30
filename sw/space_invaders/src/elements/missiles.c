#include "missiles.h"

static bool wobble;

void missiles_shift_origin(uint16_t index);
void missiles_set_alien_origin(uint16_t index);

//-----------------------------------------------------------------------------

void missiles_init() {
	uint8_t i;

	for (i=0; i<MISSILE_COUNT; i++) {
		// Turn off all missiles
		missile_array[i].active = false;
	}
}

//-----------------------------------------------------------------------------

void missiles_move(){
	uint8_t i;
	wobble = !wobble;
	for(i=0; i<MISSILE_COUNT; i++){
		missile_t missile = missile_array[i];
		if (missile.active){
			int8_t dir = missile.up ? -1 : 1;
			const uint32_t* symbol = wobble ? missile.symbol_r : missile.symbol_l;
			screen_shiftElement(symbol, missile.origin, missile.size,
								0, dir*MISSILE_SHIFT, MISSILE_SCALE, MISSILE_COLOR);
			missiles_shift_origin(i);
		}
	}
}

//-----------------------------------------------------------------------------

void missiles_tank_fire(){
	missile_t *missile = &missile_array[TANK_MISSILE];

	if (!missile->active){ // no tank missile on screen

		missile->active = true;
		point_t tank_gun_origin = tank_get_origin();
		tank_gun_origin.x += (TANK_WIDTH*TANK_SCALE)/2 - (missile->size.w*MISSILE_SCALE)/2;
		tank_gun_origin.y -= MISSILE_HEIGHT*MISSILE_SCALE;

		missile->origin = tank_gun_origin;
		screen_drawSymbol(missile->symbol_r, missile->origin, missile->size,
				MISSILE_SCALE, SCREEN_COLOR_WHITE);
	}
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

void missiles_shift_origin(uint16_t index) {
	int16_t dir = missile_array[index].up ? -1 : 1;
	missile_array[index].origin.y += dir*MISSILE_SHIFT*MISSILE_SCALE;
}

//-----------------------------------------------------------------------------

void missiles_set_alien_origin(uint16_t index) {
	uint16_t r = rand();
	point_t alien_point = alien_getAlienOrigin(r%10, 4);
	alien_point.y += (ALIEN_HEIGHT * ALIEN_SCALE);
	alien_point.x += (ALIEN_WIDTH * ALIEN_SCALE)/2;
	missile_array[index].origin = alien_point;
}


