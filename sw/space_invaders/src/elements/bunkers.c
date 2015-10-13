#include "bunkers.h"

#define BUNKER_START_XOFFSET 	24*BUNKER_SCALE

static bunker_t bunker_array[4];
static point_t bunker_sub_origins[40];
static int32_t bunker_state[4] = {0,0,0,0};

// size of bunker bitmap
static const symbolsize_t bunker_size = {
		.w = 24,
		.h = 18
};


void bunkers_draw();
void bunkers_init_origins();
void bunkers_init_sub_origins(point_t origin, point_t *sub_points);

//-----------------------------------------------------------------------------

void bunkers_init() {
	// create the origins of the bunkers
	bunkers_init_origins();

	// draw the origins
	bunkers_draw();
}

//-----------------------------------------------------------------------------

//void bunkers_get_contact_point(point_t point){
//
//}


// overlay given bunker with a random erosion pattern
// TODO: make this function accept an point param rather than using rand
void bunkers_damage(point_t point){
	const uint32_t* symbol = bunker_damage_symbols[2];
	// draw the symbol to the screen
	screen_drawSymbol(symbol, point, bunker_damage_size, 3, SCREEN_BG_COLOR);
	// also update the background frame (used for reference only)
	screen_bgDrawSymbol(symbol, point, bunker_damage_size, 3, SCREEN_BG_COLOR);
}



//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// initialize bunkers
void bunkers_init_origins(){
	uint16_t i;
	bunker_t* bunker;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = {
				.x = i * 148 + BUNKER_START_XOFFSET,
				.y = 3*(SCREEN_HEIGHT)/4
		};
		bunker = &bunker_array[i];
		bunker->origin = origin;
		bunker->size = bunker_size;
		bunker->status=0;

		bunker->sub_points = (point_t*)malloc(4);
		bunkers_init_sub_origins(origin, bunker->sub_points);

	}
}

void bunkers_init_sub_origins(point_t origin, point_t *sub_points) {
	int i, j, x_offset=0, y_offset=0;
	for(j=0; j<3; j++){
		for(i=0; i<4; i++){
			sub_points[j*4+i].x += x_offset;
			sub_points[j*4+i].y += y_offset;
			x_offset += (BUNKER_WIDTH*BUNKER_SCALE)/4;
		}
		y_offset += (BUNKER_HEIGHT*BUNKER_SCALE)/3;
	}
}

//-----------------------------------------------------------------------------

// draw all bunkers to the screen
void bunkers_draw(){
	uint16_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = bunker_array[i].origin;
		screen_drawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
		screen_bgDrawSymbol(bunker_24x18, origin, bunker_size,
				BUNKER_SCALE, BUNKER_COLOR);
	}

}

bunker_t* bunkers_get_origins(){
	return bunker_array;
}
