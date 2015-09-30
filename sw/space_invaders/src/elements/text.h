/*
 * text.h
 *
 *  Created on: Sep 29, 2015
 *      Author: superman
 */

#ifndef TEXT_H_
#define TEXT_H_


#include "../globals.h"
#include "../screen/screen.h"
#define TEXT_SCALE 2

void text_print_game_over();


static const int ZERO[] = { // @0 '0' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int ONE[] = {	// @10 '1' (3 pixels wide)
	0x20, //   #
	0xE0, // ###
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x00, //
};


static const int TWO[] = {	// @20 '2' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x10, //    #
	0x20, //   #
	0x40, //  #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const int THREE[] = {	// @30 '3' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x30, //   ##
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int FOUR[] = {	// @40 '4' (5 pixels wide)
	0x10, //    #
	0x30, //   ##
	0x30, //   ##
	0x50, //  # #
	0x50, //  # #
	0x90, // #  #
	0xF8, // #####
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const int FIVE[] = {	// @50 '5' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int SIX[] = {	// @60 '6' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int SEVEN[] = {	// @70 '7' (5 pixels wide)
	0xF8, // #####
	0x08, //     #
	0x10, //    #
	0x10, //    #
	0x20, //   #
	0x20, //   #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x00, //
};


static const int EIGHT[] = {	// @80 '8' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int NINE[] = {	// @90 '9' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int A[] = {	// @100 'A' (7 pixels wide)
	0x10, //    #
	0x10, //    #
	0x28, //   # #
	0x28, //   # #
	0x44, //  #   #
	0x44, //  #   #
	0x7C, //  #####
	0x82, // #     #
	0x82, // #     #
	0x00, //
};


static const int B[] = {	// @110 'B' (5 pixels wide)
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // ####
	0x00, //
};


static const int C[] = {	// @120 'C' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const int D[] = {	// @130 'D' (6 pixels wide)
	0xF0, // ####
	0x88, // #   #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x88, // #   #
	0xF0, // ####
	0x00, //
};


static const int E[] = {	// @140 'E' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const int F[] = {	// @150 'F' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const int G[] = {	// @160 'G' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x80, // #
	0x80, // #
	0x9C, // #  ###
	0x84, // #    #
	0x84, // #    #
	0x8C, // #   ##
	0x74, //  ### #
	0x00, //
};


static const int H[] = {	// @170 'H' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xFC, // ######
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //
};


static const int I[] = {	// @180 'I' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const int J[] = {	// @190 'J' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x90, // #  #
	0x90, // #  #
	0x60, //  ##
	0x00, //
};


static const int K[] = {	// @200 'K' (6 pixels wide)
	0x88, // #   #
	0x90, // #  #
	0xA0, // # #
	0xC0, // ##
	0xC0, // ##
	0xA0, // # #
	0x90, // #  #
	0x88, // #   #
	0x84, // #    #
	0x00, //
};


static const int L[] = {	// @210 'L' (5 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const int M[] = {	// @220 'M' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xAA, // # # # #
	0xAA, // # # # #
	0x92, // #  #  #
	0x92, // #  #  #
	0x82, // #     #
	0x00, //
};


static const int N[] = {	// @230 'N' (6 pixels wide)
	0x84, // #    #
	0xC4, // ##   #
	0xC4, // ##   #
	0xA4, // # #  #
	0xA4, // # #  #
	0x94, // #  # #
	0x8C, // #   ##
	0x8C, // #   ##
	0x84, // #    #
	0x00, //
};


static const int O[] = {	// @240 'O' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const int P[] = {	// @250 'P' (6 pixels wide)
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const int Q[] = {	// @260 'Q' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x94, // #  # #
	0x8C, // #   ##
	0x78, //  ####
	0x04, //      #
};


static const int R[] = {	// @270 'R' (6 pixels wide)
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //
};


static const int S[] = {	// @280 'S' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x80, // #
	0x80, // #
	0x70, //  ###
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int T[] = {	// @290 'T' (5 pixels wide)
	0xF8, // #####
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x00, //
};


static const int U[] = {	// @300 'U' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const int V[] = {	// @310 'V' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x44, //  #   #
	0x44, //  #   #
	0x28, //   # #
	0x28, //   # #
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const int W[] = {	// @320 'W' (11 pixels wide)
	0x80, 	0x20, // #         #
	0x80, 	0x20, // #         #
	0x44, 	0x40, //  #   #   #
	0x44, 	0x40, //  #   #   #
	0x44, 	0x40, //  #   #   #
	0x2A, 	0x80, //   # # # #
	0x2A, 	0x80, //   # # # #
	0x11, 	0x00, //    #   #
	0x11, 	0x00, //    #   #
	0x00, 	0x00, //
};


static const int X[] = {	// @340 'X' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x28, //   # #
	0x10, //    #
	0x28, //   # #
	0x44, //  #   #
	0x82, // #     #
	0x82, // #     #
	0x00, //
};


static const int Y[] = {	// @350 'Y' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x28, //   # #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const int Z[] = {	// @360 'Z' (7 pixels wide)
	0xFE, // #######
	0x02, //       #
	0x04, //      #
	0x08, //     #
	0x10, //    #
	0x20, //   #
	0x40, //  #
	0x80, // #
	0xFE, // #######
	0x00, //
};

static const int SPACE[] = { // @0 '0' (5 pixels wide)
	0x00, //  ###
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, //  ###
	0x00, //
};

#endif /* TEXT_H_ */
