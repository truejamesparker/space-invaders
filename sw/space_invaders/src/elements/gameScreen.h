#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <stdio.h>
#include <stdint.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "../text/text.h"

/** Floor static game element **/
#define FLOOR_COLOR		SCREEN_COLOR_GREEN
#define FLOOR_ORIGIN_X	0
#define FLOOR_ORIGIN_Y	(SCREEN_HEIGHT - (5*SCREEN_EDGE_BUFFER)/3)
#define FLOOR_WIDTH		32
#define FLOOR_HEIGHT	2
#define FLOOR_SCALE		1

// space after the "SCORE" and "LIVES"
#define POST_TEXT_PADDING	10

/** Score static game element **/
// the text
#define SCORE_TXT_COLOR		SCREEN_COLOR_WHITE
#define SCORE_TXT_ORIGIN_X	SCREEN_EDGE_BUFFER
#define SCORE_TXT_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define SCORE_TXT_WIDTH		30
#define SCORE_TXT_HEIGHT	5
#define SCORE_TXT_SCALE		2
// the number
#define SCORE_VAL_COLOR		SCREEN_COLOR_GREEN
#define SCORE_VAL_ORIGIN_X	((SCORE_TXT_ORIGIN_X+SCORE_TXT_WIDTH*SCORE_TXT_SCALE)+POST_TEXT_PADDING)
#define SCORE_VAL_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define SCORE_VAL_SCALE		2
// Max score
#define SCORE_VAL_MAX_LEN	6
#define SCORE_VAL_MAX		999999

/** Lives static game element **/
// Tank info
#define LIVES_TANK_COLOR	SCREEN_COLOR_GREEN
#define LIVES_TANK_WIDTH	15
#define LIVES_TANK_HEIGHT	8
#define LIVES_TANK_PADDING	4
#define LIVES_TANK_SCALE	2
// Max tank lives
#define LIVES_MAX			3
// the text
#define LIVES_TXT_COLOR		SCREEN_COLOR_WHITE
#define LIVES_TXT_ORIGIN_X	((((SCREEN_WIDTH-SCREEN_EDGE_BUFFER)-LIVES_TXT_WIDTH*LIVES_TXT_SCALE)- \
								LIVES_MAX*(LIVES_TANK_WIDTH+LIVES_TANK_PADDING)*LIVES_TANK_SCALE)- \
								POST_TEXT_PADDING)
#define LIVES_TXT_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define LIVES_TXT_WIDTH		24
#define LIVES_TXT_HEIGHT	5
#define LIVES_TXT_SCALE		2
// Tank position info
#define LIVES_TANK_ORIGIN_X	((LIVES_TXT_ORIGIN_X+LIVES_TXT_WIDTH*LIVES_TXT_SCALE)+POST_TEXT_PADDING)
#define LIVES_TANK_ORIGIN_Y	(SCREEN_EDGE_BUFFER-3*LIVES_TANK_SCALE)


// Initialize the screen by drawing all the
// static elements (floor, lives, score)
void gameScreen_init();

// increase/decrease the score of the game
uint32_t gameScreen_increaseScore(int32_t score);

// increase/decrease the tank lives
uint8_t gameScreen_increaseLives(int8_t lives);


#endif /* GAMESCREEN_H_ */
