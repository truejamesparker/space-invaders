/*
 * mixer.h
 *
 *  Created on: Oct 27, 2015
 *      Author: superman
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "stdbool.h"
#include "stdint.h"
#include "sound.h"

#define SOUND_ALIEN_KILLED		0
#define SOUND_ALIEN_MOVE1		1
#define SOUND_ALIEN_MOVE2		2
#define SOUND_ALIEN_MOVE3		3
#define SOUND_ALIEN_MOVE4		4
#define SOUND_SPACESHIP			5
#define SOUND_TANK_DEATH		6
#define SOUND_TANK_SHOT			7

uint32_t getMixedSample();
void play_track(uint8_t index);

#endif /* MIXER_H_ */
