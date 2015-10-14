#ifndef ALIENBLOCKSM_H_
#define ALIENBLOCKSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../elements/aliens.h"
#include "../elements/missiles.h"

#define SM_PERIOD_ALIEN_BLOCK_MS 		325

// How many times out of 100 do you want a missile
// to be fired every SM tick?
#define ALIEN_BLOCK_MISSILE_PROBABILITY		45

void alienBlockSM_tick();

#endif /* ALIENBLOCKSM_H_ */
