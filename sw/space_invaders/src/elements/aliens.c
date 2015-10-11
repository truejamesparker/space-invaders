#include "aliens.h"

static bool alien_lives_matter[ALIEN_COUNT] = { false };
static point_t alienOrigins[ALIEN_COUNT];

// global var indicates which position the aliens
// are in (flapping up vs flapping in)
static bool flapIn = false;

// a struct containing a bool indicating whether an
// alien death has occurred and its coordinates
typedef struct {
	bool kill;
	uint16_t x;
	uint16_t y;
} kill_t;

// implementation of the struct above
// nicknamed "the kill log"
static kill_t kill_log = {
		.kill = false
};

// keeps track of whether the aliens should be marching right or left
static bool _aliensMarchingRight = true;


// function definitions
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


// shift aliens in any direction
void aliens_march_dir(uint16_t dir){
	uint16_t x, y;
	int16_t x_shift = 0, y_shift = 0;

	aliens_kill_cleanup(); // erase any explosions (kills) before moving on

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
	// If there are any exploded aliens, clean up the mess
	aliens_kill_cleanup();

	// kill the alien in memory
	alien_lives_matter[index] = false;

	// Convert index to (x,y) coordinates
	uint16_t y = index / (ALIEN_COL_COUNT);
	uint16_t x = index % (ALIEN_COL_COUNT);

	// Get the origin of the alien we want to kill
	point_t origin = alien_getAlienOrigin(x, y);

	// draw the explosion in place of that particular alien
	screen_drawSymbol(alien_explosion_12x10, origin, explosionsize,
						ALIEN_SCALE, SCREEN_COLOR_WHITE);

	// set up the global kill log to know which area needs to be
	// cleaned up on next kill. Updates on the next march happen
	// automatically because we killed that alien in memory, so
	// the explosion will be removed.
	kill_log.kill = true;
	kill_log.x = x;
	kill_log.y = y;
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


bool alien_isAlive(uint16_t x, uint16_t y) {
	return ALIEN_ALIVE(x,y);
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// draw all the aliens as they currently appear (only living aliens)
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

// initializes the alien lives array
void initLivesArray() {
	uint16_t i;
	for(i=0; i < ALIEN_COUNT; i++){
		alien_lives_matter[i] = true;
	}
}

//-----------------------------------------------------------------------------

// initialize the array containing all the origin point of every alien
void initAlienOrigins() {
	uint16_t y, x;
	for(y=0; y<ALIEN_ROW_COUNT; y++){
		alien_t alien = alien_symbols[y];	// select alien type
		for(x=0; x<ALIEN_COL_COUNT; x++){
			point_t origin = {
					.x = (x * alien.size.w * ALIEN_SCALE) + x*ALIEN_PADDING_X + SCREEN_EDGE_BUFFER, // account for the screen buffer
					.y = (y * alien.size.h * ALIEN_SCALE) + y*ALIEN_PADDING_Y + SCREEN_EDGE_BUFFER + 3*ALIEN_HEIGHT*ALIEN_SCALE
			};
			alienOrigins[ALIEN_XY_TO_INDEX(x, y)] = origin;
		}
	}
}

//-----------------------------------------------------------------------------

void aliens_kill_cleanup(){
	if(kill_log.kill){
		// Get the origin of the already exploded alien to clean up.
		point_t origin = alien_getAlienOrigin(kill_log.x, kill_log.y);

		// Blank the rectangle that the exploded alien was
		screen_drawSymbol(alien_explosion_12x10, origin, explosionsize,
								ALIEN_SCALE, SCREEN_BG_COLOR);

		// reset kill log
		kill_log.kill = false;
	}
}

//-----------------------------------------------------------------------------

point_t alien_getAlienOrigin(uint16_t x, uint16_t y) {
	point_t origin = alienOrigins[ALIEN_XY_TO_INDEX(x,y)];
	return origin;
}

bool* alien_getAlienLives(){
	return alien_lives_matter;
}

//-----------------------------------------------------------------------------

void alien_shiftOrigin(uint16_t x, uint16_t y, int16_t xShift, int16_t yShift) {
	point_t *origin = &alienOrigins[ALIEN_XY_TO_INDEX(x,y)];

	// Change the x and y in place (the actual value in the array)
	origin->x += xShift;
	origin->y += yShift;
}

//-----------------------------------------------------------------------------
