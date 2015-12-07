#ifndef SCREENREFRESHSH_H_
#define SCREENREFRESHSH_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../screen/screen.h"
#include "gamePlaySM.h"
#include "../gpio/slideSwitches.h"

// Screen refresh rate of 33.33 Hz
#define SM_PERIOD_SCREEN_REFRESH_MS 	30

void screenRefreshSM_tick();

#endif /* SCREENREFRESHSH_H_ */
