/*
 * text.c
 *
 *  Created on: Sep 29, 2015
 *      Author: superman
 */

#include "text.h"

static int string_game_over[9] = {G, A, M, E, SPACE, O, V, E, R};
static int string_lives[6] = {L, I, V, E, S, COLON};


void text_print(point_t origin_start, int* letter_array, uint16_t length, uint16_t scale, uint32_t color){
	int i;
	uint16_t shift = charsize.w*SCALE;
	point_t origin = origin_start;

		for(i=0; i<length; i++){
			origin.x += shift;
			screen_drawSymbol(letter_array[i], origin,
					charsize, scale, color);
		}
}

void text_print_game_over(){
	point_t origin;
	origin.y = SCREEN_HEIGHT/2;
	origin.x = (SCREEN_WIDTH/2) - (9*charsize.w*TEXT_SCALE)/2;
	text_print(origin, string_game_over, 9, TEXT_SCALE, SCREEN_COLOR_RED);
}


void text_print_lives(){
	point_t origin;
	origin.y = charsize.h*TEXT_SCALE;
	origin.x = 5 * charsize.w;
	text_print(origin, string_lives, 6, 1, SCREEN_COLOR_GREEN);
}
