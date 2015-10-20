#ifndef BUNKERS_H_
#define BUNKERS_H_

#include <stdlib.h>

#include "../globals.h"
#include "../screen/screen.h"

// bunker characteristics
#define BUNKER_COUNT		4
#define BUNKER_COLOR		0x32CD32

// define the bunker scale (see globals.h)
#define BUNKER_SCALE 			SCALE
#define BUNKER_ERODE_SCALE		2
#define BUNKER_WIDTH			(BITMAP_BUNKER_WIDTH*BUNKER_SCALE)
#define BUNKER_HEIGHT			(BITMAP_BUNKER_HEIGHT*BUNKER_SCALE)
#define BUNKER_START_XOFFSET 	((SCREEN_WIDTH/BUNKER_COUNT - BUNKER_WIDTH)/2)
#define BUNKER_START_Y			(3*(SCREEN_HEIGHT)/4)
#define BUNKER_END_Y			(BUNKER_START_Y+(BUNKER_HEIGHT*BUNKER_SCALE))

#define STATUS_BIT_LENGTH		3

// missile array indexes
#define TANK_MISSILE 		0
#define ALIEN_MISSILE1 		1
#define ALIEN_MISSILE2 		2
#define ALIEN_MISSILE3 		3

#define BUNKER_ERODED_STATUS		4
#define BUNKER_SUB_ORIGIN_COUNT 	10
#define BUNKER_SUB_ORIGIN_WIDTH		(BUNKER_WIDTH/4)
#define BUNKER_SUB_ORIGIN_HEIGHT	(BUNKER_HEIGHT/3)


// bunker struct definition
typedef struct {
	point_t origin;				// current location of missile
	symbolsize_t size;			// size of missile bitmap
	int32_t status;
	point_t *sub_points;
} bunker_t;


// itiailize bunkers
void bunkers_init();

// erode the given bunker
void bunkers_damage(uint8_t bunker_index, uint8_t sub_index);
bool bunkers_isPointEroded(uint8_t bunker_index, uint8_t sub_index);

// given an index, return that bunker struct
bunker_t bunkers_getBunker(uint8_t index);

#endif /* BUNKERS_H_ */
