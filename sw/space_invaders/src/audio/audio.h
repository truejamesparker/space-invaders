/*
 * audio.h
 *
 *  Created on: Oct 27, 2015
 *      Author: superman
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "stdbool.h"
#include "stdint.h"
#include "sound.h"
#include "../globals.h"
#include "../soundDriver/xac97_l.h"
#include "xparameters.h"

#define BUFFER_SIZE 			512
#define MAX_FIFO_SAMPLES		BUFFER_SIZE/2
#define VOL_LEVELS				32

#define SOUND_ALIEN_KILLED		0
#define SOUND_ALIEN_MOVE1		1
#define SOUND_ALIEN_MOVE2		2
#define SOUND_ALIEN_MOVE3		3
#define SOUND_ALIEN_MOVE4		4
#define SOUND_SPACESHIP			5
#define SOUND_TANK_DEATH		6
#define SOUND_TANK_SHOT			7

void audio_init();
void audio_interrupt_handler();
uint32_t getMixedSample();
void audio_play_track(uint8_t index);
void audio_mute_track(uint8_t index);
void audio_play_alien_track();
void audio_volume_up();
void audio_volume_down();


#endif /* AUDIO_H_ */
