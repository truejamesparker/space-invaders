/*
 * text.c
 *
 *  Created on: Sep 29, 2015
 *      Author: superman
 */

#include "text.h"

//static int string_game_over[9] = {G, A, M, E, SPACE, O, V, E, R};
static char string_game_over[4] = {'G', 'A', 'M', 'E'};

static int string_lives[6] = {L, I, V, E, S, COLON};

static int gwidth = 0;

void font_get_char(char letter, symbolsize_t* symbol, uint32_t** letter_array){
	xil_printf("%c\n\r", letter);
	int index = letter - fontInfo.startChar;
	xil_printf("letter info index: %d\n\r", index);
	FONT_CHAR_INFO info = fontInfo.charInfo[index];
	symbol->w = info.widthBits + 4;
	symbol->h = 9;
	gwidth = info.widthBits;
	xil_printf("width: %d, offset: %d, height %d\n\r", info.widthBits, info.offset, symbol->h);

	*letter_array = &(bitmaps[info.offset]);
}

void text_print(point_t origin_start, char* string, uint8_t length, uint16_t scale, uint32_t color){
	int i, shift;
	xil_printf("string len: %d\n\r", length);
	point_t origin = origin_start;
	symbolsize_t charsize;
	uint32_t* letter;

	for(i=0; i<length; i++){
		if (string[i] == ' '){
			origin.x += fontInfo.spacePixels*scale;
		}
		else{
			font_get_char(string[i], &charsize, &letter);
			xil_printf("%d\n\r", shift);
			xil_printf("first line: %02X\n\r", letter[0]);

	//		screen_bgDrawSymbol(letter, origin, charsize, scale, color);
			screen_drawSymbol(letter, origin, charsize, scale, color);

			shift = charsize.w*scale;
			origin.x += shift;
		}
	}
}

void text_print_game_over(){
	point_t origin;
	origin.y = SCREEN_HEIGHT/2;
	origin.x = (SCREEN_WIDTH/3);
	text_print(origin, "GAME OVER", 9, 2, SCREEN_COLOR_RED);
}



