#ifndef ALIENS_H_
#define ALIENS_H_

#include <stdint.h>
#include <stdbool.h>

#include "../screen/screen.h"
#include "../globals.h"

#define ALIEN_COL_COUNT 		11
#define ALIEN_ROW_COUNT 		5
#define ALIEN_COUNT 			(ALIEN_COL_COUNT*ALIEN_ROW_COUNT)

#define ALIEN_SCALE		1
#define ALIEN_COLOR		SCREEN_COLOR_TEAL

/****
 * Macro definitions
 */

#define ALIEN_XY_TO_INDEX(x,y) 	((y)*ALIEN_COL_COUNT + (x))
#define ALIEN_ALIVE(x,y) 	(alien_lives_matter[ALIEN_XY_TO_INDEX((x),(y))])

/****
 * Function prototypes
 */

// Return the array of bools representing aliens lives
bool* aliens_getLives();

// Draw the aliens to the screen
void aliens_draw();


#endif /* ALIENS_H_ */
