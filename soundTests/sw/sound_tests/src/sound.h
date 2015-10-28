/*
 * sound.h
 *
 *  Created on: Oct 27, 2015
 *      Author: superman
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <stdint.h>

typedef struct{
    uint32_t numSamples;
    uint32_t sampleRate;
    const uint32_t data[];
} sound_t;


typedef struct {
    const sound_t* sound;
    uint32_t sample_num;
} sound_track_t;


#endif /* SOUND_H_ */
