/*
 * volumeSM.h
 *
 *  Created on: Oct 28, 2015
 *      Author: superman
 */

#ifndef VOLUMESM_H_
#define VOLUMESM_H_

#include "../audio/audio.h"
#include "../gpio/pushButtons.h"

#define SM_PERIOD_VOLUME_MS	60

void volumeSM_tick();

#endif /* VOLUMESM_H_ */
