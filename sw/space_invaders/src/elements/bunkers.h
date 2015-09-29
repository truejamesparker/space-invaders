#ifndef BUNKERS_H_
#define BUNKERS_H_

#include "../globals.h"
#include "../screen/screen.h"
#include <stdlib.h>

#define BUNKER_COUNT		4
#define BUNKER_COLOR		0x32CD32
#define BUNKER_SCALE 		SCALE
#define BUNKER_WIDTH		24
#define BUNKER_HEIGHT		18

static const symbolsize_t bunker_size= {
		.w = 24,
		.h = 18
};

static const symbolsize_t bunker_damage_size = {
		.w = 6,
		.h = 6
};

void bunkers_draw();
void bunkers_init_origins();
void bunkers_damage(uint16_t index);

#endif /* BUNKERS_H_ */
