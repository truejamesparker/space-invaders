/*
 * text.c
 *
 *  Created on: Sep 29, 2015
 *      Author: superman
 */

#include "text.h"

static int string_game_over[9] = {G, A, M, E, SPACE, O, V, E, R};

const symbolsize_t charsize = {
		.w = 8,
		.h = 9
};


void text_print(point_t origin_start, int* letter_array, uint16_t length, uint16_t scale){
	int i;
	uint16_t shift = charsize.w*SCALE;
	point_t origin = origin_start;

		for(i=0; i<length; i++){
			origin.x += shift;
			screen_drawSymbol(letter_array[i], origin,
					charsize, scale, SCREEN_COLOR_RED);
		}
}

void text_print_game_over(){
	point_t origin;
	origin.y = SCREEN_HEIGHT/2;
	origin.x = (SCREEN_WIDTH/2) - (9*charsize.w*TEXT_SCALE)/2;
	text_print(origin, string_game_over, 9, TEXT_SCALE);
}
