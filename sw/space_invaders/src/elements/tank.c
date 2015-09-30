#include "tank.h"

static point_t tank_origin = {
		.x = SCREEN_WIDTH/2 ,
		.y = (7*SCREEN_HEIGHT)/8
};

void tank_draw();
void tank_move(int16_t xShift, int16_t yShift);
void tank_shiftOrigin(int16_t xShift, int16_t yShift);

//-----------------------------------------------------------------------------

void tank_init(){
	tank_draw();
}

//-----------------------------------------------------------------------------

void tank_right() {
	tank_move(TANK_SHIFT_X, 0);
}

//-----------------------------------------------------------------------------

void tank_left() {
	tank_move(-TANK_SHIFT_X, 0);
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

void tank_draw() {
	screen_drawSymbol(tank_15x8, tank_origin, tank_size, TANK_SCALE, TANK_COLOR);
}

//-----------------------------------------------------------------------------

void tank_move(int16_t xShift, int16_t yShift) {
	// shift the tank to the right
	screen_shiftElement(tank_15x8, tank_origin, tank_size, xShift, yShift, TANK_SCALE, TANK_COLOR);

	// update the internal state of the tank's position
	tank_shiftOrigin(xShift, yShift);
}

//-----------------------------------------------------------------------------

void tank_shiftOrigin(int16_t xShift, int16_t yShift) {
	// Change the x and y of the tank's origin
	tank_origin.x += xShift;
	tank_origin.y += yShift;
}

//-----------------------------------------------------------------------------

