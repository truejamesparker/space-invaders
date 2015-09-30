#include "aliens.h"

static bool alien_lives_matter[ALIEN_COUNT] = { false };
static point_t alienOrigins[ALIEN_COUNT];

static bool flapIn = false;

typedef struct {
	bool kill;
	uint16_t x;
	uint16_t y;
}kill_t;

static kill_t kill_log = {
		.kill = false
};


static bool _aliensMarchingRight = true;

void initAlienOrigins();
void initLivesArray();
void aliens_draw();
void aliens_kill_cleanup();
point_t alien_getAlienOrigin(uint16_t x, uint16_t y);
void alien_shiftOrigin(uint16_t x, uint16_t y, int16_t xShift, int16_t yShift);

//-----------------------------------------------------------------------------

void aliens_init() {
	// set all lives to true
	initLivesArray();

	// set all alien origins, relative to top-left
	initAlienOrigins();

	// draw the aliens!
	aliens_draw();
}

//-----------------------------------------------------------------------------

void aliens_march_dir(uint16_t dir){
	uint16_t x, y;
	int16_t x_shift = 0, y_shift = 0;

	aliens_kill_cleanup();

	// Set the (x,y) shifts according to dir input
	if (dir == ALIEN_MARCH_DOWN) {
		x_shift = 0;
		y_shift = ALIEN_SHIFT_Y;
	} else if (dir == ALIEN_MARCH_UP) {
		x_shift = 0;
		y_shift = -ALIEN_SHIFT_Y;
	} else if (dir == ALIEN_MARCH_RIGHT) {
		x_shift = ALIEN_SHIFT_X;
		y_shift = 0;
	} else if (dir == ALIEN_MARCH_LEFT) {
		x_shift = -ALIEN_SHIFT_X;
		y_shift = 0;
	}


	for (y = 0; y < ALIEN_ROW_COUNT; y++) {

		// If we are marching down, we need to start drawing from
		// the downmost column, otherwise the aliens will stack on top
		// of each other and the bottom y_shift rows will be blank
		if (dir == ALIEN_MARCH_DOWN) y = (ALIEN_ROW_COUNT-1) - y;

		// ================== possibly backward y ================

		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {

			// If we are marching to the right, we need to start drawing from
			// the rightmost column, otherwise the aliens will stack on top
			// of each other and the right x_shift columns will be blank
			if (dir == ALIEN_MARCH_RIGHT) x = (ALIEN_COL_COUNT-1) - x;

			// -------------- possibly backward x ----------------

			// Grab the alien origin for this given alien (col,row)
			point_t alienOrigin = alien_getAlienOrigin(x, y);

			// Tell the screen to shift this element by x_shift, y_shift
			// uint32_t color = (ALIEN_ALIVE(x,y)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			if(ALIEN_ALIVE(x,y)){
				screen_shiftElement(symbol, alienOrigin, alien.size,
									x_shift, y_shift, ALIEN_SCALE, ALIEN_COLOR);
			}


			// update internal alien origin
			alien_shiftOrigin(x, y, x_shift*ALIEN_SCALE, y_shift*ALIEN_SCALE);

			// ---------------------------------------------------

			// Switch back to the original x so that the for loop is happy
			if (dir == ALIEN_MARCH_RIGHT) x = (ALIEN_COL_COUNT-1) - x;
		}

		// =======================================================

		// Switch back to the original y so that the for loop is happy
		if (dir == ALIEN_MARCH_DOWN) y = (ALIEN_ROW_COUNT-1) - y;
	}
}



void aliens_march(){
	// origin of leftmost alien
	point_t left_origin = alien_getAlienOrigin(0, 0);
	// origin of rightmost alien
	point_t right_origin = alien_getAlienOrigin(ALIEN_COL_COUNT-1, 0);

	// if i'm marching right and my rightmost part of me will be in the
	// margin, drop down onto the next row, change marching direction to left
	if(_aliensMarchingRight && ((right_origin.x + ALIEN_SCALE*ALIEN_WIDTH) >= SCREEN_WIDTH - SCREEN_EDGE_BUFFER)){
		aliens_march_dir(ALIEN_MARCH_DOWN);
		_aliensMarchingRight = false;

	// if I'm about to be in the left margin, drop down, change marching direction
	} else if(!_aliensMarchingRight && ((left_origin.x) <= SCREEN_EDGE_BUFFER)){
		aliens_march_dir(ALIEN_MARCH_DOWN);
		_aliensMarchingRight = true;

	// If I'm marching right, then march right, dang it!
	} else if(_aliensMarchingRight) {
		aliens_march_dir(ALIEN_MARCH_RIGHT);

	// If I'm marching left, then march left
	} else if(!_aliensMarchingRight) {
		aliens_march_dir(ALIEN_MARCH_LEFT);
	}

	// change the direction of the alien flapping
	flapIn = !flapIn;
}

