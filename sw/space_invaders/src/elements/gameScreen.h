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
#define FLOOR_SCALE		1
#define FLOOR_WIDTH		(BITMAP_FLOOR_WIDTH*FLOOR_SCALE)
#define FLOOR_HEIGHT	(BITMAP_FLOOR_HEIGHT*FLOOR_SCALE)

// space after the "SCORE" and "LIVES"
#define POST_TEXT_PADDING	10

/** Score static game element **/
// the text
#define SCORE_TXT_COLOR		SCREEN_COLOR_WHITE
#define SCORE_TXT_ORIGIN_X	SCREEN_EDGE_BUFFER
#define SCORE_TXT_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define SCORE_TXT_SCALE		2
#define SCORE_TXT_WIDTH		(BITMAP_WORD_SCORE_WIDTH*SCORE_TXT_SCALE)
#define SCORE_TXT_HEIGHT	(BITMAP_WORD_SCORE_HEIGHT*SCORE_TXT_SCALE)
// the number
#define SCORE_VAL_COLOR		SCREEN_COLOR_GREEN
#define SCORE_VAL_ORIGIN_X	((SCORE_TXT_ORIGIN_X+SCORE_TXT_WIDTH)+POST_TEXT_PADDING)
#define SCORE_VAL_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define SCORE_VAL_SCALE		2
// Max score
#define SCORE_VAL_MAX_LEN	6
#define SCORE_VAL_MAX		999999

/** Lives static game element **/
// Tank info
#define LIVES_TANK_COLOR	SCREEN_COLOR_GREEN
#define LIVES_TANK_SCALE	2
#define LIVES_TANK_WIDTH	(BITMAP_TANK_WIDTH*LIVES_TANK_SCALE)
#define LIVES_TANK_HEIGHT	(BITMAP_TANK_HEIGHT*LIVES_TANK_SCALE)
#define LIVES_TANK_PADDING	(4*LIVES_TANK_SCALE)
// Max tank lives
#define LIVES_MAX			3
// the text
#define LIVES_TXT_COLOR		SCREEN_COLOR_WHITE
#define LIVES_TXT_ORIGIN_X	((((SCREEN_WIDTH-SCREEN_EDGE_BUFFER)-LIVES_TXT_WIDTH)- \
								LIVES_MAX*(LIVES_TANK_WIDTH+LIVES_TANK_PADDING))- \
								POST_TEXT_PADDING)
#define LIVES_TXT_ORIGIN_Y	SCREEN_EDGE_BUFFER
#define LIVES_TXT_SCALE		2
#define LIVES_TXT_WIDTH		(BITMAP_WORD_LIVES_WIDTH*LIVES_TXT_SCALE)
#define LIVES_TXT_HEIGHT	(BITMAP_WORD_LIVES_HEIGHT*LIVES_TXT_SCALE)
// Tank position info
#define LIVES_TANK_ORIGIN_X	((LIVES_TXT_ORIGIN_X+LIVES_TXT_WIDTH)+POST_TEXT_PADDING)
#define LIVES_TANK_ORIGIN_Y	(SCREEN_EDGE_BUFFER-3*LIVES_TANK_SCALE)


#define GAME_OVER_SCALE		4
#define GAME_OVER_SPACE		(6*GAME_OVER_SCALE)

// Initialize the screen by drawing all the
// static elements (floor, lives, score)
void gameScreen_init();

// increase/decrease the score of the game
uint32_t gameScreen_increaseScore(int32_t score);

// increase/decrease the tank lives
uint8_t gameScreen_increaseLives(int8_t lives);

uint8_t gameScreen_getTankLives();

// print "GAME OVER" in the middle of screen
void gameScreen_printGameOver();

#endif /* GAMESCREEN_H_ */
