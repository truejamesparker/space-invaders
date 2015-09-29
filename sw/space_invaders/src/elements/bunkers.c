#include "bunkers.h"

#define BUNKER_START_XOFFSET 24*BUNKER_SCALE

static point_t bunker_origins[4];
static uint32_t* bunker_damage_symbols[3] = {bunkerDamage0_6x6, bunkerDamage1_6x6, bunkerDamage2_6x6};


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
		screen_drawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
		screen_bgDrawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
	}

}


void bunkers_damage(uint16_t index){
	uint16_t r = rand();
	point_t origin = bunker_origins[index];
	origin.x += r%(BUNKER_WIDTH*BUNKER_SCALE);
	origin.y += -r%(BUNKER_SCALE*10);
	uint32_t* symbol = bunker_damage_symbols[r%2];
	screen_drawSymbol(symbol, origin, bunker_damage_size, 3, SCREEN_BG_COLOR);
	screen_bgDrawSymbol(symbol, origin, bunker_damage_size, 3, SCREEN_BG_COLOR);


}