// Character bitmaps for Gill Sans MT 9pt
const int bitmaps[] =
{
		// @0 '0' (6 pixels wide)
		0x78, //  ####
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0x78, //  ####
		0x00, //
		0x00, //

		// @10 '1' (6 pixels wide)
		0x30, //   ##
		0xF0, // ####
		0x30, //   ##
		0x30, //   ##
		0x30, //   ##
		0x30, //   ##
		0x30, //   ##
		0xFC, // ######
		0x00, //
		0x00, //

		// @20 '2' (6 pixels wide)
		0xF8, // #####
		0x8C, // #   ##
		0x0C, //     ##
		0x18, //    ##
		0x30, //   ##
		0x60, //  ##
		0xC4, // ##   #
		0xFC, // ######
		0x00, //
		0x00, //

		// @30 '3' (6 pixels wide)
		0xF8, // #####
		0x8C, // #   ##
		0x0C, //     ##
		0x38, //   ###
		0x0C, //     ##
		0x0C, //     ##
		0x8C, // #   ##
		0xF8, // #####
		0x00, //
		0x00, //

		// @40 '4' (6 pixels wide)
		0x18, //    ##
		0x38, //   ###
		0x58, //  # ##
		0x58, //  # ##
		0x98, // #  ##
		0xFC, // ######
		0x18, //    ##
		0x3C, //   ####
		0x00, //
		0x00, //

		// @50 '5' (5 pixels wide)
		0xF8, // #####
		0xC0, // ##
		0xC0, // ##
		0xF0, // ####
		0x18, //    ##
		0x18, //    ##
		0x98, // #  ##
		0xF0, // ####
		0x00, //
		0x00, //

		// @60 '6' (6 pixels wide)
		0x38, //   ###
		0x60, //  ##
		0xC0, // ##
		0xF8, // #####
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0x78, //  ####
		0x00, //
		0x00, //

		// @70 '7' (6 pixels wide)
		0xFC, // ######
		0x8C, // #   ##
		0x18, //    ##
		0x18, //    ##
		0x30, //   ##
		0x30, //   ##
		0x60, //  ##
		0x60, //  ##
		0x00, //
		0x00, //

		// @80 '8' (6 pixels wide)
		0x78, //  ####
		0xCC, // ##  ##
		0xCC, // ##  ##
		0x78, //  ####
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0x78, //  ####
		0x00, //
		0x00, //

		// @90 '9' (6 pixels wide)
		0x78, //  ####
		0xCC, // ##  ##
		0xCC, // ##  ##
		0xCC, // ##  ##
		0x7C, //  #####
		0x0C, //     ##
		0x18, //    ##
		0x70, //  ###
		0x00, //
		0x00, //

		// @100 'A' (8 pixels wide)
		0x18, //    ##
		0x18, //    ##
		0x2C, //   # ##
		0x2C, //   # ##
		0x46, //  #   ##
		0x7E, //  ######
		0x46, //  #   ##
		0xEF, // ### ####
		0x00, //
		0x00, //

		// @110 'B' (7 pixels wide)
		0xFC, // ######
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x7C, //  #####
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0xFC, // ######
		0x00, //
		0x00, //

		// @120 'C' (6 pixels wide)
		0x3C, //   ####
		0x64, //  ##  #
		0xC0, // ##
		0xC0, // ##
		0xC0, // ##
		0xC0, // ##
		0x64, //  ##  #
		0x3C, //   ####
		0x00, //
		0x00, //

		// @130 'D' (7 pixels wide)
		0xF8, // #####
		0x6C, //  ## ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x6C, //  ## ##
		0xF8, // #####
		0x00, //
		0x00, //

		// @140 'E' (6 pixels wide)
		0xFC, // ######
		0x64, //  ##  #
		0x60, //  ##
		0x78, //  ####
		0x60, //  ##
		0x60, //  ##
		0x64, //  ##  #
		0xFC, // ######
		0x00, //
		0x00, //

		// @150 'F' (6 pixels wide)
		0xFC, // ######
		0x64, //  ##  #
		0x60, //  ##
		0x78, //  ####
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0xF0, // ####
		0x00, //
		0x00, //

		// @160 'G' (8 pixels wide)
		0x3E, //   #####
		0x62, //  ##   #
		0xC0, // ##
		0xC0, // ##
		0xCF, // ##  ####
		0xC6, // ##   ##
		0x66, //  ##  ##
		0x3E, //   #####
		0x00, //
		0x00, //

		// @170 'H' (8 pixels wide)
		0xF7, // #### ###
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x7E, //  ######
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0xF7, // #### ###
		0x00, //
		0x00, //

		// @180 'I' (4 pixels wide)
		0xF0, // ####
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0xF0, // ####
		0x00, //
		0x00, //

		// @190 'J' (4 pixels wide)
		0xF0, // ####
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0xC0, // ##

		// @200 'K' (8 pixels wide)
		0xF7, // #### ###
		0x62, //  ##   #
		0x64, //  ##  #
		0x78, //  ####
		0x6C, //  ## ##
		0x6C, //  ## ##
		0x66, //  ##  ##
		0xF7, // #### ###
		0x00, //
		0x00, //

		// @210 'L' (6 pixels wide)
		0xF0, // ####
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x60, //  ##
		0x64, //  ##  #
		0xFC, // ######
		0x00, //
		0x00, //

		// @220 'M' (9 pixels wide)
		0xE38, // ###   ###
		0x770, //  ### ###
		0x770, //  ### ###
		0x5B0, //  # ## ##
		0x5B0, //  # ## ##
		0x5B0, //  # ## ##
		0x430, //  #    ##
		0xE78, // ###  ####
		0x000, //
		0x000, //

		// @240 'N' (7 pixels wide)
		0xEE, // ### ###
		0x64, //  ##  #
		0x74, //  ### #
		0x74, //  ### #
		0x5C, //  # ###
		0x5C, //  # ###
		0x4C, //  #  ##
		0xEC, // ### ##
		0x00, //
		0x00, //

		// @250 'O' (7 pixels wide)
		0x38, //   ###
		0x6C, //  ## ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0x6C, //  ## ##
		0x38, //   ###
		0x00, //
		0x00, //

		// @260 'P' (7 pixels wide)
		0xFC, // ######
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x7C, //  #####
		0x60, //  ##
		0x60, //  ##
		0xF0, // ####
		0x00, //
		0x00, //

		// @270 'Q' (7 pixels wide)
		0x38, //   ###
		0x6C, //  ## ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0xC6, // ##   ##
		0x6C, //  ## ##
		0x38, //   ###
		0x18, //    ##
		0x0E, //     ###

		// @280 'R' (8 pixels wide)
		0xFC, // ######
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x66, //  ##  ##
		0x7C, //  #####
		0x6C, //  ## ##
		0x66, //  ##  ##
		0xF7, // #### ###
		0x00, //
		0x00, //

		// @290 'S' (5 pixels wide)
		0x78, //  ####
		0xC8, // ##  #
		0xC0, // ##
		0xF0, // ####
		0x78, //  ####
		0x18, //    ##
		0x98, // #  ##
		0xF0, // ####
		0x00, //
		0x00, //

		// @300 'T' (8 pixels wide)
		0xFF, // ########
		0x99, // #  ##  #
		0x18, //    ##
		0x18, //    ##
		0x18, //    ##
		0x18, //    ##
		0x18, //    ##
		0x3C, //   ####
		0x00, //
		0x00, //

		// @310 'U' (7 pixels wide)
		0xEE, // ### ###
		0x64, //  ##  #
		0x64, //  ##  #
		0x64, //  ##  #
		0x64, //  ##  #
		0x64, //  ##  #
		0x64, //  ##  #
		0x38, //   ###
		0x00, //
		0x00, //

		// @320 'V' (8 pixels wide)
		0xF7, // #### ###
		0x62, //  ##   #
		0x62, //  ##   #
		0x34, //   ## #
		0x34, //   ## #
		0x34, //   ## #
		0x18, //    ##
		0x18, //    ##
		0x00, //
		0x00, //

		// @330 'W' (11 pixels wide)
		0xE66, // ###  ##  ##
		0x664, //  ##  ##  #
		0x664, //  ##  ##  #
		0x6B4, //  ## # ## #
		0x6B4, //  ## # ## #
		0x398, //   ###  ##
		0x318, //   ##   ##
		0x318, //   ##   ##
		0x000, //
		0x000, //

		// @350 'X' (7 pixels wide)
		0xEE, // ### ###
		0x64, //  ##  #
		0x68, //  ## #
		0x38, //   ###
		0x38, //   ###
		0x2C, //   # ##
		0x4C, //  #  ##
		0xEE, // ### ###
		0x00, //
		0x00, //

		// @360 'Y' (8 pixels wide)
		0xF7, // #### ###
		0x62, //  ##   #
		0x34, //   ## #
		0x34, //   ## #
		0x18, //    ##
		0x18, //    ##
		0x18, //    ##
		0x3C, //   ####
		0x00, //
		0x00, //

		// @370 'Z' (6 pixels wide)
		0xFC, // ######
		0x8C, // #   ##
		0x18, //    ##
		0x30, //   ##
		0x30, //   ##
		0x60, //  ##
		0xC4, // ##   #
		0xFC, // ######
		0x00, //
		0x00, //
};

