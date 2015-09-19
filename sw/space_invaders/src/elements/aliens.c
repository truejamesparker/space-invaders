#include "aliens.h"

static bool alien_lives_matter[ALIEN_COUNT] = { false };

static symbolsize_t alienSize = { .h = ALIEN_HEIGHT, .w = WORD_WIDTH };

//-----------------------------------------------------------------------------

bool* aliens_getLives() {
	return alien_lives_matter;
}

//-----------------------------------------------------------------------------

void aliens_draw() {
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
