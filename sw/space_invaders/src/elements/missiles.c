#include "missiles.h"

// some missiles "wiggle" as they move across the screen.
// This global defines which state we're in.
static bool wobble;
static uint16_t bunker_y;
static uint16_t alien_block_y;

// function declarations
void moveMissile(uint8_t missileIndex);
void shiftMissileOrigin(missile_t* missile);
bool missiles_inBounds(missile_t* missile);
void missiles_impact(missile_t* missile);
void missile_bunker_impact(missile_t* missile);
void missile_missile_impact();
void missile_alien_impact(missile_t* missile);
void missile_tank_impact(missile_t* missile);
void missiles_deactivate(missile_t* missile);
void missiles_check_impact(missile_t* missile);
bool missile_in_block(missile_t* missile, point_t target_origin, uint16_t target_width, uint16_t target_height);
bool missile_kill_alien_in_row(missile_t* missile, uint16_t row);
void missile_explode(point_t origin);

//-----------------------------------------------------------------------------

void missiles_init() {
	uint8_t i;

	for (i=0; i<MISSILE_COUNT; i++) {
		// Turn off all missiles
		missile_array[i].active = false;
	}
	bunker_y = bunkers_get_bunker(0).origin.y;
	alien_block_y = aliens_get_lowest_y();
}

//-----------------------------------------------------------------------------

// update the position of all alien missiles
void missiles_moveAlienMissiles(){
	uint8_t i;

	// make the alien bullets wobble next time
	wobble = !wobble;

	// i=1 because this function only updates alien missiles
	for(i=1; i<MISSILE_COUNT; i++){
		// move the corresponding missile
		moveMissile(i);
	}
}

//-----------------------------------------------------------------------------

void missiles_moveTankMissile() {
	moveMissile(TANK_MISSILE);

	// Check if the tank missile impacted with any alien missiles
	if (missile_array[TANK_MISSILE].active) missile_missile_impact();
}

//-----------------------------------------------------------------------------

