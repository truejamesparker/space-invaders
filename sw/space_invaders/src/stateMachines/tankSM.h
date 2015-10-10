#ifndef TANKSM_H_
#define TANKSM_H_

#include <stdio.h>
#include <stdint.h>

#include "../gpio/pushButtons.h"
#include "../elements/tank.h"

#define SM_PERIOD_TANK_MS 	30

void tankSM_init();

void tankSM_tick();

#endif /* TANKSM_H_ */
