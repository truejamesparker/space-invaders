#ifndef TANKSM_H_
#define TANKSM_H_

#include <stdio.h>
#include <stdint.h>

#include "../controller/controller.h"
#include "../gpio/pushButtons.h"
#include "../elements/tank.h"
#include "../elements/missiles.h"
#include "../elements/gameScreen.h"
#include "spaceshipSM.h"
#include "alienBlockSM.h"
#include "controllerSM.h"

#define SM_PERIOD_TANK_MS 	60

// how many periods to wait after a tank death
#define TANK_KILLED_TIMEOUT	30

void tankSM_tick();

void tankSM_lock();
void tankSM_unlock();

#endif /* TANKSM_H_ */
