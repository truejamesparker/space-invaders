#ifndef SCREENREFRESHSH_H_
#define SCREENREFRESHSH_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../screen/screen.h"
#include "gamePlaySM.h"
#include "../gpio/slideSwitches.h"
#include "../timer/timer.h"

// Screen refresh rate of 33.33 Hz
#define SM_PERIOD_SCREEN_REFRESH_MS 	30

void screenRefreshSM_tick();
void screenRefreshSM_hwCaptureDone();

#endif /* SCREENREFRESHSH_H_ */
