#ifndef SPACESHIPSM_H_
#define SPACESHIPSM_H_

#include <stdio.h>
#include <stdint.h>

#include "../elements/spaceship.h"

#define SM_PERIOD_SPACESHIP_MS	60

// How many times out of 1000 do you want the
// spaceship to be started every SM period?
// (tenths of percentage, i.e. 10/1000 = 1%)
#define SPACESHIP_START_PROBABILITY		3

// periods to wait after a spaceship death
#define SPACESHIP_MOURNING_PERIOD		5


void spaceshipSM_tick();

#endif /* SPACESHIPSM_H_ */
