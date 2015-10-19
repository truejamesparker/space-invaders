#ifndef SCREENREFRESHSH_H_
#define SCREENREFRESHSH_H_

#include <stdio.h>
#include <stdint.h>

#include "../screen/screen.h"

// Screen refresh rate of 66.67 Hz
#define SM_PERIOD_SCREEN_REFRESH_MS 	30

void screenRefreshSM_tick();

#endif /* SCREENREFRESHSH_H_ */
