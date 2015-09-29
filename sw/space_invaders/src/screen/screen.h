#ifndef SCREEN_H_
#define SCREEN_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"

#include "../globals.h"

#define SCREEN_COLOR_BLACK	0x00000000
#define SCREEN_COLOR_TEAL 	0x0000FFFF
#define SCREEN_COLOR_RED	0x00FF0000
#define SCREEN_COLOR_GREEN	0x0000FF00
#define SCREEN_COLOR_ORANGE 0x00FF5A00
#define SCREEN_COLOR_BROWN 0x00F4A460

#define SCREEN_BG_COLOR				SCREEN_COLOR_BLACK
#define SCREEN_ELEM_OUTLINE 		SCREEN_COLOR_RED
#define SCREEN_ELEM_DIFF_OUTLINE	SCREEN_COLOR_GREEN
#define SCREEN_ORIGIN_COLOR			SCREEN_COLOR_BROWN

#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

#define SCREEN_EDGE_BUFFER 	20

#define FRAME_BUFFER_0_ADDR 0xC1000000

// For debugging positions, sizes and shifts
#define SCREEN_SHOW_MARGINS 0
#define SCREEN_SHIFT_BOX	0
#define SCREEN_SHOW_ORIGIN	0

/****
 * Macro definitions
 */

#define SCREEN_XY_TO_INDEX(x,y) (((y)*SCREEN_WIDTH) + (x))
#define SCREEN_SET_XY_TO_COLOR(x,y,color) (framePointer[SCREEN_XY_TO_INDEX((x),(y))] = color)
#define SCREEN_BG_SET_XY_TO_COLOR(x, y, color) (bgFramePointer[SCREEN_XY_TO_INDEX((x),(y))] = color)


/****
 * Function prototypes
 */

// init the screen, get parking ready, create a framePointer
void screen_init();

// clears the screen to the background color
void screen_clear();

// Causes the screen to park again, redrawing the framePointer to screen
void screen_refresh();

//
void screen_drawSymbol(const uint32_t* symbol, point_t origin, symbolsize_t size, uint16_t scale, uint32_t onColor);
void screen_bgDrawSymbol(const uint32_t* symbol, point_t origin, symbolsize_t size, uint16_t scale, uint32_t onColor);
void screen_shiftElement(const uint32_t* symbol, point_t origin, symbolsize_t size, int16_t dx, int16_t dy, uint16_t scale, uint32_t onColor);
uint32_t screen_getBgColor(uint16_t x, uint16_t y);
uint32_t screen_getScreenColor(uint16_t x, uint16_t y);

#endif /* SCREEN_H_ */
