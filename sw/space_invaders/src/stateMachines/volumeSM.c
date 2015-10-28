/*
 * volumeSM.c
 *
 *  Created on: Oct 28, 2015
 *      Author: superman
 */

#include "volumeSM.h"

void volumeSM_tick(){
	if (pushButtons_downPressed()) {
		audio_volume_down();
	}
	else if (pushButtons_upPressed()) {
		audio_volume_up();
	}
}
