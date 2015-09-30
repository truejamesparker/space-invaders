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

#define TANK_MISSILE 0
#define ALIEN_MISSILE1 1
#define ALIEN_MISSILE2 2
#define ALIEN_MISSILE3 3

static const symbolsize_t bunker_size= {
		.w = 24,
		.h = 18
};

static const symbolsize_t bunker_damage_size = {
		.w = 6,
		.h = 6
};

static uint32_t* bunker_damage_symbols[3] = {bunkerDamage0_6x6, bunkerDamage1_6x6, bunkerDamage2_6x6};

void bunkers_draw();
void bunkers_init_origins();
void bunkers_damage(uint16_t index);

#endif /* BUNKERS_H_ */
