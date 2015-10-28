#include "taskControl.h"

static task_t tasks[TC_SM_COUNT];

// ----------------------------------------------------------------------------

void taskControl_init() {
	uint8_t sm = 0;

	// Screen Refresh SM (highest priority)
	tasks[sm].period = SM_PERIOD_SCREEN_REFRESH_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &screenRefreshSM_tick;

	// Tank SM
	++sm;
	tasks[sm].period = SM_PERIOD_GAMEPLAY_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &gamePlaySM_tick;

	// Tank SM
	++sm;
	tasks[sm].period = SM_PERIOD_TANK_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &tankSM_tick;

	// Alien Block SM
	++sm;
	tasks[sm].period = SM_PERIOD_ALIEN_BLOCK_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &alienBlockSM_tick;

	// Spaceship SM
	++sm;
	tasks[sm].period = SM_PERIOD_SPACESHIP_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &spaceshipSM_tick;

	// Missile SM (for updating the missiles)
	++sm;
	tasks[sm].period = SM_PERIOD_MISSILE_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &missileSM_tick;

	// Volume SM (for updating the volume)
	++sm;
	tasks[sm].period = SM_PERIOD_VOLUME_MS;
	tasks[sm].elapsedTime = tasks[sm].period;
	tasks[sm].TickFn = &volumeSM_tick;

}

// ----------------------------------------------------------------------------

void taskControl_tick() {
	uint8_t i;
	for (i=0; i<TC_SM_COUNT; i++) {
		// Check to see if this SM is ready to be ticked.
		if (tasks[i].elapsedTime >= tasks[i].period) {
			// in fact, it is.
			// So make it happen and reset elapsedTime
			tasks[i].TickFn();
			tasks[i].elapsedTime = 0;
		}

		// increase the task's elapsedTime by whatever the period of
		// the FIT timer is (which is what calls this function)
		tasks[i].elapsedTime += TC_TIMER_PERIOD_MS;
	}
}
