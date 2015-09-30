#ifndef ALIENS_H_
#define ALIENS_H_

#include <stdint.h>

#include "../screen/screen.h"
#include "../globals.h"



#define ALIEN_COL_COUNT 		11
#define ALIEN_ROW_COUNT 		5
#define ALIEN_COUNT 			(ALIEN_COL_COUNT*ALIEN_ROW_COUNT)
#define ALIEN_SCALE				2
#define ALIEN_COLOR				SCREEN_COLOR_TEAL
#define ALIEN_WIDTH 			12
#define ALIEN_HEIGHT 			8
#define ALIEN_LOW_COORDINATE	0
#define ALIEN_HIGH_COORDINATE	(ALIEN_COUNT-1)

#define ALIEN_SHIFT_X			3
#define ALIEN_SHIFT_Y			6

#define ALIEN_PADDING_X			(ALIEN_SCALE*3)
#define ALIEN_PADDING_Y			(ALIEN_SCALE*2)

#define ALIEN_MARCH_RIGHT	6
#define ALIEN_MARCH_LEFT	4
#define ALIEN_MARCH_DOWN	2
#define ALIEN_MARCH_UP		8


/****
 * Macro definitions
 */

#define ALIEN_XY_TO_INDEX(x,y) 	((y)*ALIEN_COL_COUNT + (x))
#define ALIEN_ALIVE(x,y) 		(alien_lives_matter[ALIEN_XY_TO_INDEX((x),(y))])

/***
 * Struct definitions
 */

typedef struct{
	const uint32_t* in;
	const uint32_t* out;
	const symbolsize_t size;
} alien_t;

static const alien_t alien_symbols[ALIEN_ROW_COUNT] = {
		{
				.in = alien_top_in_12x8,			// elite aliens
				.out = alien_top_out_12x8,
				.size = {.w = ALIEN_WIDTH, .h = ALIEN_HEIGHT}
		},
		{
				.in = alien_middle_in_12x8,			// infantry aliens
				.out = alien_middle_out_12x8,
				.size = {.w = ALIEN_WIDTH, .h = ALIEN_HEIGHT}
		},
		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.size = {.w = ALIEN_WIDTH, .h = ALIEN_HEIGHT}
		},
		{
				.in = alien_bottom_in_12x8,			// grunt aliens
				.out = alien_bottom_out_12x8,
				.size = {.w = ALIEN_WIDTH, .h = ALIEN_HEIGHT}
		},
		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.size = {.w = ALIEN_WIDTH, .h = ALIEN_HEIGHT}
		}
};


static const symbolsize_t explosionsize = {
		.w = 12,
		.h = 10
};
/****
 * Function prototypes
 */

// Initialize the alien states and draw onto screen
void aliens_init();

void aliens_march();

void aliens_kill(uint16_t index);

point_t alien_getAlienOrigin(uint16_t x, uint16_t y);

void aliens_left();
void aliens_right();
void aliens_up();
void aliens_down();


#endif /* ALIENS_H_ */
