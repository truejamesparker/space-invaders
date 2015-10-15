#ifndef TEXT_H_
#define TEXT_H_

#include <stdio.h>
#include <stdint.h>

#include "../globals.h"
#include "../screen/screen.h"

#define TEXT_EXPLODE_MAX		255
#define TEXT_NUMBER_PADDING		0

// Take an int, separate digits out into array
void text_explodeNumber(uint32_t number, uint32_t maxLength, uint8_t *array, uint8_t *length);

// Take in an exploded number array to print
void text_drawNumberString(uint8_t *array, uint8_t length, uint32_t maxLength,
							point_t origin, uint8_t scale, uint32_t color);

// given that you want some text centered, this will create an origin point for you
point_t text_getCenterStartPoint(uint16_t width, uint16_t height, uint8_t scale);

#endif /* TEXT_H_ */
