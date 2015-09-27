/*
 * bunkers.h
 *
 *  Created on: Sep 26, 2015
 *      Author: superman
 */

#ifndef BUNKERS_H_
#define BUNKERS_H_

#include "../globals.h"
#include "../screen/screen.h"

#define BUNKER_COUNT		4
#define BUNKER_COLOR		0x32CD32
#define BUNKER_SCALE 		SCALE

static const symbolsize_t bunker_size= {
		.w = 24,
		.h = 18
};

void bunkers_draw();
void bunkers_init_origins();

#endif /* BUNKERS_H_ */
