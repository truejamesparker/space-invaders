#include "taskControl.h"

static task_t tasks[TC_SM_COUNT];

static XTmrCtr TmrCtrInstancePtr;

static uint32_t times[TC_PERIODS_TO_MEASURE];
static uint32_t periodsElapsed = 0;

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

	// initialize the timer to calc CPU utilization
	XTmrCtr_Initialize(&TmrCtrInstancePtr, XPAR_AXI_TIMER_0_DEVICE_ID);
}

// ----------------------------------------------------------------------------

void taskControl_tick() {
	XTmrCtr_Reset(&TmrCtrInstancePtr, 0);
	uint32_t time1 = XTmrCtr_GetValue(&TmrCtrInstancePtr, 0);
	XTmrCtr_Start(&TmrCtrInstancePtr, 0);

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
		tasks[i].elapsedTime += TC_SM_PERIOD_GCD;
	}

	XTmrCtr_Stop(&TmrCtrInstancePtr, 0);
	uint32_t time2 = XTmrCtr_GetValue(&TmrCtrInstancePtr, 0);
	times[periodsElapsed++] = time2 - time1;
	if (periodsElapsed == TC_PERIODS_TO_MEASURE) {
		uint32_t j = 0;
		uint32_t sum = 0;
		for (j=0;j<TC_PERIODS_TO_MEASURE;j++) sum += times[j];
		xil_printf("Average time spent in taskControl_tick: %d\r\n", sum/TC_PERIODS_TO_MEASURE);
	}
}
