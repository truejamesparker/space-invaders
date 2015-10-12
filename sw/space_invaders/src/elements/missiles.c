#include "missiles.h"

// some missiles "wiggle" as they
// move across the screen. This global
// defines which state we're in
static bool wobble;
static point_t cur_missile_tip;

// function declarations
void missiles_shift_origin(missile_t* missile);
bool missiles_in_bounds(missile_t* missile);
void missiles_set_alien_origin(uint16_t index);
void missiles_impact();
void missile_bunker_impact();
void missile_missile_impact();
void missile_alien_impact();
void missile_tank_impact();
void missiles_deactivate(missile_t* missile);
void missiles_check_impact(missile_t* missile);

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
		missile_t* missile = &missile_array[i];
		if (missile->active) {
			int8_t dir = missile->up ? -1 : 1;
			const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;

			// shift it on the scrren
			screen_shiftElement(symbol, missile->origin, missile->size,
								0, dir*MISSILE_SHIFT, MISSILE_SCALE, MISSILE_COLOR);
			// now update the origin in the missile struct
			missiles_shift_origin(missile);
			if(!missiles_in_bounds(missile)){
				xil_printf("deactivating missile\n\r");
				missiles_deactivate(missile);
			}
			else{
				missiles_check_impact(missile);
			}

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
void missiles_shift_origin(missile_t* missile) {
	int8_t dir = (missile->up) ? -1 : 1;
	missile->origin.y += dir*MISSILE_SHIFT*MISSILE_SCALE;
}

void missiles_erase(missile_t* missile){
	const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;
	screen_drawSymbol(symbol, missile->origin,
						missile->size, MISSILE_SCALE, SCREEN_COLOR_BLACK);
}

bool missiles_in_bounds(missile_t* missile){
	if(missile->origin.y > (SCREEN_HEIGHT-SCREEN_EDGE_BUFFER) || missile->origin.y < SCREEN_EDGE_BUFFER){
		return false;
	}
	else{
		return true;
	}
}

void missiles_deactivate(missile_t* missile){
	missiles_erase(missile);
	missile->active = false;
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

point_t missiles_get_tip(missile_t* missile){
	point_t origin = missile->origin;
	uint16_t x = missile->origin.x;
	uint16_t y = missile->origin.y;
	origin.x = x + (missile->size.w*SCALE)/2;
	origin.y += (missile->up) ? y : y + missile->size.h*MISSILE_SCALE;
	return origin;
}

//-----------------------------------------------------------------------------



void missiles_check_impact(missile_t* missile){
	point_t missile_tip = missiles_get_tip(missile);
	if(screen_getScreenColor(missile_tip.x, missile_tip.y)!=SCREEN_COLOR_BLACK){
		xil_printf("impact alert!\n\r");
		missiles_impact(missile);
	}
}

//-----------------------------------------------------------------------------


void missiles_impact(missile_t* missile){
	if(missile->up){
		missile_bunker_impact();
		missile_alien_impact();
	}
	else{
		missile_tank_impact();
		missile_bunker_impact();
	}
}


void missile_missile_impact(){

}

void missile_bunker_impact(){
	xil_printf("hit bunker?\n\r");
}

bool in_range(missile_t* missile, point_t target_origin, uint16_t target_width, uint16_t target_height);

bool x_in_range(missile_t* missile, point_t target_origin, uint16_t target_width);

void missile_alien_impact(missile_t* missile){
	xil_printf("hit alien?\n\r");
	point_t alien_origin;
	int x, y, dist;
		for(x=0; x<ALIEN_COL_COUNT; x++){
			for(y=0; y<ALIEN_ROW_COUNT; y++){
				if (alien_isAlive(x,y)) {
					alien_origin = alien_get_origin(x,y);
					bool hit = x_in_range(missile, alien_origin, ALIEN_WIDTH*ALIEN_SCALE);
					if(hit){
						xil_printf("alien impact detected!\n\r");
						uint16_t index = alien_xy_to_index(alien_origin.x, alien_origin.y);
						aliens_kill(index);
						missiles_deactivate(missile);
						return;
					}
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

bool in_range(missile_t* missile, point_t target_origin, uint16_t target_width, uint16_t target_height){
	bool up = missile->up;
	int x_dist = (missile->origin.x - target_origin.x);
	int y_dist = up ? (missile->origin.y - target_origin.y) : (target_origin.y - missile->origin.y);
	xil_printf("x: %d , y: %d\n\r", x_dist, y_dist);
	if (x_dist < target_width && x_dist > 0 && y_dist < target_height && y_dist > 0){
		return true;
	}
	else{
		return false;
	}
}

bool x_in_range(missile_t* missile, point_t target_origin, uint16_t target_width){
	int x_dist = (missile->origin.x - target_origin.x);
	if (x_dist < target_width && x_dist > 0){
			xil_printf("x in range!\b\r");
			return true;
		}
		else{
			return false;
		}
}

