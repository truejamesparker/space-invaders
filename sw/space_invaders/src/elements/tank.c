#include "tank.h"

// position of tank
static point_t origin;

// direction of tank
typedef enum tankEnum { TANK_MOVING_RIGHT, TANK_MOVING_LEFT } tankdir_t;

// status of tank
static bool alive = true;

// use to determine which smoulder guise to use
static bool smoulderToggler = false;

// function declarations
void tank_draw();
void tank_move(int16_t xShift, int16_t yShift);
void tank_shiftOrigin(int16_t xShift, int16_t yShift);
bool tank_isInMargin(tankdir_t tankDirection);

//-----------------------------------------------------------------------------

// draw all tanks to screen
void tank_init(){
	// clear the tank in its place if it was somewhere
	if (!alive) {
		screen_drawSymbol(tank_15x8, origin, tankBitmapSize, TANK_SCALE, SCREEN_BG_COLOR);
	}

	// make the alien living!
	alive = true;

	// init origin
	origin.x = BUNKER_START_XOFFSET + ((BUNKER_WIDTH/2)-(TANK_WIDTH/2));
	origin.y = (7*SCREEN_HEIGHT)/8;

	tank_draw();
}

//-----------------------------------------------------------------------------

// return tank origin
point_t tank_get_origin(){
	return origin;
}

//-----------------------------------------------------------------------------

// shift tank to right
void tank_right() {
	// make sure we aren't in the right side margin
	if (tank_isInMargin(TANK_MOVING_RIGHT)) return;

	// We are clear to move to the right
	tank_move(TANK_SHIFT_X, 0);
}

//-----------------------------------------------------------------------------

// shift tank left
void tank_left() {
	// make sure we aren't in the left side margin
	if (tank_isInMargin(TANK_MOVING_LEFT)) return;

	// We are clear to move to the left
	tank_move(-TANK_SHIFT_X, 0);
}

//-----------------------------------------------------------------------------

void tank_kill() {
	// let the world know that I'm dead.
	alive = false;

//	screen_drawSymbol(tank_smoulder1_15x8, origin, tank_size, TANK_SCALE, TANK_COLOR);
}

//-----------------------------------------------------------------------------

void tank_smoulder() {
	// this will switch the guise for next time
	smoulderToggler = !smoulderToggler;

	// get a guise!
	const uint32_t *guise = (smoulderToggler) ? tank_smoulder1_15x8 : tank_smoulder2_15x8;

	// go ahead and draw it
	screen_drawSymbol(guise, origin, tankBitmapSize, TANK_SCALE, TANK_COLOR);
}

//-----------------------------------------------------------------------------

bool tank_isAlive() {
	return alive;
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// draw tank at origin
void tank_draw() {
	screen_drawSymbol(tank_15x8, origin, tankBitmapSize, TANK_SCALE, TANK_COLOR);
}

//-----------------------------------------------------------------------------

// shift the tank by xShift or yShift
void tank_move(int16_t xShift, int16_t yShift) {
	// shift the tank to the right
	screen_shiftElement(tank_15x8, origin, tankBitmapSize, xShift, yShift, TANK_SCALE, TANK_COLOR);

	// update the internal state of the tank's position
	tank_shiftOrigin(xShift*TANK_SCALE, yShift*TANK_SCALE);
}

//-----------------------------------------------------------------------------

// update the global tank origin variable
void tank_shiftOrigin(int16_t xShift, int16_t yShift) {
	// Change the x and y of the tank's origin
	origin.x += xShift;
	origin.y += yShift;
}

//-----------------------------------------------------------------------------

bool tank_isInMargin(tankdir_t tankDirection) {

	// make sure that my turret doesn't go past left/right margin
	if (tankDirection == TANK_MOVING_RIGHT) {
		return (origin.x + (TANK_SCALE) >= (SCREEN_WIDTH-SCREEN_EDGE_BUFFER));
	} else {
		return (origin.x + (TANK_SCALE)/4 <= SCREEN_EDGE_BUFFER);
	}
}

//-----------------------------------------------------------------------------
