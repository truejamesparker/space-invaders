#include "missiles.h"

// some missiles "wiggle" as they move across the screen.
// This global defines which state we're in.
static bool wobble;
static uint16_t bunker_y;
static uint16_t alien_block_y;

// instantiate a kill-log to keep track of detonated missiles
// for missile-to-missile collisions (extra feature) 
static kill_t mkill_log = {.kill = false, .x = 0, .y=0};

// array of all missile types
static missile_t missile_array[MISSILE_COUNT] = {
		{
				.symbol_r = missile0_1x7,			// missile type 1 (tank)
				.symbol_l = missile0_1x7,
				.up = true,
				.active = false,
				.bitmapSize = &tankMissileBitmapSize
		},
		{
				.symbol_r = missile1_3x7,			// missile type 2 (alien)
 				.symbol_l = missile1_3x7,
				.up = false,
				.active = false,
				.bitmapSize = &alienMissile12BitmapSize
		},
		{
				.symbol_r = missile2r_3x7,			// missile type 3 (alien)
				.symbol_l = missile2l_3x7,
				.up = false,
				.active = false,
				.bitmapSize = &alienMissile12BitmapSize
		},
		{
				.symbol_r = missile3r_6x7,			// missile type 4 (alien)
				.symbol_l = missile3l_6x7,
				.up = false,
				.active = false,
				.bitmapSize = &alienMissile3BitmapSize
		},
};

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
void missile_cleanup();

//-----------------------------------------------------------------------------

