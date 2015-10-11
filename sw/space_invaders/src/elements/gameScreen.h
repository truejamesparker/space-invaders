#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <stdio.h>
#include <stdint.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "../text/text.h"

#define FLOOR_COLOR		SCREEN_COLOR_GREEN
#define FLOOR_ORIGIN_X	0
#define FLOOR_ORIGIN_Y	(SCREEN_HEIGHT - 2*SCREEN_EDGE_BUFFER)
#define FLOOR_WIDTH		SCREEN_WIDTH
#define FLOOR_HEIGHT	2
#define FLOOR_SCALE		1

void gameScreen_init();


#endif /* GAMESCREEN_H_ */
