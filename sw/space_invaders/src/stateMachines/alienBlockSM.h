#ifndef ALIENBLOCKSM_H_
#define ALIENBLOCKSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../elements/aliens.h"
#include "../elements/missiles.h"
#include "../elements/gameScreen.h"

#define SM_PERIOD_ALIEN_BLOCK_MS 		25

// march speeds (march every n periods)
#define ALIEN_BLOCK_MARCH_SLOW			13
#define ALIEN_BLOCK_MARCH_MED			11
#define ALIEN_BLOCK_MARCH_FAST			9
#define ALIEN_BLOCK_MARCH_VERY_FAST		7

// minimum count required for march speeds
#define ALIEN_BLOCK_SLOW_MIN_COUNT			(ALIEN_COUNT-1*ALIEN_COL_COUNT)
#define ALIEN_BLOCK_MED_MIN_COUNT			(ALIEN_COUNT-2*ALIEN_COL_COUNT)
#define ALIEN_BLOCK_FAST_MIN_COUNT			(ALIEN_COUNT-4*ALIEN_COL_COUNT)
#define ALIEN_BLOCK_VERY_FAST_MIN_COUNT		0

// how fast to clean up killed alien (clean every n periods)
#define ALIEN_BLOCK_KILL_REFRESH		2

// How many times out of 100 do you want a missile
// to be fired every SM tick?
#define ALIEN_BLOCK_MISSILE_PROBABILITY		75

void alienBlockSM_tick();

// Other people can call these to change marching speeds
void alienBlockSM_marchSlow();
void alienBlockSM_marchMedium();
void alienBlockSM_marchFast();
void alienBlockSM_marchVeryFast();

// lock/unlock this SM from runnning
void alienBlockSM_lock();
void alienBlockSM_unlock();

// Reset the aliens
void alienBlockSM_startNewLevel();

#endif /* ALIENBLOCKSM_H_ */
