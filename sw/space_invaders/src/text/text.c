#include "text.h"

// ----------------------------------------------------------------------------

void text_explodeNumber(uint32_t number, uint32_t maxLength, uint8_t *array, uint8_t *length) {
	uint8_t tmpArray[TEXT_EXPLODE_MAX] = { 0 };
	uint8_t count = 0;
	int8_t i = (maxLength-1); // A backward counter to tell us which digit

	// If you passed in a single 0, make the appropriate array/length
	if (number == 0) {
		array[0] = 0;
		*length = 1;
		return;
	}

	// while there's still a number to explode out into an array
	while(number) {
		// Grab the digit
		tmpArray[i] = (number % 10);

		// Divide by 10 to get the next digit in the one's spot
		number /= 10;

		i--;
		count++;
	}

	uint8_t j = 0;
	// Push the tmpArray to the left, so the values are rightmost
	for (j=0; j<count; j++) array[j] = tmpArray[++i];

	// Let the caller now how many digits there are
	*length = count;
}

// ----------------------------------------------------------------------------

void text_drawNumberString(uint8_t *array, uint8_t length, uint32_t maxLength,
							point_t origin, uint8_t scale, uint32_t color) {
	uint8_t i = 0;

	for (i=0; i<maxLength; i++) {

		// Find out if this digit should be drawn or not
		uint32_t myColor = (i<length) ? color : SCREEN_BG_COLOR;

		uint32_t digit = array[i];
		screen_drawSymbol(numbers_5x5[digit], origin, numbersSize, scale, myColor);

		// Shift the origin over to the next spot
		origin.x += (numbersSize.w+TEXT_NUMBER_PADDING)*scale;
	}
}
