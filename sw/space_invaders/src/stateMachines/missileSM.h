#ifndef MISSLESM_H_
#define MISSLESM_H_

#include <stdio.h>
#include <stdint.h>

#include "../elements/missiles.h"

#define SM_PERIOD_MISSILE_MS 	10

// missile speeds (update every n periods)
#define MISSILE_ALIEN_REFRESH	2
#define MISSILE_TANK_REFRESH	1


void missileSM_tick();

#endif /* MISSLESM_H_ */
