#ifndef ALIENS_H_
#define ALIENS_H_

#include <stdint.h>
#include <stdbool.h>

#include "../screen/screen.h"
#include "../globals.h"

#define ALIEN_COL_COUNT 		11
#define ALIEN_ROW_COUNT 		5
#define ALIEN_COUNT 			(ALIEN_COL_COUNT*ALIEN_ROW_COUNT)

#define ALIEN_SCALE		2
#define ALIEN_COLOR		SCREEN_COLOR_TEAL

/****
 * Macro definitions
 */

#define ALIEN_XY_TO_INDEX(x,y) 	((y)*ALIEN_COL_COUNT + (x))
#define ALIEN_ALIVE(x,y) 	(alien_lives_matter[ALIEN_XY_TO_INDEX((x),(y))])

/***
 * Struct definitions
 */

typedef struct{
	const uint32_t* in;
	const uint32_t* out;
	const symbolsize_t size;
} alien_t;

extern bool flapIn;

//static symbolsize_t alien_12x8 = {
//		.w = 12,
//};


static const alien_t alien_symbols[ALIEN_ROW_COUNT] = {
		{
				.in = alien_top_in_12x8,			// elite aliens
				.out = alien_top_out_12x8,
				.size = {.w = 12, .h = 8}
		},
		{
				.in = alien_middle_in_12x8,			// infantry aliens
				.out = alien_middle_out_12x8,
				.size = {.w = 12, .h = 8}
		},
		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.size = {.w = 12, .h = 8}
		},
		{
				.in = alien_bottom_in_12x8,			// grunt aliens
				.out = alien_bottom_out_12x8,
				.size = {.w = 12, .h = 8}
		},
		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.size = {.w = 12, .h = 8}
		}
};

/****
 * Function prototypes
 */

// Return the array of bools representing aliens lives
bool* aliens_getLives();

void init_alien_rel_origins();
void aliens_init_lives_array();

// Draw the aliens to the screen
void aliens_draw();

void aliens_march_right();

void aliens_march_left();

void aliens_march_down();


#endif /* ALIENS_H_ */
