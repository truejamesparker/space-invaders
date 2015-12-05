#ifndef GAMEPLAYSM_H_
#define GAMEPLAYSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../gpio/pushButtons.h"
#include "../gpio/slideSwitches.h"
#include "../elements/aliens.h"
#include "../elements/tank.h"
#include "alienBlockSM.h"
#include "spaceshipSM.h"
#include "tankSM.h"
#include "controllerSM.h"

#define SM_PERIOD_GAMEPLAY_MS		20

void gamePlaySM_tick();

// Allow the user to play/pause
void gamePlaySM_pauseGame();
void gamePlaySM_resumeGame();


#endif /* GAMEPLAYSM_H_ */
