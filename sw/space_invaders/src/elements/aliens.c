#include "aliens.h"
#define HSPACE 5*ALIEN_SCALE
#define VSPACE 5*ALIEN_SCALE

static bool alien_lives_matter[ALIEN_COUNT] = { false }; bool flapIn = true;

static point_t alien_block_origin = {.x = 0, .y = 0};

static point_t alien_rel_origins[55];
static point_t bunker_origins[4];

#define BUNKER_START_XOFFSET 24*ALIEN_SCALE

bool aliens_is_alive_right(uint16_t x, uint16_t y);
bool aliens_is_alive_left(uint16_t x, uint16_t y);

//-----------------------------------------------------------------------------

bool* aliens_getLives() {
	return alien_lives_matter;
}

//-----------------------------------------------------------------------------

void bunkers_init_origins(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = {
				.x = i * 148 + BUNKER_START_XOFFSET,
				.y = 3*(SCREEN_HEIGHT)/4
		};
		bunker_origins[i] = origin;
	}
}

void bunkers_draw(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = bunker_origins[i];
		screen_drawSymbol(bunker_24x18, origin, tank_size,
				ALIEN_SCALE, BUNKER_COLOR);
	}

}
//-----------------------------------------------------------------------------

void aliens_init_lives_array(){
	uint16_t i, size = sizeof(alien_lives_matter);
	for(i=0; i < size; i++){
		alien_lives_matter[i] = true;
	}
}

void aliens_init_rel_origins(){
	uint16_t y, x;
	for(y=0; y<ALIEN_ROW_COUNT; y++){
		alien_t alien = alien_symbols[y];	// select alien type
		for(x=0; x<ALIEN_COL_COUNT; x++){
			point_t origin = {
					.x = x * alien.size.w * ALIEN_SCALE,
					.y = y * alien.size.h * ALIEN_SCALE
			};
			alien_rel_origins[ALIEN_XY_TO_INDEX(x, y)] = origin;
		}
	}
}


void aliens_draw() {
	uint16_t x = 0;
	uint16_t y = 0;

	// For every alien out of the all the aliens in the whole wide world...
	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];	// select alien type
		for (x = 0; x < ALIEN_COL_COUNT; x++) {

			// This is the top-left of the symbol
			point_t alienOrigin = {
					.x = (x * alien.size.w * ALIEN_SCALE) + alien_block_origin.x,
					.y = (y * alien.size.h * ALIEN_SCALE) + alien_block_origin.y
			};

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(x,y)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
			// Tell the screen to draw my symbol
			screen_drawSymbol(symbol, alienOrigin, alien.size,
					ALIEN_SCALE, color);
		}
	}
}


void alien_add_block_offset(point_t alien_origin){
	alien_origin.x += alien_block_origin.x;
	alien_origin.y += alien_block_origin.y;
}

point_t alien_atHere(uint16_t x, uint16_t y){
	point_t alien_origin =  alien_rel_origins[ALIEN_XY_TO_INDEX(x,y)];
	alien_origin.x += alien_block_origin.x;
	alien_origin.y += alien_block_origin.y;
	return alien_origin;
}

point_t alien_atRight(uint16_t x, uint16_t y){
	point_t alien_origin = alien_rel_origins[ALIEN_XY_TO_INDEX(x,y)];
	alien_origin.x += (alien_symbols[0].size.w * ALIEN_SCALE);
	alien_add_block_offset(alien_origin);
	return alien_origin;
}

point_t alien_atLeft(uint16_t x, uint16_t y){
	point_t alien_origin =  alien_rel_origins[ALIEN_XY_TO_INDEX(x,y)];
	alien_origin.x -= (alien_symbols[0].size.w * ALIEN_SCALE);
	alien_origin.x += alien_block_origin.x;
	alien_origin.y += alien_block_origin.y;
	return alien_origin;
}

void aliens_march_right(){
	uint16_t x = 0;
	uint16_t y = 0;

	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {
			if(x==0 && ALIEN_ALIVE(x,y)){
				screen_drawSymbol(symbol, alien_atHere(x, y), alien.size,
										ALIEN_SCALE, 0x0000);
			}

			if(!ALIEN_ALIVE(x, y) && aliens_is_alive_right(x, y)){
				uint32_t color = SCREEN_BG_COLOR;
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atRight(x,y), alien.size,
						ALIEN_SCALE, color);
			}
		}
	}
	alien_block_origin.x += (alien_symbols[0].size.w * ALIEN_SCALE);
}

void aliens_march_left(){
	uint16_t x = 0;
	uint16_t y = 0;

	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {
			if(x==10 && ALIEN_ALIVE(x,y)){
				screen_drawSymbol(symbol, alien_atHere(x, y), alien.size,
										ALIEN_SCALE, 0x0000);
			}

			if(!ALIEN_ALIVE(x, y) && aliens_is_alive_left(x, y)){
				uint32_t color = SCREEN_BG_COLOR;
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atLeft(x,y), alien.size,
						ALIEN_SCALE, color);
			}
		}
	}
	alien_block_origin.x -= (alien_symbols[0].size.w * ALIEN_SCALE);
}



void aliens_march_down(){
	uint16_t x = 0;
	uint16_t y = 0;

	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {
			if(x==10 && ALIEN_ALIVE(x,y)){
				screen_drawSymbol(symbol, alien_atHere(x, y), alien.size,
										ALIEN_SCALE, 0x0000);
			}

			if(!ALIEN_ALIVE(x, y) && aliens_is_alive_left(x, y)){
				uint32_t color = SCREEN_BG_COLOR;
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atLeft(x,y), alien.size,
						ALIEN_SCALE, color);
			}
		}
	}
	alien_block_origin.y += (alien_symbols[0].size.h * ALIEN_SCALE);
}


//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------


bool aliens_is_alive_right(uint16_t x, uint16_t y){
	if(x==10){
		return false;
	}
	else{
		return ALIEN_ALIVE(x+1, y);
	}
}

bool aliens_is_alive_left(uint16_t x, uint16_t y){
	if(x==0){
		return false;
	}
	else{
		return ALIEN_ALIVE(x-1, y);
	}
}

void aliens_kill(uint16_t index){
	alien_lives_matter[index] = false;
}
