/*
 * mixer.c
 *
 *  Created on: Oct 27, 2015
 *      Author: superman
 */

#include "mixer.h"

#define TRACK_NUM		8

extern const sound_t sound_alienKilled;
extern const sound_t sound_alienMove2;
extern const sound_t sound_alienMove3;
extern const sound_t sound_alienMove4;
extern const sound_t sound_alienMove1;
extern const sound_t sound_spaceship;
extern const sound_t sound_tankDeath;
extern const sound_t sound_tankShot;

volatile bool active_sounds[TRACK_NUM];

static sound_track_t sound_tracks[TRACK_NUM] = {
		{.sound = &sound_alienKilled, .sample_num = 0},
		{.sound = &sound_alienMove1, .sample_num = 0},
		{.sound = &sound_alienMove2, .sample_num = 0},
		{.sound = &sound_alienMove3, .sample_num = 0},
		{.sound = &sound_alienMove4, .sample_num = 0},
		{.sound = &sound_spaceship, .sample_num = 0},
		{.sound = &sound_tankDeath, .sample_num = 0},
		{.sound = &sound_tankShot, .sample_num = 0},
};

uint32_t getMixedSample(){
	int i;
	uint32_t sample = 0;
	for(i=0; i<TRACK_NUM; i++){
		if(active_sounds[i]){
			if(sound_tracks[i].sample_num == sound_tracks[i].sound->numSamples){
				active_sounds[i] = false;
				sound_tracks[i].sample_num = 0;
			}
			else{
				sample += sound_tracks[i].sound->data[sound_tracks[i].sample_num];
				sound_tracks[i].sample_num++;
			}
		}
	}
	return sample;
}

void play_track(uint8_t index){
	active_sounds[index] = true;
}
