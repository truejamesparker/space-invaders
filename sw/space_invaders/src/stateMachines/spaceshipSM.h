#ifndef SPACESHIPSM_H_
#define SPACESHIPSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../elements/spaceship.h"

#define SM_PERIOD_SPACESHIP_MS	15

// How many times out of 1000 do you want the
// spaceship to be started every SM period?
// (tenths of percentage, i.e. 10/1000 = 1%)
#define SPACESHIP_START_PROBABILITY		4

// how fast to flash score (flash every n periods)
#define SPACESHIP_FLASH_REFRESH			4

// periods to wait after a spaceship death
#define SPACESHIP_MOURNING_PERIOD_LEN	(5*SPACESHIP_FLASH_REFRESH*SPACESHIP_SCORE_FLASHES)

void spaceshipSM_tick();

// lock/unlock this SM from runnning
void spaceshipSM_lock();
void spaceshipSM_unlock();

#endif /* SPACESHIPSM_H_ */
