/*
 * audio.c
 *
 *  Created on: Oct 27, 2015
 *      Author: superman
 */

#include "audio.h"

#define TRACK_NUM		8

static uint32_t volumes[VOL_LEVELS] = {
	AC97_VOL_ATTN_0_DB,
	AC97_VOL_ATTN_1_5_DB,
	AC97_VOL_ATTN_3_0_DB,
	AC97_VOL_ATTN_4_5_DB,
	AC97_VOL_ATTN_6_0_DB,
	AC97_VOL_ATTN_7_5_DB,
	AC97_VOL_ATTN_9_0_DB,
	AC97_VOL_ATTN_10_0_DB,
	AC97_VOL_ATTN_11_5_DB,
	AC97_VOL_ATTN_13_0_DB,
	AC97_VOL_ATTN_14_5_DB,
	AC97_VOL_ATTN_16_0_DB,
	AC97_VOL_ATTN_17_5_DB,
	AC97_VOL_ATTN_19_0_DB,
	AC97_VOL_ATTN_20_5_DB,
	AC97_VOL_ATTN_22_0_DB,
	AC97_VOL_ATTN_23_5_DB,
	AC97_VOL_ATTN_25_0_DB,
	AC97_VOL_ATTN_26_5_DB,
	AC97_VOL_ATTN_28_0_DB,
	AC97_VOL_ATTN_29_5_DB,
	AC97_VOL_ATTN_31_0_DB,
	AC97_VOL_ATTN_32_5_DB,
	AC97_VOL_ATTN_34_0_DB,
	AC97_VOL_ATTN_35_5_DB,
	AC97_VOL_ATTN_37_0_DB,
	AC97_VOL_ATTN_38_5_DB,
	AC97_VOL_ATTN_40_0_DB,
	AC97_VOL_ATTN_41_5_DB,
	AC97_VOL_ATTN_43_0_DB,
	AC97_VOL_ATTN_44_5_DB,
	AC97_VOL_ATTN_46_0_DB,
};

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


void audio_init(){
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);
	XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_MAX);
}


uint32_t getMixedSample(){
	int i;
	uint32_t sample = 0;
	uint8_t num_streams = 0;
	for(i=0; i<TRACK_NUM; i++){
		if(active_sounds[i]){
			if(sound_tracks[i].sample_num == sound_tracks[i].sound->numSamples){
				active_sounds[i] = false;
				sound_tracks[i].sample_num = 0;
			}
			else{
				sample += sound_tracks[i].sound->data[sound_tracks[i].sample_num];
				num_streams++;
				sound_tracks[i].sample_num++;
			}
		}
	}
	num_streams = (num_streams) ? num_streams : 1; // prevent division by zero
	return sample/num_streams;
}

void play_track(uint8_t index){
	active_sounds[index] = true;
}
