#ifndef BUNKERS_H_
#define BUNKERS_H_

#include <stdlib.h>

#include "../globals.h"
#include "../screen/screen.h"

#define BUNKER_COUNT		4
#define BUNKER_COLOR		0x32CD32
#define BUNKER_SCALE 		SCALE // define the bunker scale (see globals.h)
#define BUNKER_WIDTH		24
#define BUNKER_HEIGHT		18

#define TANK_MISSILE 0
#define ALIEN_MISSILE1 1
#define ALIEN_MISSILE2 2
#define ALIEN_MISSILE3 3


// struct definintions

// size of bunker bitmap
static const symbolsize_t bunker_size= {
		.w = 24,
		.h = 18
};

// size of bumker-damage bitmap
static const symbolsize_t bunker_damage_size = {
		.w = 6,
		.h = 6
};

// array of three different types of bunker damage patterns
static const uint32_t* bunker_damage_symbols[3] = {bunkerDamage0_6x6, bunkerDamage1_6x6, bunkerDamage2_6x6};

// itiailize bunkers
void bunkers_init();

// erode the given bunker
void bunkers_damage(uint16_t index);

#endif /* BUNKERS_H_ */
