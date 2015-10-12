#include "missiles.h"

// some missiles "wiggle" as they
// move across the screen. This global
// defines which state we're in
static bool wobble;

// function declarations
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

// update the position of all missiles
void missiles_move(){
	uint8_t i;
	wobble = !wobble;
	for(i=0; i<MISSILE_COUNT; i++){
		missile_t missile = missile_array[i];
		if (missile.active) {
			int8_t dir = missile.up ? -1 : 1;
			const uint32_t* symbol = wobble ? missile.symbol_r : missile.symbol_l;

			// shift it on the scrren
			screen_shiftElement(symbol, missile.origin, missile.size,
								0, dir*MISSILE_SHIFT, MISSILE_SCALE, MISSILE_COLOR);

			// no update the origin in the missile struct
			missiles_shift_origin(i);
		}
	}
}

//-----------------------------------------------------------------------------

// fire the tank missile
void missiles_tank_fire(){
	missile_t *missile = &missile_array[TANK_MISSILE];

	if (!missile->active){ // no tank missile on screen

		missile->active = true; // set status to active
		point_t tank_gun_origin = tank_get_origin(); // get tank location
		// compute the cooridnates of the cannon
		tank_gun_origin.x += (TANK_WIDTH*TANK_SCALE)/2 - (missile->size.w*MISSILE_SCALE)/2;
		tank_gun_origin.y -= MISSILE_HEIGHT*MISSILE_SCALE;

		missile->origin = tank_gun_origin;
		// draw the missile at the tip of the tank's cannon
		screen_drawSymbol(missile->symbol_r, missile->origin, missile->size,
				MISSILE_SCALE, SCREEN_COLOR_WHITE);
	}
}

//-----------------------------------------------------------------------------

// initiate an alien missile
void missiles_alien_fire(){
	int i;
	for(i=1; i<MISSILE_COUNT; i++){
		// find a missile that is not already active
		if (!missile_array[i].active) {
			// set the initial position of the missile to the center
			// of a random alien in the bottom row
			missiles_set_alien_origin(i);

			// draw the symbol to the screen
			screen_drawSymbol(missile_array[i].symbol_r, missile_array[i].origin,
					missile_array[i].size, MISSILE_SCALE, MISSILE_COLOR);

			missile_array[i].active = true; // set missile status to active

			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// update the missile origin (shift it in the y direction)
void missiles_shift_origin(uint16_t index) {
	missile_t* missile = &(missile_array[index]);
	int8_t dir = (missile->up) ? -1 : 1;
	missile->origin.y += dir*MISSILE_SHIFT*MISSILE_SCALE;
	if(missile->origin.y > (SCREEN_HEIGHT-SCREEN_EDGE_BUFFER) || missile->origin.y < SCREEN_EDGE_BUFFER){
		missile->active = false;
	}
}

//-----------------------------------------------------------------------------

// set the initial position of the missile to the center
// of a random alien in the bottom row
void missiles_set_alien_origin(uint16_t index) {
	uint16_t r = rand();
	// todo: change this the be the bottom aliens
	// NOT just the last row (this will cause a bug later)
	point_t alien_point = alien_get_origin(r%10, 4);
	alien_point.y += (ALIEN_HEIGHT * ALIEN_SCALE);
	alien_point.x += (ALIEN_WIDTH * ALIEN_SCALE)/2;
	missile_array[index].origin = alien_point;
}

//-----------------------------------------------------------------------------

point_t missiles_get_tip(int index){
	missile_t* missile = &missile_array[index];
	point_t origin = missile->origin;
	origin.x = (MISSILE_WIDTH*SCALE)/2;
	origin.y += (missile->up) ? 0 : MISSILE_HEIGHT*MISSILE_SCALE;
	return origin;
}

//-----------------------------------------------------------------------------

void missiles_check_impact(){
	int i;
	missile_t* missile;
	for(i=0; i<MISSILE_COUNT; i++){
		missile = &missile_array[i];
		if(missile->active){
			point_t missile_tip = missiles_get_tip(i);
			int8_t inc = (missile->up) ? -1 : 1;
			missile_tip.y += inc;
			if(screen_getScreenColor(missile_tip.x, missile_tip.y)!=SCREEN_COLOR_BLACK){

			}
		}
	}
}

//-----------------------------------------------------------------------------

void missiles_tank_check_impact(){
	missile_t* missile = &missile_array[TANK_MISSILE];
	int x, y;
	for(x=0; x<ALIEN_COL_COUNT; x++){
		for(y=0; y<ALIEN_ROW_COUNT; y++){
			if (alien_isAlive(x,y)) {
				point_t alien_pt = alien_get_origin(x,y);
			}
//			ALIEN_XY_TO_INDEX(x,y);
		}
	}
}

void missile_missile_impact(){

}

void missile_bunker_impact(){

}

void missile_alien_impact(){
	point_t alien_origin;
	int x, y, dist;
		for(x=0; x<ALIEN_COL_COUNT; x++){
			for(y=0; y<ALIEN_ROW_COUNT; y++){
				if (alien_isAlive(x,y)) {
					alien_origin = alien_get_origin(x,y);
//					if alien_origin.x
				}
			}
		}
}

void missile_tank_impact(point_t alien_missile){
	point_t tank_origin = tank_get_origin();
	int dist = (alien_missile.x - tank_origin.x);
	if(dist < (TANK_WIDTH*TANK_SCALE) && dist > 0){
		tank_kill();
	}
}
