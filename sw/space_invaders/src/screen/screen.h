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

#define SCREEN_BG_COLOR		SCREEN_COLOR_BLACK

#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

#define FRAME_BUFFER_0_ADDR 0xC1000000

/****
 * Macro definitions
 */

#define SCREEN_XY_TO_INDEX(x,y) (((y)*SCREEN_WIDTH) + (x))
#define SCREEN_SET_XY_TO_COLOR(x,y,color) (framePointer[SCREEN_XY_TO_INDEX((x),(y))] = color)

/****
 * Function prototypes
 */

// clears the screen to the background color
void screen_clear();

// Causes the screen to park again, redrawing the framePointer to screen
void screen_refresh();

//
void screen_drawSymbol(const uint32_t* symbol, point_t origin, symbolsize_t size, uint16_t scale, uint32_t onColor);


#endif /* SCREEN_H_ */