// Character descriptors for Gill Sans MT 9pt
// { [Char width in bits], [Offset into gillSansMT_9ptCharBitmaps in bytes] }
const FONT_CHAR_INFO descriptors[] =
{
		{6, 0}, 		// 0
		{6, 10}, 		// 1
		{6, 20}, 		// 2
		{6, 30}, 		// 3
		{6, 40}, 		// 4
		{5, 50}, 		// 5
		{6, 60}, 		// 6
		{6, 70}, 		// 7
		{6, 80}, 		// 8
		{6, 90}, 		// 9
		{0, 0}, 		// :
		{0, 0}, 		// ;
		{0, 0}, 		// <
		{0, 0}, 		// =
		{0, 0}, 		// >
		{0, 0}, 		// ?
		{0, 0}, 		// @
		{8, 100}, 		// A
		{7, 110}, 		// B
		{6, 120}, 		// C
		{7, 130}, 		// D
		{6, 140}, 		// E
		{6, 150}, 		// F
		{8, 160}, 		// G
		{8, 170}, 		// H
		{4, 180}, 		// I
		{4, 190}, 		// J
		{8, 200}, 		// K
		{6, 210}, 		// L
		{9, 220}, 		// M
		{7, 230}, 		// N
		{7, 240}, 		// O
		{7, 250}, 		// P
		{7, 260}, 		// Q
		{8, 270}, 		// R
		{5, 280}, 		// S
		{8, 290}, 		// T
		{7, 300}, 		// U
		{8, 310}, 		// V
		{11, 320}, 		// W
		{7, 330}, 		// X
		{8, 340}, 		// Y
		{6, 350}, 		// Z
};

// Font information
const FONT_INFO fontInfo =
{
	2, //  Character height
	'0', //  Start character
	'Z', //  End character
	2, //  Width, in pixels, of space character
	descriptors, //  Character descriptor array
	bitmaps, //  Character bitmap array
};




