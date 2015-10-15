#ifndef GAMEPLAYSM_H_
#define GAMEPLAYSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../gpio/pushButtons.h"
#include "../elements/aliens.h"
#include "../elements/tank.h"
#include "alienBlockSM.h"
#include "spaceshipSM.h"

#define SM_PERIOD_GAMEPLAY_MS		10

void gamePlaySM_tick();


#endif /* GAMEPLAYSM_H_ */
