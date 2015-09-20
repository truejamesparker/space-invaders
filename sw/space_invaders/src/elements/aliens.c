#include "aliens.h"

static bool alien_lives_matter[ALIEN_COUNT] = { false };

static symbolsize_t alienSize = { .h = ALIEN_HEIGHT, .w = WORD_WIDTH };

//-----------------------------------------------------------------------------

bool* aliens_getLives() {
	return alien_lives_matter;
}

//-----------------------------------------------------------------------------

void init_tanks(int* pointer, int scale){
	uint16_t i;
	for(i=0; i<5; i++){
//		draw_symbol(bunker_24x18, pointer + 640*250 + (i*2*24)*scale, 24, 18, scale, 0x0000FFFF);
	}
}
//-----------------------------------------------------------------------------

void aliens_init_lives_array(){
	uint16_t i, size = sizeof(alien_lives_matter);
	for(i=0; i < size; i++){
		alien_lives_matter[i] = true;
	}
}


void aliens_draw(bool in) {
	uint16_t x = 0;
	uint16_t y = 0;

	// For every alien out of the all the aliens in the whole wide world...
	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		alien_t alien = alien_symbols[y];
//		xil_printf("%x\n", alien.in);
		for (x = 0; x < ALIEN_COL_COUNT; x++) {

			// This is the top-left of the symbol
			point_t alienOrigin = {
					.x = x * alien.size.w * ALIEN_SCALE,
					.y = y * alien.size.h * ALIEN_SCALE
			};

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(x,y)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			uint32_t* symbol = in ? alien.in : alien.out;
			// Tell the screen to draw my symbol
			screen_drawSymbol(symbol, alienOrigin, alien.size,
					ALIEN_SCALE, color);
		}
	}
}

void aliens_march_right(){
	uint16_t x = 0;
	uint16_t y = 0;

	// For every alien out of the all the aliens in the whole wide world...
	for (y = 0; y < ALIEN_ROW_COUNT; y++) {
		for (x = 0; x < ALIEN_COL_COUNT; x++) {

			// This is the top-left of the symbol
			point_t alienOrigin = {
					.x = x * WORD_WIDTH * ALIEN_SCALE,
					.y = y * ALIEN_HEIGHT * ALIEN_SCALE
			};

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(x,y)) ? ALIEN_COLOR : SCREEN_BG_COLOR;

			// Tell the screen to draw my symbol
			screen_drawSymbol(topOutAlienSymbol, alienOrigin, alienSize,
					ALIEN_SCALE, color);
		}
	}
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------