// fire the tank missile
void missiles_tankFire(){
	missile_t *missile = &missile_array[TANK_MISSILE];

	if (!missile->active){ // no tank missile on screen

		missile->active = true; // set status to active
		point_t tank_gun_origin = tank_get_origin(); // get tank location
		// compute the coordinates of the cannon
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
bool missiles_alienFire(uint16_t x, uint16_t y) {
	uint8_t i = 0;

	// First off, make sure that alien is even living
	if (!alien_isAlive(x,y)) return false;

	// start at i=1 (the tank is 0)
	for(i=1; i<MISSILE_COUNT; i++){
		// find a missile that is not already active
		if (!missile_array[i].active) {

			// Get the given aliens origin
			point_t alienOrigin = aliens_getAlienOrigin(x, y);

			// transform alien origin into the origin/tip of the missile
			alienOrigin.y += (ALIEN_HEIGHT*ALIEN_SCALE);
			alienOrigin.x += (ALIEN_WIDTH*ALIEN_SCALE)/2;
			missile_array[i].origin = alienOrigin;

			// draw the symbol to the screen
			screen_drawSymbol(missile_array[i].symbol_r, missile_array[i].origin,
					missile_array[i].size, MISSILE_SCALE, MISSILE_COLOR);

			missile_array[i].active = true; // set missile status to active

			return true;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

void moveMissile(uint8_t missileIndex) {
	// Grab the missile that was passed in
	missile_t* missile = &missile_array[missileIndex];

	// No need to do anything if the missile isn't actively on screen
	if (missile->active) {
		int8_t dir = missile->up ? -1 : 1;
		const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;

		// shift it on the screen
		screen_shiftElement(symbol, missile->origin, missile->size,
							0, dir*MISSILE_SHIFT, MISSILE_SCALE, MISSILE_COLOR);

		// now update the origin in the missile struct
		shiftMissileOrigin(missile);

		// Should we keep drawing this missile?
		if (missiles_inBounds(missile)) {
			// Yes? Then check if it hit anything
			missiles_check_impact(missile);
		} else {
			// No? Then get it outta here!
			missiles_deactivate(missile);
		}

	}
}

//-----------------------------------------------------------------------------

// update the missile origin (shift it in the y direction)
void shiftMissileOrigin(missile_t* missile) {
	int8_t dir = (missile->up) ? -1 : 1;
	missile->origin.y += dir*MISSILE_SHIFT*MISSILE_SCALE;
}

//-----------------------------------------------------------------------------

void missiles_erase(missile_t* missile){
	const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;
	screen_drawSymbol(symbol, missile->origin,
						missile->size, MISSILE_SCALE, SCREEN_COLOR_BLACK);
}

//-----------------------------------------------------------------------------

bool missiles_inBounds(missile_t* missile){
	bool outOfBounds = (missile->origin.y > MISSILE_BOTTOM_BUFFER ||
						missile->origin.y < MISSILE_TOP_BUFFER);
	return !outOfBounds;
}

//-----------------------------------------------------------------------------

void missiles_deactivate(missile_t* missile){
	missiles_erase(missile);
	missile->active = false;
}

//-----------------------------------------------------------------------------

point_t missiles_get_tip(missile_t* missile){
	point_t origin;
	uint16_t x = missile->origin.x;
	uint16_t y = missile->origin.y;
	origin.x = x + 1;
	origin.y = (missile->up) ? y-1 : y + missile->size.h*MISSILE_SCALE;
	return origin;
}

//-----------------------------------------------------------------------------

void missiles_check_impact(missile_t* missile){
	point_t tip = missiles_get_tip(missile);
	if(missile->up){
		// Then it's a tank's missile
		if(tip.y > aliens_get_lowest_y()){
			missile_alien_impact(missile);
		}
	} else {
		// Then it's an alien's missile
		// Don't check if the missile is higher than the bunkers
		if(tip.y > bunker_y){
			missile_tank_impact(missile);
		}
	}
	missile_bunker_impact(missile);
}

//-----------------------------------------------------------------------------

void missile_missile_impact(){
	int i;
	missile_t* am;
	missile_t* tm = &missile_array[TANK_MISSILE];
	for(i=1; i<MISSILE_COUNT; i++){
		am = &missile_array[i];
		if(am->active){
			if(missile_in_block(tm, am->origin, MISSILE_WIDTH*MISSILE_SCALE*2, MISSILE_HEIGHT*MISSILE_SCALE)){
//				xil_printf("collision!\n\r");
				missiles_deactivate(am);
				missiles_deactivate(tm);
				missile_explode(tm->origin);
			}
		}
	}
}

//-----------------------------------------------------------------------------

void missile_bunker_impact(missile_t* missile){
	int i, j;
	for(i=0; i<BUNKER_COUNT; i++){
		bunker_t bunker = bunkers_get_bunker(i);
		if(missile_in_block(missile, bunker.origin, bunker.size.w*BUNKER_SCALE, bunker.size.h*BUNKER_SCALE)){
			for(j=0; j<BUNKER_SUB_ORIGIN_COUNT; j++){
				if(missile_in_block(missile, bunker.sub_points[j], BUNKER_SUB_ORIGIN_WIDTH, BUNKER_SUB_ORIGIN_HEIGHT)){
					if(!bunker_point_eroded(i,j)){
						bunkers_damage(i, j);
						missiles_deactivate(missile);
						return;
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------

void missile_alien_impact(missile_t* missile){
	uint16_t y;
	uint16_t height = missile->origin.y;

	for(y=0; y<ALIEN_ROW_COUNT; y++){
		int16_t y_dist = height - aliens_getAlienOrigin(0,y).y;
		if(y_dist <= ALIEN_HEIGHT*ALIEN_SCALE){
			if(missile_kill_alien_in_row(missile, y)){
				return;
			}
		}
	}
}

//-----------------------------------------------------------------------------

bool missile_kill_alien_in_row(missile_t* missile, uint16_t row){
	point_t alien_origin;
	uint16_t x;
	for(x=0; x<ALIEN_COL_COUNT; x++){
		alien_origin = aliens_getAlienOrigin(x,row);
		if(!alien_isAlive(x, row)){
			continue;
		}
		bool hit = missile_in_block(missile, alien_origin, ALIEN_WIDTH*ALIEN_SCALE, ALIEN_HEIGHT*ALIEN_SCALE);
		if(hit){
			uint16_t index = alien_xy_to_index(x, row);
			missiles_deactivate(missile);
			aliens_kill(index);
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------

void missile_tank_impact(missile_t* missile){
	point_t tip = missiles_get_tip(missile);
	if (screen_getScreenColor(tip.x, tip.y)!=TANK_COLOR){
		return;
	}
	point_t tank_origin = tank_get_origin();
	bool hit = missile_in_block(missile, tank_origin, TANK_WIDTH*TANK_SCALE, TANK_HEIGHT*TANK_SCALE);
	if(hit){
		tank_kill();
	}
}

//-----------------------------------------------------------------------------

bool missile_in_block(missile_t* missile, point_t target_origin, uint16_t target_width, uint16_t target_height){
	point_t tip = missiles_get_tip(missile);
	bool up = missile->up;
	int x_dist = (tip.x - target_origin.x);
	int y_dist = up ? ((target_origin.y+target_height) - tip.y) : (tip.y - target_origin.y);
//	int y_dist = (tip.y - target_origin.y);

	if ((x_dist <= target_width) && (x_dist >= 0) &&
			(y_dist <= (target_height+MISSILE_HEIGHT*MISSILE_SCALE)) &&
					(y_dist >= 0)){
		return true;
	}
	else{
		return false;
	}
}

void missile_explode(point_t origin){

}

//-----------------------------------------------------------------------------
