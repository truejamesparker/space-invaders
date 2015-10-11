#include "gameScreen.h"

void drawFloor();
void drawScore();
void drawLives();

// ----------------------------------------------------------------------------

void gameScreen_init(){
	drawFloor();
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void drawFloor() {
	point_t origin = { .x = FLOOR_ORIGIN_X, .y = FLOOR_ORIGIN_Y };
	symbolsize_t size = { .w = FLOOR_WIDTH, .h = FLOOR_HEIGHT };
	uint32_t floor[FLOOR_WIDTH];
	memset(floor, 1, sizeof(floor));

	screen_drawSymbol(floor, origin, size, FLOOR_SCALE, FLOOR_COLOR);
}

// ----------------------------------------------------------------------------

void drawScore() {

}

// ----------------------------------------------------------------------------

void drawLives() {


}

// ----------------------------------------------------------------------------
