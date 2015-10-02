#include "bunkers.h"

#define BUNKER_START_XOFFSET 24*BUNKER_SCALE

static point_t bunker_origins[4];

void bunkers_draw();
void bunkers_init_origins();

//-----------------------------------------------------------------------------

void bunkers_init() {
	// create the origins of the bunkers
	bunkers_init_origins();

	// draw the origins
	bunkers_draw();
}

//-----------------------------------------------------------------------------

// overlay given bunker with a random errosion pattern
void bunkers_damage(uint16_t index){
	uint16_t r = rand();
	point_t origin = bunker_origins[index];
	origin.x += r%(BUNKER_WIDTH*BUNKER_SCALE);
	origin.y += -r%(BUNKER_SCALE*10);
	const uint32_t* symbol = bunker_damage_symbols[r%3];
	// draw the symbol to the sreen
	screen_drawSymbol(symbol, origin, bunker_damage_size, 3, SCREEN_BG_COLOR);
	// also update the background frame (used for reference only)
	screen_bgDrawSymbol(symbol, origin, bunker_damage_size, 3, SCREEN_BG_COLOR);
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// initialize bunkers
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

//-----------------------------------------------------------------------------

// draw all bunkers to the screen
void bunkers_draw(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = bunker_origins[i];
		screen_drawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
		screen_bgDrawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
	}

}