void missiles_init() {
	uint8_t i;

	for (i=0; i<MISSILE_COUNT; i++) {
		// Turn off all missiles
		missile_array[i].active = false;
	}

	// get the y-coordinate of the bunkers 
	// used for starting missile-to-bunker impacts
	bunker_t bunker = bunkers_getBunker(0);
	bunker_y = bunker.origin.y;

	// get the y-coordinate of the alien block
	// used for starting missile-to-alien impacts
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
		audio_play_track(SOUND_TANK_SHOT);
		missile->active = true; // set status to active
		point_t tank_gun_origin = tank_get_origin(); // get tank location
		// compute the coordinates of the cannon
		// x-coordinate: take into account the width of the missile and width of the gun
		tank_gun_origin.x += (TANK_WIDTH)/2 - (missile->bitmapSize->w*MISSILE_SCALE)/2;
		tank_gun_origin.y -= MISSILE_HEIGHT;

		// set the starting coordinates
		missile->origin = tank_gun_origin;
		// draw the missile at the tip of the tank's cannon
		screen_drawSymbol(missile->symbol_r, missile->origin, *missile->bitmapSize,
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
			alienOrigin.y += (ALIEN_HEIGHT);
			alienOrigin.x += (ALIEN_WIDTH)/2;
			missile_array[i].origin = alienOrigin;

			// draw the symbol to the screen
			screen_drawSymbol(missile_array[i].symbol_r, missile_array[i].origin,
					*missile_array[i].bitmapSize, MISSILE_SCALE, MISSILE_COLOR);

			missile_array[i].active = true; // set missile status to active

			return true;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------

// deactivate all missiles
void missiles_deactivateAll() {
	uint8_t i = 0;
	for(i=0; i<MISSILE_COUNT; i++) {
		// grab a missile and turn it off!
		missiles_deactivate(&missile_array[i]);
	}
}

//-----------------------------------------------------------------------------

// return number of alien missiles on the screen
uint16_t missiles_getActiveAlienMissiles() {
	uint8_t i = 0;
	uint16_t count = 0;

	// i=1, we are only considering alien missiles
	for(i=1; i<MISSILE_COUNT; i++) {
		if (missile_array[i].active) count++;
	}

	return count;
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// incrementally shift the missiles (up/down) on the screen
void moveMissile(uint8_t missileIndex) {
	// Grab the missile that was passed in
	missile_t* missile = &missile_array[missileIndex];
	// if a missile was exploded, clean it up before moving missiles again
	if(mkill_log.kill){
			missile_cleanup();
		}
	// No need to do anything if the missile isn't actively on screen
	if (missile->active) {
		int8_t dir = missile->up ? -1 : 1;
		const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;

		// shift it on the screen
		screen_shiftElement(symbol, missile->origin, *missile->bitmapSize,
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

// erase the missile on the screen
void missiles_erase(missile_t* missile){
	const uint32_t* symbol = wobble ? missile->symbol_r : missile->symbol_l;
	screen_drawSymbol(symbol, missile->origin,
						*missile->bitmapSize, MISSILE_SCALE, SCREEN_BG_COLOR);
}

//-----------------------------------------------------------------------------

// is the missile ouside the gameplay area?
bool missiles_inBounds(missile_t* missile){
	bool outOfBounds = (missile->origin.y > MISSILE_BOTTOM_BUFFER ||
						missile->origin.y < MISSILE_TOP_BUFFER);
	return !outOfBounds;
}

//-----------------------------------------------------------------------------

// deactivate missile
void missiles_deactivate(missile_t* missile){
	missiles_erase(missile); // erase the missile image
	missile->active = false; // set status to inactive
}

//-----------------------------------------------------------------------------

// get the point directly in front of the missile (direction-dependent)
point_t missiles_get_tip(missile_t* missile){
	point_t origin;
	uint16_t x = missile->origin.x;
	uint16_t y = missile->origin.y;
	origin.x = x + 1;
	// if this missile is moving down, get the coordinate
	// of the bottom of the bitmap
	origin.y = (missile->up) ? y-1 : y + missile->bitmapSize->h*MISSILE_SCALE;
	return origin;
}

//-----------------------------------------------------------------------------

// check to see if a missile hit something
void missiles_check_impact(missile_t* missile){
	point_t tip = missiles_get_tip(missile);
	if(missile->up){ // is this a tank missile
		if(tip.y > aliens_get_lowest_y()){ // make sure missile is in range of aliens
			missile_alien_impact(missile); // check missile-to-alien impacts
		}
	} else { // it's an alien missile
		// Don't check if the missile is higher than the bunkers
		if(tip.y > bunker_y){
			missile_tank_impact(missile); // check missile-to-tank impacts
		}
	}
	// always check missile-to-missile impacts
	missile_bunker_impact(missile);
}

//-----------------------------------------------------------------------------

// check if any missiles hit each other
void missile_missile_impact(){
	int i;
	missile_t* am; // active missile
	missile_t* tm; // tank missile
	tm = &missile_array[TANK_MISSILE];
	for(i=1; i<MISSILE_COUNT; i++){ // iterate through the aliens missiles
		am = &missile_array[i];
		if(am->active){
			if(missile_in_block(tm, am->origin, MISSILE_WIDTH*2, MISSILE_HEIGHT)){
				// deactivate both missiles
				missiles_deactivate(am);
				missiles_deactivate(tm);
				// draw the collision explosion
				missile_explode(tm->origin);
				audio_play_track(SOUND_ALIEN_KILLED);
			}
		}
	}
}

//-----------------------------------------------------------------------------

// check if any missiles hit the bunker
void missile_bunker_impact(missile_t* missile){
	int i, j;
	for(i=0; i<BUNKER_COUNT; i++){
		bunker_t bunker = bunkers_getBunker(i);
		if(missile_in_block(missile, bunker.origin, BUNKER_WIDTH, BUNKER_HEIGHT)){
			for(j=0; j<BUNKER_SUB_ORIGIN_COUNT; j++){
				if(missile_in_block(missile, bunker.sub_points[j], BUNKER_SUB_ORIGIN_WIDTH, BUNKER_SUB_ORIGIN_HEIGHT)){
					if (!bunkers_isPointEroded(i,j)) {
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
		// figure out what row the missile is closest to subtract its height
		int16_t y_dist = height - aliens_getAlienOrigin(0,y).y;
		if(y_dist <= ALIEN_HEIGHT){
			if(missile_kill_alien_in_row(missile, y)){
				return;
			}
		}
	}

	// detect spaceship collision, only if spaceship is present
	if(spaceship_isActive()){
		point_t s_origin = spaceship_get_origin();
		missile_t* missile = &missile_array[TANK_MISSILE];
		bool hit = missile_in_block(missile, s_origin, SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
		if(hit){
			missiles_deactivate(missile);
			spaceship_kill();
		}
	}
}

// ----------------------------------------------------------------------------

// check if an alien has been hit
bool missile_kill_alien_in_row(missile_t* missile, uint16_t row){
	point_t alien_origin;
	uint16_t x;
	for(x=0; x<ALIEN_COL_COUNT; x++){
		alien_origin = aliens_getAlienOrigin(x,row);
		if(!alien_isAlive(x, row)){
			continue; // it's dead, move on
		}
		// did the missile penetrate this alien?
		bool hit = missile_in_block(missile, alien_origin, ALIEN_WIDTH, ALIEN_HEIGHT);
		if(hit){
			uint16_t index = alien_xy_to_index(x, row);
			missiles_deactivate(missile); // deactivate the missile
			aliens_kill(index); // ... aliens lives don't matter
			return true;
		}
	}
	return false;
}

// ----------------------------------------------------------------------------

// check if the tank has been hit
void missile_tank_impact(missile_t* missile){
	point_t tip = missiles_get_tip(missile);
	point_t tank_origin = tank_get_origin();
	if (screen_getScreenColor(tip.x, tip.y) != TANK_COLOR && tip.y < (tank_origin.y + TANK_GUN_HEIGHT) ){
		return;
	}

	// If tank was hit, kill the tank
	bool hit = missile_in_block(missile, tank_origin, TANK_WIDTH, TANK_HEIGHT);
	if (hit) tank_kill();
}
// ----------------------------------------------------------------------------

bool missile_in_block(missile_t* missile, point_t target_origin, uint16_t target_width, uint16_t target_height){
	point_t tip = missiles_get_tip(missile);
	bool up = missile->up;

	// account for the fact that we disable graphics wrapping
	// and allow for overflow in the origin coordinates
	if(target_origin.x > SCREEN_WIDTH){
		target_origin.x = 0;
	}

	int x_dist = (tip.x - target_origin.x);
	int y_dist = up ? ((target_origin.y+target_height) - tip.y) : (tip.y - target_origin.y);

	return ((x_dist <= target_width) && (x_dist >= 0) &&
					(y_dist <= (target_height+MISSILE_HEIGHT)) &&
					(y_dist >= 0));
}

// ----------------------------------------------------------------------------

// draw the missile-to-missile explosions
void missile_explode(point_t origin){
	// center on missile collision
	origin.x -= (explosionBitmapSize.w*MISSILE_SCALE)/2;

	screen_drawSymbol(missile_explosion_12x10, origin,
			explosionBitmapSize, MISSILE_SCALE, SCREEN_COLOR_YELLOW);

	// log this collision to the kill-log
	mkill_log.kill = true;
	mkill_log.x = origin.x;
	mkill_log.y = origin.y;
}

// ----------------------------------------------------------------------------

// cleanup the missile-to-missile explosions
void missile_cleanup(){
	point_t kill_point = {.x = mkill_log.x, .y = mkill_log.y};
	screen_drawSymbol(missile_explosion_12x10, kill_point,
			explosionBitmapSize, MISSILE_SCALE, SCREEN_BG_COLOR);
	mkill_log.kill = false;
}

//-----------------------------------------------------------------------------
