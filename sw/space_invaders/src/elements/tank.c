#include "tank.h"

// position of tank
static point_t tank_origin = {
		.x = (SCREEN_WIDTH/2 - TANK_WIDTH/2),
		.y = (7*SCREEN_HEIGHT)/8
};

// direction of tank
typedef enum tankEnum { TANK_MOVING_RIGHT, TANK_MOVING_LEFT } tankdir_t;

// function declarations
void tank_draw();
void tank_move(int16_t xShift, int16_t yShift);
void tank_shiftOrigin(int16_t xShift, int16_t yShift);
bool tank_isInMargin(tankdir_t tankDirection);

//-----------------------------------------------------------------------------

// draw all tanks to screen
void tank_init(){
	tank_draw();
}

//-----------------------------------------------------------------------------

// return tank origin
point_t tank_get_origin(){
	return tank_origin;
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
// Private Helper Methods
//-----------------------------------------------------------------------------

// draw tank at origin
void tank_draw() {
	screen_drawSymbol(tank_15x8, tank_origin, tank_size, TANK_SCALE, TANK_COLOR);
}

//-----------------------------------------------------------------------------

// shift the tank by xShift or yShift
void tank_move(int16_t xShift, int16_t yShift) {
	// shift the tank to the right
	screen_shiftElement(tank_15x8, tank_origin, tank_size, xShift, yShift, TANK_SCALE, TANK_COLOR);

	// update the internal state of the tank's position
	tank_shiftOrigin(xShift*TANK_SCALE, yShift*TANK_SCALE);
}

//-----------------------------------------------------------------------------

// update the global tank origin variable
void tank_shiftOrigin(int16_t xShift, int16_t yShift) {
	// Change the x and y of the tank's origin
	tank_origin.x += xShift;
	tank_origin.y += yShift;
}

//-----------------------------------------------------------------------------

bool tank_isInMargin(tankdir_t tankDirection) {

	// make sure that my turret doesn't go past left/right margin
	if (tankDirection == TANK_MOVING_RIGHT) {
		return (tank_origin.x + (TANK_SCALE*TANK_WIDTH) >= (SCREEN_WIDTH-SCREEN_EDGE_BUFFER));
	} else {
		return (tank_origin.x + (TANK_SCALE*TANK_WIDTH)/4 <= SCREEN_EDGE_BUFFER);
	}
}

//-----------------------------------------------------------------------------
