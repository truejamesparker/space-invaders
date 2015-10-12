#ifndef globals_h
#define globals_h

#include <stdint.h>
#include <stdbool.h>

// standard point struct
// x and y coordinates represent
// the screen pixel coordinates
typedef struct {
	uint16_t x;
	uint16_t y;
} point_t;

// standard symbol size struct
// defining both a width and height
typedef struct {
	uint16_t w;
	uint16_t h;
} symbolsize_t;


// These are currenlty unused but may be enabled later
void setTankPositionGlobal(unsigned short val);
unsigned short getTankPositionGlobal();
void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();


#define WORD_WIDTH 				32

// set the scale of the game
#define SCALE					2


// Packs each horizontal line of the figures into a single n-bit bit word.
#define packword32(b31,b30,b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b31 << 31) | (b30 << 30) | (b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword30(b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword24(b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) 								  \
((b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword16(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) 																  \
((b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword15(b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) 																      \
((b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  				  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword12(b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) 								  												  \
((b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						 								 						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | 																				  \
 (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword8(b7,b6,b5,b4,b3,b2,b1,b0) 																								  \
((b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword6(b5,b4,b3,b2,b1,b0) 																								      \
((b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword5(b4,b3,b2,b1,b0) 																								      \
((b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packword3(b2,b1,b0) 																								      \
((b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

// Image bitmaps for vaiarious graphical game elements

// Large main screen alien icon
static const uint32_t topOutAlienSymbol[] = {
	packword32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packword32(0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0)
};

// saucer
static const uint32_t saucer_16x7[] = {
		packword16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0),
		packword16(0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0),
		packword16(0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
		packword16(0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0),
		packword16(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword16(0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0),
		packword16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0) };

// explosion
static const uint32_t alien_explosion_12x10[] = {
		packword12(0,0,0,0,0,0,1,0,0,0,0,0),
		packword12(0,0,0,1,0,0,1,0,0,0,1,0),
		packword12(1,0,0,1,0,0,0,0,0,1,0,0),
		packword12(0,1,0,0,1,0,0,0,1,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,1,1),
		packword12(1,1,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,1,0,0,0,1,0,0,1,0),
		packword12(0,0,1,0,0,0,0,0,1,0,0,1),
		packword12(0,1,0,0,0,1,0,0,1,0,0,0),
		packword12(0,0,0,0,0,1,0,0,0,0,0,0) };

// the following characterize the vaious alien movements
// (arms up vs arms down)

static const uint32_t alien_top_in_12x8[] = {
		packword12(0,0,0,0,0,1,1,0,0,0,0,0),
		packword12(0,0,0,0,1,1,1,1,0,0,0,0),
		packword12(0,0,0,1,1,1,1,1,1,0,0,0),
		packword12(0,0,1,1,0,1,1,0,1,1,0,0),
		packword12(0,0,1,1,1,1,1,1,1,1,0,0),
		packword12(0,0,0,1,0,1,1,0,1,0,0,0),
		packword12(0,0,1,0,0,0,0,0,0,1,0,0),
		packword12(0,0,0,1,0,0,0,0,1,0,0,0) };

static const uint32_t alien_top_out_12x8[] = {
		packword12(0,0,0,0,0,1,1,0,0,0,0,0),
		packword12(0,0,0,0,1,1,1,1,0,0,0,0),
		packword12(0,0,0,1,1,1,1,1,1,0,0,0),
		packword12(0,0,1,1,0,1,1,0,1,1,0,0),
		packword12(0,0,1,1,1,1,1,1,1,1,0,0),
		packword12(0,0,0,0,1,0,0,1,0,0,0,0),
		packword12(0,0,0,1,0,1,1,0,1,0,0,0),
		packword12(0,0,1,0,1,0,0,1,0,1,0,0) };

static const uint32_t alien_middle_in_12x8[] = {
		packword12(0,0,0,1,0,0,0,0,0,1,0,0),
		packword12(0,0,0,0,1,0,0,0,1,0,0,0),
		packword12(0,0,0,1,1,1,1,1,1,1,0,0),
		packword12(0,0,1,1,0,1,1,1,0,1,1,0),
		packword12(0,1,1,1,1,1,1,1,1,1,1,1),
		packword12(0,1,1,1,1,1,1,1,1,1,1,1),
		packword12(0,1,0,1,0,0,0,0,0,1,0,1),
		packword12(0,0,0,0,1,1,0,1,1,0,0,0) };

static const uint32_t alien_middle_out_12x8[] = {
		packword12(0,0,0,1,0,0,0,0,0,1,0,0),
		packword12(0,1,0,0,1,0,0,0,1,0,0,1),
		packword12(0,1,0,1,1,1,1,1,1,1,0,1),
		packword12(0,1,1,1,0,1,1,1,0,1,1,1),
		packword12(0,1,1,1,1,1,1,1,1,1,1,1),
		packword12(0,0,1,1,1,1,1,1,1,1,1,0),
		packword12(0,0,0,1,0,0,0,0,0,1,0,0),
		packword12(0,0,1,0,0,0,0,0,0,0,1,0) };

static const uint32_t alien_bottom_in_12x8[] = {
		packword12(0,0,0,0,1,1,1,1,0,0,0,0),
		packword12(0,1,1,1,1,1,1,1,1,1,1,0),
		packword12(1,1,1,1,1,1,1,1,1,1,1,1),
		packword12(1,1,1,0,0,1,1,0,0,1,1,1),
		packword12(1,1,1,1,1,1,1,1,1,1,1,1),
		packword12(0,0,1,1,1,0,0,1,1,1,0,0),
		packword12(0,1,1,0,0,1,1,0,0,1,1,0),
		packword12(0,0,1,1,0,0,0,0,1,1,0,0) };

static const uint32_t alien_bottom_out_12x8[] = {
		packword12(0,0,0,0,1,1,1,1,0,0,0,0),
		packword12(0,1,1,1,1,1,1,1,1,1,1,0),
		packword12(1,1,1,1,1,1,1,1,1,1,1,1),
		packword12(1,1,1,0,0,1,1,0,0,1,1,1),
		packword12(1,1,1,1,1,1,1,1,1,1,1,1),
		packword12(0,0,0,1,1,0,0,1,1,0,0,0),
		packword12(0,0,1,1,0,1,1,0,1,1,0,0),
		packword12(1,1,0,0,0,0,0,0,0,0,1,1) };

// tank
static const uint32_t tank_15x8[] = {
		packword15(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0),
		packword15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
		packword15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
		packword15(0,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
		packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1) };

// currenlty unused
static const uint32_t block_erase_12x8[] = {
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0),
		packword12(0,0,0,0,0,0,0,0,0,0,0,0) };

// missile bitmaps

static const uint32_t missile0_3x7[] = {
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0)};

static const uint32_t missile1_3x7[] = {
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(1,1,1)};

static const uint32_t missile2l_3x7[] = {
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(1,1,1),
		packword3(0,1,0)};

static const uint32_t missile2r_3x7[] = {
		packword3(0,1,0),
		packword3(1,1,1),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0),
		packword3(0,1,0)};

static const uint32_t missile3l_6x7[] = {
		packword6(0,0,0,1,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,1,0,0,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,0,0,1,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,1,0,0,0,0)};

static const uint32_t missile3r_6x7[] = {
		packword6(0,1,0,0,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,0,0,1,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,1,0,0,0,0),
		packword6(0,0,1,0,0,0),
		packword6(0,0,0,1,0,0)};


// Shape of the entire bunker.
static const uint32_t bunker_24x18[] = {
		packword24(0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0),
		packword24(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
		packword24(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
		packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
		packword24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1) };

// These are the blocks that comprise the bunker and each time a bullet
// strikes one of these blocks, you erode the block as you sequence through
// these patterns.

static const uint32_t bunkerDamage0_6x6[] = {
		packword6(1,1,0,0,0,0),
		packword6(1,1,1,0,0,0),
		packword6(1,1,1,1,0,0),
		packword6(1,1,1,1,1,0),
		packword6(0,0,1,1,0,0),
		packword6(0,0,0,0,1,0)
};

static const uint32_t bunkerDamage1_6x6[] = {
		packword6(1,1,1,0,1,0),
		packword6(1,0,1,0,0,1),
		packword6(1,1,0,1,1,1),
		packword6(1,0,0,0,0,0),
		packword6(0,1,1,1,0,1),
		packword6(0,1,1,0,1,0)
};

static const uint32_t bunkerDamage2_6x6[] = {
		packword6(1,1,1,1,1,1),
		packword6(1,0,1,1,0,1),
		packword6(1,1,0,1,1,1),
		packword6(1,1,0,1,1,0),
		packword6(0,1,1,1,0,1),
		packword6(1,1,1,1,1,1)
};

static const uint32_t bunkerDamage3_6x6[] = {
		packword6(1,1,1,1,1,1),
		packword6(1,1,1,1,1,1),
		packword6(1,1,1,1,1,1),
		packword6(1,1,1,1,1,1),
		packword6(1,1,1,1,1,1),
		packword6(1,1,1,1,1,1)
};

static const uint32_t word_score_30x5[] = {
packword30(0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0),
packword30(1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0),
packword30(0,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,0,1,1,1,1,0,0),
packword30(0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0),
packword30(1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,1,0)
};

static const uint32_t word_lives_24x5[] = {
packword24(1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0),
packword24(1,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0),
packword24(1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,0,0,0),
packword24(1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0),
packword24(1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,0,0,0)
};

static const uint32_t word_game_24x5[] = {
packword24(1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1,1,1,0,0,0),
packword24(1,0,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,0),
packword24(1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0),
packword24(1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0),
packword24(1,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0)
};

static const uint32_t numbers_5x5[][5] = {
		{
				// 0
				packword5(0,0,1,0,0),
				packword5(0,1,0,1,0),
				packword5(0,1,0,1,0),
				packword5(0,1,0,1,0),
				packword5(0,0,1,0,0)
		},
		{
				// 1
				packword5(0,0,1,0,0),
				packword5(0,1,1,0,0),
				packword5(0,0,1,0,0),
				packword5(0,0,1,0,0),
				packword5(0,1,1,1,0)
		},
		{
				// 2
				packword5(0,1,1,1,0),
				packword5(0,0,0,1,0),
				packword5(0,1,1,1,0),
				packword5(0,1,0,0,0),
				packword5(0,1,1,1,0)
		},
		{
				// 3
				packword5(0,1,1,1,0),
				packword5(0,0,0,1,0),
				packword5(0,0,1,1,0),
				packword5(0,0,0,1,0),
				packword5(0,1,1,1,0),
		},
		{
				// 4
				packword5(0,0,0,1,0),
				packword5(0,0,1,1,0),
				packword5(0,1,0,1,0),
				packword5(0,1,1,1,0),
				packword5(0,0,0,1,0)
		},
		{
				// 5
				packword5(0,1,1,1,0),
				packword5(0,1,0,0,0),
				packword5(0,1,1,0,0),
				packword5(0,0,0,1,0),
				packword5(0,1,1,0,0)
		},
		{
				// 6
				packword5(0,0,1,1,0),
				packword5(0,1,0,0,0),
				packword5(0,1,1,0,0),
				packword5(0,1,0,1,0),
				packword5(0,0,1,0,0)
		},
		{
				// 7
				packword5(0,1,1,1,0),
				packword5(0,0,0,1,0),
				packword5(0,0,1,0,0),
				packword5(0,1,0,0,0),
				packword5(0,1,0,0,0)
		},
		{
				// 8
				packword5(0,0,1,0,0),
				packword5(0,1,0,1,0),
				packword5(0,0,1,0,0),
				packword5(0,1,0,1,0),
				packword5(0,0,1,0,0)
		},
		{
				// 9
				packword5(0,0,1,0,0),
				packword5(0,1,0,1,0),
				packword5(0,0,1,1,0),
				packword5(0,0,0,1,0),
				packword5(0,1,1,0,0)
		}
};


static const uint32_t floor_32x2[] = {
		0xFFFFFFFF,
		0xFFFFFFFF
};

#endif
