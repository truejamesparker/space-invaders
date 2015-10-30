#ifndef AUDIO_H_
#define AUDIO_H_

#include "stdbool.h"
#include "stdint.h"
#include "sounds.h"
#include "../globals.h"
#include "../soundDriver/xac97_l.h"
#include "xparameters.h"

// size of AC'97 buffer (samples)
#define BUFFER_SIZE 			512

// we want to fill the buffer when it is half empty
#define MAX_FIFO_SAMPLES		BUFFER_SIZE/2

// number of preset volume levels
#define VOL_LEVELS				32

// sound index values to be used with
// audio_play_track() and audio_mute_track()
#define SOUND_ALIEN_KILLED		0
#define SOUND_ALIEN_MOVE1		1
#define SOUND_ALIEN_MOVE2		2
#define SOUND_ALIEN_MOVE3		3
#define SOUND_ALIEN_MOVE4		4
#define SOUND_SPACESHIP			5
#define SOUND_SPACESHIP_KILLED	6
#define SOUND_TANK_DEATH		7
#define SOUND_TANK_SHOT			8

// init the AC'97
void audio_init();

// the interrupt handler for the AC'97;
// called every time the buffer is half-empty
void audio_interrupt_handler();

// return the next audio sample
// (a mix of all current sound tracks)
uint32_t getMixedSample();

// play sound (mark track as ready for play)
void audio_play_track(uint8_t index);

// mute track (mark track to be excluded from play)
void audio_mute_track(uint8_t index);

// plays the next alinen march sound
void audio_play_alien_track();

// increase volume
void audio_volume_up();

// decrease volume
void audio_volume_down();


#endif /* AUDIO_H_ */
