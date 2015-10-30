#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <stdint.h>


// sound struct
typedef struct{
    uint32_t numSamples;	// total number of samples
    uint32_t sampleRate;	// sample rate
    const uint32_t data[]; 	// actual samples
} sound_t;


// soundtrack struct
typedef struct {
    const sound_t* sound;	// sound 
    uint32_t sample_num;	// current point (sample) in playback
} sound_track_t;


#endif /* SOUNDS_H_ */
