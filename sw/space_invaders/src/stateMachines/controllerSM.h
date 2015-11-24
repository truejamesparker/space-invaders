#ifndef CONTROLLERSM_H_
#define CONTROLLERSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../controller/controller.h"

#define SM_PERIOD_CONTROLLER_MS		10

// tank move speeds
#define CONTROLLER_TANK_MOVE_SLOW		8
#define CONTROLLER_TANK_MOVE_REGULAR	6
#define CONTROLLER_TANK_MOVE_FAST		4
#define CONTROLLER_TANK_MOVE_VERY_FAST	2

void controllerSM_tick();
void controllerSM_lock();
void controllerSM_unlock();
void controllerSM_updateTankSpeed(uint8_t speed);

#endif /* CONTROLLERSM_H_ */
