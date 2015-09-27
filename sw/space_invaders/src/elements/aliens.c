#include "aliens.h"
#define HSPACE 5*ALIEN_SCALE
#define VSPACE 5*ALIEN_SCALE

static bool alien_lives_matter[ALIEN_COUNT] = { false }; bool flapIn = true;

static point_t alien_block_origin = {.x = ALIEN_WIDTH*ALIEN_SCALE, .y = ALIEN_HEIGHT*ALIEN_SCALE*2};

static point_t alien_rel_origins[55];

static bool march_right = true;



bool aliens_is_alive_right(uint16_t x, uint16_t y);
bool aliens_is_alive_left(uint16_t x, uint16_t y);
point_t alien_atHere(uint16_t x, uint16_t y);
bool aliens_is_alive_down(uint16_t x, uint16_t y);
point_t alien_atRight(uint16_t x, uint16_t y);
point_t alien_atLeft(uint16_t x, uint16_t y);
point_t alien_atDown(uint16_t x, uint16_t y);

//-----------------------------------------------------------------------------

bool* aliens_getLives() {
	return alien_lives_matter;
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
					.x = (x * 3 * alien.size.w * ALIEN_SCALE)/2,
					.y = (y * 3 * alien.size.h * ALIEN_SCALE)/2
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

			point_t alienOrigin = alien_atHere(x, y);

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(x,y)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
			// Tell the screen to draw my symbol
			screen_drawSymbol(symbol, alienOrigin, alien.size,
					ALIEN_SCALE, color);
		}
	}
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
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atHere(x+1,y), alien.size,
						ALIEN_SCALE, SCREEN_BG_COLOR);
			}
		}
	}
	alien_block_origin.x += (3 * alien_symbols[0].size.w * ALIEN_SCALE)/2;
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
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atHere(x-1,y), alien.size,
						ALIEN_SCALE, SCREEN_BG_COLOR);
			}
		}
	}
	alien_block_origin.x -= (3 * alien_symbols[0].size.w * ALIEN_SCALE)/2;
}


void aliens_march_down(){
	uint16_t x = 0;
	uint16_t y = 0;

	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {
			if(y==0 && ALIEN_ALIVE(x,y)){
				screen_drawSymbol(symbol, alien_atHere(x, y), alien.size,
										ALIEN_SCALE, 0x0000);
			}

			if(!ALIEN_ALIVE(x, y) && aliens_is_alive_down(x, y)){
				const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
				// Tell the screen to draw my symbol
				screen_drawSymbol(symbol, alien_atHere(x,y+1), alien.size,
						ALIEN_SCALE, SCREEN_BG_COLOR);
			}
		}
	}
	alien_block_origin.y += (3 * alien_symbols[0].size.h * ALIEN_SCALE)/2;
}



void aliens_march(){
	point_t left_origin = alien_atHere(0, 0);
	point_t right_origin = alien_atHere(ALIEN_COL_COUNT-1, 0);
	bool shift_down = false;

	xil_printf("Left: %d\r\n", left_origin.x);
	xil_printf("Right: %d\r\n", right_origin.x);

	if(((right_origin.x + ALIEN_SCALE*ALIEN_WIDTH) >= SCREEN_WIDTH - SCREEN_EDGE_BUFFER) && march_right){
		march_right = false;
		aliens_march_down();
		shift_down = true;
	}
	if(left_origin.x <= SCREEN_EDGE_BUFFER && !march_right){
		march_right = true;
		aliens_march_down();
		shift_down = true;
	}
	if(march_right && !shift_down){
		aliens_march_right();
	}
	else if(!march_right && !shift_down){
		aliens_march_left();
	}


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

bool aliens_is_alive_down(uint16_t x, uint16_t y){
	if(x==5){
		return false;
	}
	else{
		return ALIEN_ALIVE(x, y+1);
	}
}

void aliens_kill(uint16_t index){
	alien_lives_matter[index] = false;
}


void alien_add_block_offset(point_t* alien_origin){
	(*alien_origin).x += alien_block_origin.x;
	(*alien_origin).y += alien_block_origin.y;
}

point_t alien_atHere(uint16_t x, uint16_t y){
	point_t alien_origin =  alien_rel_origins[ALIEN_XY_TO_INDEX(x,y)];
	alien_add_block_offset(&alien_origin);
	return alien_origin;
}

point_t alien_atRight(uint16_t x, uint16_t y){
	point_t alien_origin = alien_rel_origins[ALIEN_XY_TO_INDEX((x+1),y)];
	alien_add_block_offset(&alien_origin);
	return alien_origin;
}

point_t alien_atLeft(uint16_t x, uint16_t y){
	point_t alien_origin =  alien_rel_origins[ALIEN_XY_TO_INDEX(x-1,y)];
	alien_add_block_offset(&alien_origin);
	return alien_origin;
}

point_t alien_atDown(uint16_t x, uint16_t y){
	point_t alien_origin =  alien_rel_origins[ALIEN_XY_TO_INDEX(x,y+1)];
	alien_add_block_offset(&alien_origin);
	return alien_origin;
}
