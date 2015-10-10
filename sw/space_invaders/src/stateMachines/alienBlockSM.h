#ifndef ALIENBLOCKSM_H_
#define ALIENBLOCKSM_H_

#include <stdio.h>
#include <stdint.h>

#include "../elements/aliens.h"

#define SM_PERIOD_ALIEN_BLOCK_MS 	325

void alienBlockSM_init();

void alienBlockSM_tick();

#endif /* ALIENBLOCKSM_H_ */