//-----------------------------------------------------------------------------

void aliens_kill(uint16_t index) {
	aliens_kill_cleanup();
	alien_lives_matter[index] = false;
	uint16_t y = index / (ALIEN_COL_COUNT);
	uint16_t x = index % (ALIEN_COL_COUNT);
	xil_printf("index: %d -> x: %d y: %d", index, x, y);
	point_t origin = alien_getAlienOrigin(x, y);
	screen_drawSymbol(alien_explosion_12x10, origin, explosionsize,
						ALIEN_SCALE, SCREEN_COLOR_WHITE);
	kill_log.kill = true;
	kill_log.x = x;
	kill_log.y = y;
}

void aliens_kill_cleanup(){
	if(kill_log.kill){
		point_t origin = alien_getAlienOrigin(kill_log.x, kill_log.y);
		screen_drawSymbol(alien_explosion_12x10, origin, explosionsize,
								ALIEN_SCALE, SCREEN_BG_COLOR);
	}
}

//-----------------------------------------------------------------------------

void aliens_left() {
	_aliensMarchingRight = false;
	aliens_march();
}

//-----------------------------------------------------------------------------

void aliens_right() {
	_aliensMarchingRight = true;
	aliens_march();
}

//-----------------------------------------------------------------------------

void aliens_up() {
	aliens_march_dir(ALIEN_MARCH_UP);
}

//-----------------------------------------------------------------------------

void aliens_down() {
	aliens_march_dir(ALIEN_MARCH_DOWN);
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

void aliens_draw() {
	uint16_t row = 0, col = 0;

	// For every alien out of the all the aliens in the whole wide world...
	for (row = 0; row < ALIEN_ROW_COUNT; row++) {
		alien_t alien = alien_symbols[row];	// select alien type
		for (col = 0; col < ALIEN_COL_COUNT; col++) {

			// Convert Alien Coordinates (col,row) into an absolute point (x,y)
			point_t alienOrigin = alien_getAlienOrigin(col, row);

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(col,row)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
			// Tell the screen to draw my symbol
			screen_drawSymbol(symbol, alienOrigin, alien.size,
					ALIEN_SCALE, color);
		}
	}
}

//-----------------------------------------------------------------------------

void initLivesArray() {
	uint16_t i;
	for(i=0; i < ALIEN_COUNT; i++){
		alien_lives_matter[i] = true;
	}
}

//-----------------------------------------------------------------------------

void initAlienOrigins() {
	uint16_t y, x;
	for(y=0; y<ALIEN_ROW_COUNT; y++){
		alien_t alien = alien_symbols[y];	// select alien type
		for(x=0; x<ALIEN_COL_COUNT; x++){
			point_t origin = {
					.x = (x * alien.size.w * ALIEN_SCALE) + x*ALIEN_PADDING_X + SCREEN_EDGE_BUFFER,
					.y = (y * alien.size.h * ALIEN_SCALE) + y*ALIEN_PADDING_Y + SCREEN_EDGE_BUFFER
			};
			alienOrigins[ALIEN_XY_TO_INDEX(x, y)] = origin;
		}
	}
}

//-----------------------------------------------------------------------------

point_t alien_getAlienOrigin(uint16_t x, uint16_t y) {
	point_t origin = alienOrigins[ALIEN_XY_TO_INDEX(x,y)];
	return origin;
}

//-----------------------------------------------------------------------------

void alien_shiftOrigin(uint16_t x, uint16_t y, int16_t xShift, int16_t yShift) {
	point_t *origin = &alienOrigins[ALIEN_XY_TO_INDEX(x,y)];

	// Change the x and y in place (the actual value in the array)
	origin->x += xShift;
	origin->y += yShift;
}

//-----------------------------------------------------------------------------
