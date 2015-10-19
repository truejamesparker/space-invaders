#ifndef ALIENS_H_
#define ALIENS_H_

#include <stdint.h>

#include "gameScreen.h"
#include "../screen/screen.h"
#include "../globals.h"
#include "bunkers.h"


#define ALIEN_COL_COUNT 		11
#define ALIEN_ROW_COUNT 		5
#define ALIEN_COUNT 			(ALIEN_COL_COUNT*ALIEN_ROW_COUNT)
#define ALIEN_SCALE				2
#define ALIEN_COLOR				SCREEN_COLOR_WHITE
#define ALIEN_WIDTH 			(BITMAP_ALIEN_WIDTH*ALIEN_SCALE)
#define ALIEN_HEIGHT 			(BITMAP_ALIEN_HEIGHT*ALIEN_SCALE)
#define ALIEN_LOW_COORDINATE	0
#define ALIEN_HIGH_COORDINATE	(ALIEN_COUNT-1)

#define ALIEN_SHIFT_X			3
#define ALIEN_SHIFT_Y			6

#define ALIEN_PADDING_X			(ALIEN_SCALE*4)
#define ALIEN_PADDING_Y			(ALIEN_SCALE*5)

// scoring
#define ALIEN_SCORE_ELITE_VALUE		40
#define ALIEN_SCORE_INFANTRY_VALUE	20
#define ALIEN_SCORE_GRUNT_VALUE		10


// Direction parameters to pass into alien_march_dir(int dir)
#define ALIEN_MARCH_RIGHT	6
#define ALIEN_MARCH_LEFT	4
#define ALIEN_MARCH_DOWN	2
#define ALIEN_MARCH_UP		8


/****
 * Macro definitions
 */

#define ALIEN_XY_TO_INDEX(x,y) 	((y)*ALIEN_COL_COUNT + (x))
#define ALIEN_ALIVE(x,y) 		(alien_lives_matter[ALIEN_XY_TO_INDEX((x),(y))])


 /****
 * Struct definitions 
 */

typedef struct {
	const uint32_t* in; 			// alien "in" bitmap
	const uint32_t* out; 			// alien "out" bitmap
	const symbolsize_t* bitmapSize; 	// size of alien bitmap
	const uint32_t scoreValue;		// score value of the alien
} alien_t;

// array of the 3 types of aliens (elite, infantry, and grunt)

static const alien_t alien_symbols[ALIEN_ROW_COUNT] = {
		/** Elite Aliens **/

		{
				.in = alien_top_in_12x8,
				.out = alien_top_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_ELITE_VALUE
		},

		/** Infantry Aliens **/

		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_INFANTRY_VALUE
		},
		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_INFANTRY_VALUE
		},

		/** Grunt Aliens **/

		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_GRUNT_VALUE
		},
		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_GRUNT_VALUE
		}
};

/****
 * Function prototypes
 */

// Initialize the alien states and draw onto screen
void aliens_init();

// updates alien march sequence
void aliens_march();

// kill alien at specified index
void aliens_kill(uint16_t index);

// return the origin of the alien at the coordinates 
// coordinates within the alien block (i.e. row 1, col 2)
point_t aliens_getAlienOrigin(uint16_t x, uint16_t y);

// Ask if a particular (x,y) alien is still alive
bool alien_isAlive(uint16_t x, uint16_t y);

// Convert a particular (x,y) alien to an array index
uint16_t alien_xy_to_index(uint16_t x , uint16_t y);

// Get a list of the bottom-most aliens
void aliens_getLowestAliens(uint16_t *xArray, uint16_t *yArray);

// How many aliens are still alive?
uint32_t aliens_areLiving();

// clean up the mess of dead aliens
void aliens_cleanupKills();

// are the lowest living aliens below the bunkers?
bool aliens_belowBunkers();

// move alien block
void aliens_left();
void aliens_right();
void aliens_up();
void aliens_down();
uint16_t aliens_get_lowest_y();
uint16_t aliens_getFiringCount();

#endif /* ALIENS_H_ */
